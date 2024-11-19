#include "code_writer.h"
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <cctype>

CodeWriter::CodeWriter(std::string output_file) {
    this->label_num = 0;
    this->return_counter = 0;
    this->current_function = "";
    std::filesystem::path p(output_file);
    this->file_name = p.stem().string(); // get file name without ext
    this->current_vm_file = "";  // Initialize the new member
    this->output_file.open(output_file);
    if (!this->output_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + file_name);
    }
    std::cout << "CodeWriter initialized with: " << file_name << std::endl;
} 

void CodeWriter::setCurrentVMFile(std::string vmFileName) {
    std::filesystem::path p(vmFileName);
    this->current_vm_file = p.stem().string();
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
    writePushPop(C_POP, "temp", 1); // pop to @R6 (TEMP[1]) - second operand
    writePushPop(C_POP, "temp", 0); // pop to @R5 (TEMP[0]) - first operand
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

    output_file << "@R5" << std::endl  // first value
                << "D=M" << std::endl
                << "@R6" << std::endl  // second value
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
    writeLabel(true_label);
    output_file << "@SP" << std::endl
                << "A=M" << std::endl
                << "M=-1" << std::endl;
    // End
    writeLabel(end_label);
    output_file << "@SP" << std::endl
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
        output_file << "@" << current_vm_file << "." << index << std::endl // set A reg to static variable current_vm_file.index
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
                    << "@" << current_vm_file << "." << index << std::endl // set A reg to static variable current_vm_file.index
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

void CodeWriter::writeLabel(std::string label) {
    if (isdigit(label[0])) {
        throw std::runtime_error("Label name incorrectly began with a digit");
    } else {
        output_file << "// label " << label << std::endl
                    << "(" << label << ")" << std::endl;
    }
}

void CodeWriter::writeGoto(std::string label) {
    output_file << "// goto " << label << std::endl
                << "@" << label << std::endl
                << "0;JMP" << std::endl;
}

void CodeWriter::writeIf(std::string label) {
    output_file << "// if goto " << label << std::endl
                << "@SP" << std::endl
                << "AM=M-1" << std::endl // decrement SP and set A reg to new SP and M reg to top of stack
                << "D=M" << std::endl // set D reg to value at top of stack
                << "@" << label << std::endl
                << "D;JNE" << std::endl; // jump if D reg does not equal 0
}

void CodeWriter::writeFunction(std::string functionName, int nVars) {
    current_function = functionName;
    output_file << "// function " << functionName << " " << nVars << std::endl;
    writeLabel(functionName);

    // initialize local variables to 0
    for (int i = 0; i < nVars; i++) {
        writePushPop(C_PUSH, "constant", 0); 
    }
}

void CodeWriter::writeCall(std::string functionName, int nArgs) {
    std::string returnLabel;
    if (current_function.empty()) {
        returnLabel = functionName + "$ret." + std::to_string(return_counter++);
    } else {
        returnLabel = current_function + "$ret." + std::to_string(return_counter++);
    }

    // Push return address
    output_file << "@" << returnLabel << std::endl
                << "D=A" << std::endl
                << "@SP" << std::endl
                << "A=M" << std::endl
                << "M=D" << std::endl
                << "@SP" << std::endl
                << "M=M+1" << std::endl;

    // Push LCL
    output_file << "@LCL" << std::endl
                << "D=M" << std::endl
                << "@SP" << std::endl
                << "A=M" << std::endl
                << "M=D" << std::endl
                << "@SP" << std::endl
                << "M=M+1" << std::endl;

    // Push ARG
    output_file << "@ARG" << std::endl
                << "D=M" << std::endl
                << "@SP" << std::endl
                << "A=M" << std::endl
                << "M=D" << std::endl
                << "@SP" << std::endl
                << "M=M+1" << std::endl;

    // Push THIS
    output_file << "@THIS" << std::endl
                << "D=M" << std::endl
                << "@SP" << std::endl
                << "A=M" << std::endl
                << "M=D" << std::endl
                << "@SP" << std::endl
                << "M=M+1" << std::endl;

    // Push THAT
    output_file << "@THAT" << std::endl
                << "D=M" << std::endl
                << "@SP" << std::endl
                << "A=M" << std::endl
                << "M=D" << std::endl
                << "@SP" << std::endl
                << "M=M+1" << std::endl;

    // Reposition ARG (SP-5-nArgs)
    output_file << "@SP" << std::endl
                << "D=M" << std::endl
                << "@5" << std::endl
                << "D=D-A" << std::endl
                << "@" << nArgs << std::endl
                << "D=D-A" << std::endl
                << "@ARG" << std::endl
                << "M=D" << std::endl;

    // Reposition LCL (LCL = SP)
    output_file << "@SP" << std::endl
                << "D=M" << std::endl
                << "@LCL" << std::endl
                << "M=D" << std::endl;

    // Jump to function
    writeGoto(functionName);
    // Write return label
    writeLabel(returnLabel);
}

void CodeWriter::writeReturn() {
    // FRAME = LCL
    output_file << "@LCL" << std::endl
                << "D=M" << std::endl
                << "@R13" << std::endl  // R13 = FRAME
                << "M=D" << std::endl;

    // RET = *(FRAME-5)
    output_file << "@5" << std::endl
                << "A=D-A" << std::endl 
                << "D=M" << std::endl
                << "@R14" << std::endl  // R14 = RET
                << "M=D" << std::endl;

    // *ARG = pop()
    output_file << "@SP" << std::endl
                << "AM=M-1" << std::endl
                << "D=M" << std::endl
                << "@ARG" << std::endl
                << "A=M" << std::endl
                << "M=D" << std::endl;

    // SP = ARG+1
    output_file << "@ARG" << std::endl
                << "D=M+1" << std::endl
                << "@SP" << std::endl
                << "M=D" << std::endl;

    // THAT = *(FRAME-1)
    output_file << "@R13" << std::endl
                << "D=M" << std::endl 
                << "@1" << std::endl
                << "A=D-A" << std::endl
                << "D=M" << std::endl
                << "@THAT" << std::endl
                << "M=D" << std::endl;

    // THIS = *(FRAME-2)
    output_file << "@R13" << std::endl
                << "D=M" << std::endl 
                << "@2" << std::endl
                << "A=D-A" << std::endl
                << "D=M" << std::endl
                << "@THIS" << std::endl
                << "M=D" << std::endl;

    // ARG = *(FRAME-3)
    output_file << "@R13" << std::endl
                << "D=M" << std::endl 
                << "@3" << std::endl
                << "A=D-A" << std::endl
                << "D=M" << std::endl
                << "@ARG" << std::endl
                << "M=D" << std::endl;

    // LCL = *(FRAME-4)
    output_file << "@R13" << std::endl
                << "D=M" << std::endl 
                << "@4" << std::endl
                << "A=D-A" << std::endl
                << "D=M" << std::endl
                << "@LCL" << std::endl
                << "M=D" << std::endl;

    // goto RET
    output_file << "@R14" << std::endl
                << "A=M" << std::endl
                << "0;JMP" << std::endl;
}

void CodeWriter::writeInit() {
    output_file << "// Bootstrap code" << std::endl
                << "@256" << std::endl
                << "D=A" << std::endl
                << "@SP" << std::endl
                << "M=D" << std::endl;
    writeCall("Sys.init", 0);
}

void CodeWriter::close() {
    try {
        this->output_file.close();
        std::cout << "Closed file: " << file_name << std::endl;
    } catch (const std::ios_base::failure& e) {
        throw std::runtime_error("Failed to close file: " + file_name + ". Error: " + e.what());
    }
}