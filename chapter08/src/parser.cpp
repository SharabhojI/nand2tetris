#include "parser.h"
#include <iostream>
#include <unordered_map>
#include <stdexcept>

Parser::Parser(std::string input_file) {
    this->input_file.open(input_file);
    if (!this->input_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + input_file);
    }
    std::cout << "Parser initialized with file: " << input_file << std::endl;
}

bool Parser::hasMoreLines() {
    return input_file.peek() != EOF;
}

void Parser::advance() {
    if (!hasMoreLines()) {
        current_cmd = "";
        return;
    }
    do {
        std::getline(input_file, current_cmd);
        std::cout << "Read line: " << current_cmd << std::endl;
        const char* whitespace = " \t\n\r\f\v";

        current_cmd.erase(0, current_cmd.find_first_not_of(whitespace));

        size_t comment = current_cmd.find("//");
        if (comment != std::string::npos) {
            current_cmd.erase(comment);
        }

        current_cmd.erase(current_cmd.find_last_not_of(whitespace) + 1);
    } while (current_cmd.empty() && hasMoreLines());

    if (current_cmd.empty()) {
        return;
    }    
    std::cout << "Processed command: " << current_cmd << std::endl;
    static const std::unordered_map<std::string, Parser::CommandType> cmd_table = {
        {"add", C_ARITHMETIC},
        {"sub", C_ARITHMETIC},
        {"neg", C_ARITHMETIC},
        {"eq", C_ARITHMETIC},
        {"gt", C_ARITHMETIC},
        {"lt", C_ARITHMETIC},
        {"and", C_ARITHMETIC},
        {"or", C_ARITHMETIC},
        {"not", C_ARITHMETIC},
        {"push", C_PUSH},
        {"pop", C_POP},
        {"label", C_LABEL},
        {"goto", C_GOTO},
        {"if-goto", C_IF},
        {"function", C_FUNCTION},
        {"call", C_CALL},
        {"return", C_RETURN}
    };

    std::string cmd = current_cmd.substr(0, current_cmd.find(' '));
    auto it = cmd_table.find(cmd);
    if (it != cmd_table.end()) {
        current_cmd_type = it->second;
    } else {
        throw std::runtime_error("Unknown command encountered: " + current_cmd);
    }
    std::cout << "Command type set to: " << current_cmd_type << std::endl;
}

Parser::CommandType Parser::commandType() {
    return current_cmd_type;
}

std::string Parser::arg1() {
    if (current_cmd_type != C_RETURN) {
        if (current_cmd_type == C_ARITHMETIC) {
           return current_cmd.substr(0, current_cmd.find(' ')); 
        }
        size_t first = current_cmd.find(' ');
        size_t second = current_cmd.find(' ', first + 1);
        if (second != std::string::npos) {
            return current_cmd.substr(first + 1, second - first - 1);
        }
        return current_cmd.substr(first + 1);
    } else { 
        throw std::runtime_error("arg1() called with incorrect command type");
    }
}

int Parser::arg2() {
    if (current_cmd_type == C_PUSH || current_cmd_type == C_POP || current_cmd_type == C_FUNCTION || current_cmd_type == C_CALL) {
        size_t first = current_cmd.find(' ');
        size_t second = current_cmd.find(' ', first + 1);
        if (second != std::string::npos) {
            return std::stoi(current_cmd.substr(second + 1));
        }
        throw std::runtime_error("Invalid command format for arg2()");
    } else {
        throw std::runtime_error("arg2() called with incorrect command type");
    }
}