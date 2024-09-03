#include "parser.h"
#include <iostream>
#include <stdexcept>

Parser::Parser(std::string input_file) {
    this->input_file.open(input_file);
    if (!this->input_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + input_file);
    }
    std::cout << "Parser initialized with file: " << input_file << std::endl;
}

bool Parser::hasMoreLines() {
    if (eof_reached) {
        return false;
    }
    return input_file.peek() != EOF;
}

void Parser::advance() {
    if (!hasMoreLines()) {
        eof_reached = true;
        current_inst = "";
        return;
    }

    do {
        std::getline(input_file, current_inst);
        std::cout << "Read line: " << current_inst << std::endl;
        const char* whitespace = " \t\n\r\f\v";

        current_inst.erase(0, current_inst.find_first_not_of(whitespace));

        size_t comment = current_inst.find("//");
        if (comment != std::string::npos) {
            current_inst.erase(comment);
        }

        current_inst.erase(current_inst.find_last_not_of(whitespace) + 1);
    } while (current_inst.empty() && hasMoreLines());

    if (current_inst.empty()) {
        eof_reached = true;
        return;
    }

    std::cout << "Processed instruction: " << current_inst << std::endl;

    if (current_inst[0] == '@') {
        current_inst_type = A_INSTRUCTION;
    } else if (current_inst[0] == '(') {
        current_inst_type = L_INSTRUCTION;
    } else {
        current_inst_type = C_INSTRUCTION;
    }
    std::cout << "Instruction type set to: " << static_cast<int>(current_inst_type) << std::endl;
}

Parser::InstructionType Parser::instructionType() {
    return current_inst_type;
}

std::string Parser::symbol() {
    if (current_inst_type == A_INSTRUCTION) {
        return current_inst.substr(1); // return contents of inst after '@'
    } else if (current_inst_type == L_INSTRUCTION) {
        return current_inst.substr(1, current_inst.length() - 2); // return substring of length len(current_inst) - 2 from 2nd char onwards
    } else {
        throw std::runtime_error("symbol() called with incorrect instruction type");
    }
}

std::string Parser::dest() {
    if (current_inst_type == C_INSTRUCTION) {
        size_t equals = current_inst.find('='); // find equal char
        if (equals != std::string::npos) {
            return current_inst.substr(0, equals); // return substring up to equal char
        }
        return "";
    } else {
        throw std::runtime_error("dest() called with incorrect instruction type");
    }
}

std::string Parser::comp() {
    if (current_inst_type == C_INSTRUCTION) {
        size_t equals = current_inst.find('=');
        size_t semicolon = current_inst.find(';');
        if (equals != std::string::npos) {
            if (semicolon != std::string::npos) {
                return current_inst.substr(equals + 1, semicolon - equals - 1);
            } else {
                return current_inst.substr(equals + 1);
            }
        } else {
            return current_inst.substr(0, semicolon); // return substring upto ';'
        }
    } else {
        throw std::runtime_error("comp() called with incorrect instruction type");
    }
}

std::string Parser::jump() {
    if (current_inst_type == C_INSTRUCTION) {  
        size_t semicolon = current_inst.find(';'); // find semicolon char
        if (semicolon != std::string::npos) {
            return current_inst.substr(semicolon + 1); // return substring after semicolon
        }
        return "";
    } else {
        throw std::runtime_error("jump() called with incorrect instruction type");
    }
}