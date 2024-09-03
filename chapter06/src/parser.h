#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

class Parser {
public:
    enum InstructionType { A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, EOF_REACHED };

    Parser(std::string input_file);
    bool hasMoreLines(); 
    void advance();
    InstructionType instructionType();
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();

private:
    InstructionType current_inst_type;
    std::ifstream input_file;
    std::string current_inst;
    bool eof_reached = false;
};

#endif // PARSER_H