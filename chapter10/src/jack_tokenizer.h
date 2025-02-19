#ifndef JACK_TOKENIZER_H
#define JACK_TOKENIZER_H
#include <string>
#include <fstream>
#include <map>
#include <set>

class JackTokenizer {
public:
    enum TokenType {
        KEYWORD,
        SYMBOL,
        IDENTIFIER, 
        INT_CONST,
        STRING_CONST
    };

    enum KeyWord {
        CLASS,
        METHOD,
        FUNCTION,
        CONSTRUCTOR,
        INT,
        BOOLEAN,
        CHAR,
        VOID,
        VAR,
        STATIC,
        FIELD,
        LET,
        DO,
        IF,
        ELSE,
        WHILE,
        RETURN,
        TRUE,
        FALSE,
        NULL_KEY,
        THIS
    };

    JackTokenizer(std::string input_file);
    bool hasMoreTokens();
    void advance();
    TokenType tokenType();
    KeyWord keyWord();
    char symbol();
    std::string identifier();
    int intVal();
    std::string stringVal();
    
private:
    std::ifstream input_file;
    std::string currentToken;
    TokenType currentTokenType;
    std::string currentLine;
    size_t currentPosition;
    
    // Constants and lookup tables
    static const std::set<std::string> keywords;
    static const std::set<char> symbols;
    
    // Helper methods
    void skipWhitespace();
    void skipComments();
    bool isSymbol(char c);
    bool isDigit(char c); 
};

#endif