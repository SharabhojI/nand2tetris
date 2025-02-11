#include "compilation_engine.h"
#include <iostream>

CompilationEngine::CompilationEngine(std::string input_file, std::string output_file) {
    this->input_file.open(input_file);
    if (!this->input_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + input_file);
    }
    this->output_file.open(output_file);
    if (!this->output_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + output_file);
    }
    std::cout << "CompilationEngine initialized with input file: " << input_file << " and output file: " << output_file << std::endl;
}

void CompilationEngine::compileClass() {

}

void CompilationEngine::compileClassVarDec() {

}

void CompilationEngine::compileSubroutine() {

}

void CompilationEngine::compileParameterList() {

}

void CompilationEngine::compileSubroutineBody() {

}

void CompilationEngine::compileVarDec() {

}

void CompilationEngine::compileStatements() {

}

void CompilationEngine::compileLet() {

}

void CompilationEngine::compileIf() {

}

void CompilationEngine::compileWhile() {

}

void CompilationEngine::compileDo() {

}

void CompilationEngine::compileReturn() {

}

void CompilationEngine::compileExpression() {

}

void CompilationEngine::compileTerm() {

}

int CompilationEngine::compileExpressionList() {

}