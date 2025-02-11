#ifndef JACK_TOKENIZER_H
#define JACK_TOKENIZER_H
#include <string>
#include <fstream>

class JackTokenizer {
private:
    std::ifstream input_file;

public:
    JackTokenizer(std::string input_file);
    bool hasMoreTokens();
    void advance();
    std::string tokenType();
    std::string keyWord();
    char symbol();
    std::string identifier();
    int intVal();
    std::string stringVal();
};

#endif