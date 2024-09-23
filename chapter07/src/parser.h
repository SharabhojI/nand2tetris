#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

class Parser {
public:
    enum CommandType { C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL };

    Parser(std::string input_file);
    bool hasMoreLines();
    void advance();
    CommandType commandType();
    std::string arg1();
    int arg2();
private:
    std::ifstream input_file;
    std::string current_cmd;
    CommandType current_cmd_type;
};

#endif // PARSER_H