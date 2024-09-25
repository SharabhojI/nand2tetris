#include "code_writer.h"
#include <iostream>
#include <stdexcept>
#include<filesystem>

CodeWriter::CodeWriter(std::string output_file) {
    this->label_num = 0;
    std::filesystem::path p(output_file);
    this->file_name = p.stem().string(); // get file name without ext
    this->output_file.open(output_file);
    if (!this->output_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + file_name);
    }
    std::cout << "CodeWriter initialized with: " << file_name << std::endl;
} 

void CodeWriter::writeArithmetic(std::string command) {
    if (command == "add") {
        writeAdd();
    } else if (command == "sub") {
        writeSub();
    } else if (command == "neg") {
        writeNeg();
    } else if (command == "eq" || command == "gt" || command == "lt") {
        writeCompare(command);
    } else if (command == "and") {
        writeAnd();
    } else if (command == "or") {
        writeOr();
    } else if (command == "not") {
        writeNot();
    } else {
        throw std::runtime_error("writeArithmetic called with incorrect command");
    }
}

void CodeWriter::writeAdd() {
    output_file << "// add" << std::endl;
    writePushPop(C_POP, "temp", 0); // pop to @R5 (TEMP[0])
    writePushPop(C_POP, "temp", 1); // pop to @R6 (TEMP[1])
    output_file << "@R5" << std::endl
                << "D=M" << std::endl
                << "@R6" << std::endl
                << "M=D+M" << std::endl; // add operands and store in @R6
    writePushPop(C_PUSH, "temp", 1); // push @R6 to the stack
}

void CodeWriter::writeSub() {
    output_file << "// sub" << std::endl;
    writePushPop(C_POP, "temp", 0); // pop to @R5 (TEMP[0])
    writePushPop(C_POP, "temp", 1); // pop to @R6 (TEMP[1])
    output_file << "@R5" << std::endl
                << "D=M" << std::endl
                << "@R6" << std::endl
                << "M=M-D" << std::endl; // subtract operands and store in @R6
    writePushPop(C_PUSH, "temp", 1); // push @R6 to the stack
}

void CodeWriter::writeNeg() {
    output_file << "// neg" << std::endl;
    writePushPop(C_POP, "temp", 0); // pop to @R5 (TEMP[0])
    output_file << "@R5" << std::endl
                << "M=-M" << std::endl; // negate value and store in @R5
    writePushPop(C_PUSH, "temp", 0); // push @R5 to the stack
}

void CodeWriter::writeCompare(std::string comparisonType) {
    std::string true_label = "TRUE_" + std::to_string(label_num);
    std::string end_label = "END_" + std::to_string(label_num);
    label_num++;

    output_file << "// " << comparisonType << std::endl;
    
    writePushPop(C_POP, "temp", 0);  // pop to @R5 (TEMP[0])
    writePushPop(C_POP, "temp", 1);  // pop to @R6 (TEMP[1])

    output_file << "@R5" << std::endl
                << "D=M" << std::endl
                << "@R6" << std::endl
                << "D=M-D" << std::endl;

    if (comparisonType == "eq") {
        output_file << "@" << true_label << std::endl
                    << "D;JEQ" << std::endl;
    } else if (comparisonType == "gt") {
        output_file << "@" << true_label << std::endl
                    << "D;JGT" << std::endl;
    } else if (comparisonType == "lt") {
        output_file << "@" << true_label << std::endl
                    << "D;JLT" << std::endl;
    }

    // False case
    output_file << "@SP" << std::endl
                << "A=M" << std::endl
                << "M=0" << std::endl
                << "@" << end_label << std::endl
                << "0;JMP" << std::endl;

    // True case
    output_file << "(" << true_label << ")" << std::endl
                << "@SP" << std::endl
                << "A=M" << std::endl
                << "M=-1" << std::endl;
    // End
    output_file << "(" << end_label << ")" << std::endl
                << "@SP" << std::endl
                << "M=M+1" << std::endl;
}

void CodeWriter::writeAnd() {
    output_file << "// and" << std::endl;
    writePushPop(C_POP, "temp", 0); // pop to @R5 (TEMP[0])
    writePushPop(C_POP, "temp", 1); // pop to @R6 (TEMP[1])
    output_file << "@R5" << std::endl
                << "D=M" << std::endl
                << "@R6" << std::endl
                << "M=D&M" << std::endl; // AND operands and store in @R6
    writePushPop(C_PUSH, "temp", 1); // push @R6 to the stack
}

void CodeWriter::writeOr() {
    output_file << "// or" << std::endl;
    writePushPop(C_POP, "temp", 0); // pop to @R5 (TEMP[0])
    writePushPop(C_POP, "temp", 1); // pop to @R6 (TEMP[1])
    output_file << "@R5" << std::endl
                << "D=M" << std::endl
                << "@R6" << std::endl
                << "M=D|M" << std::endl; // OR operands and store in @R6
    writePushPop(C_PUSH, "temp", 1); // push @R6 to the stack
}

void CodeWriter::writeNot() {
    output_file << "// not" << std::endl;
    writePushPop(C_POP, "temp", 0); // pop to @R5 (TEMP[0])
    output_file << "@R5" << std::endl
                << "M=!M" << std::endl; // NOT value and store in @R5
    writePushPop(C_PUSH, "temp", 0); // push @R5 to the stack
}

void CodeWriter::writePushPop(CodeWriter::CommandType command, std::string segment, int index) {
    if (command == C_PUSH) {
        writePush(segment, index);
    } else if (command == C_POP) {
        writePop(segment, index);
    } else {
        throw std::runtime_error("writePushPop called with incorrect command");
    }
}

void CodeWriter::writePush(std::string segment, int index) {
    output_file << "// push " << segment << " " << index << std::endl;

    if (segment == "pointer") {
        output_file << "@" << (index == 0 ? "THIS" : "THAT") << std::endl // set A reg to THIS/THAT
                    << "D=M" << std::endl; // set D reg to value in THIS/THAT 
    } else if (segment == "temp") {
        output_file << "@" << (5 + index) << std::endl // set A reg to temp memory address 5 + index
                    << "D=M" << std::endl;  // set D reg to value stored in temp memory address
    } else if (segment == "constant") {
        output_file << "@" << index << std::endl // set A reg to constant value 'index'
                    << "D=A" << std::endl; // set D reg to constant value 'index'
    } else if (segment == "static") {
        output_file << "@" << file_name << "." << index << std::endl // set A reg to static variable file_name.index
                    << "D=M" << std::endl; // set D reg to value stored in static variable
    } else {
        // segment == local, argument, this, that
        std::string base_address = (segment == "local") ? "LCL" :
                                   (segment == "argument") ? "ARG" :
                                   (segment == "this") ? "THIS" : "THAT";
        output_file << "@" << base_address << std::endl
                    << "D=M" << std::endl // set D reg to base address of selected segment
                    << "@" << index << std::endl // set A reg to constant value 'index'
                    << "A=D+A" << std::endl // set A reg to base address + index
                    << "D=M" << std::endl; // set D reg to value stored in base address + index
    }

    output_file << "@SP" << std::endl
                << "A=M" << std::endl // set A reg to address at SP (top of stack)
                << "M=D" << std::endl // store value D at the top of stack
                << "@SP" << std::endl
                << "M=M+1" << std::endl; // increment Stack Pointer (SP++)
}

void CodeWriter::writePop(std::string segment, int index) {
    output_file << "// pop " << segment << " " << index << std::endl;

    if (segment == "pointer") {
        output_file << "@SP" << std::endl
                    << "AM=M-1" << std::endl // decrement SP and set A reg to new SP and M reg to top of stack
                    << "D=M" << std::endl // set D reg to value at top of stack
                    << "@" << (index == 0 ? "THIS" : "THAT") <<  std::endl // set A reg to THIS/THAT
                    << "M=D" << std::endl; // set M reg (THIS/THAT) to D reg (popped value)
    } else if (segment == "temp") {
        output_file << "@SP" << std::endl
                    << "AM=M-1" << std::endl 
                    << "D=M" << std::endl
                    << "@" << (5 + index) << std::endl // set A reg to base address + index
                    << "M=D" << std::endl; // set M reg (base address + index) to D reg (popped value)
    } else if (segment == "constant") {
        output_file << "@SP" << std::endl
                    << "M=M-1" << std::endl; // decrement SP
    } else if (segment == "static") {
        output_file << "@SP" << std::endl
                    << "AM=M-1" << std::endl
                    << "D=M" << std::endl
                    << "@" << file_name << "." << index << std::endl // set A reg to static variable file_name.index
                    << "M=D" << std::endl; // set M reg (static variable) to D reg (popped value)
    } else {
        // segment == local, argument, this, that
        std::string base_address = (segment == "local") ? "LCL" :
                                   (segment == "argument") ? "ARG" :
                                   (segment == "this") ? "THIS" : "THAT";
        output_file << "@" << base_address << std::endl
                    << "D=M" << std::endl // set D reg to base address of selected segment
                    << "@" << index << std::endl // set A reg to constant value 'index'
                    << "D=D+A" << std::endl // set D reg to base address + index
                    << "@R13" << std::endl 
                    << "M=D" << std::endl // set R13 (temp register) to base address + index
                    << "@SP" << std::endl
                    << "AM=M-1" << std::endl
                    << "D=M" << std::endl
                    << "@R13" << std::endl
                    << "A=M" << std::endl // set A reg to address in R13
                    << "M=D" << std::endl; // set M reg (target address) to D reg (popped value)
    }
} 

void CodeWriter::close() {
    try {
        this->output_file.close();
        std::cout << "Closed file: " << file_name << std::endl;
    } catch (const std::ios_base::failure& e) {
        throw std::runtime_error("Failed to close file: " + file_name + ". Error: " + e.what());
    }
}