#include "jack_tokenizer.h"
#include <iostream>
#include <algorithm>

const std::set<std::string> JackTokenizer::keywords = {
    "class", "constructor", "function", "method", "field", "static", "var",
    "int", "char", "boolean", "void", "true", "false", "null", "this",
    "let", "do", "if", "else", "while", "return"
};

const std::set<char> JackTokenizer::symbols = {
    '{', '}', '(', ')', '[', ']', '.', ',', ';', '+', 
    '-', '*', '/', '&', '|', '<', '>', '=', '~'
};

JackTokenizer::JackTokenizer(std::string input_file) {
    this->input_file.open(input_file);
    if (!this->input_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + input_file);
    }
    currentPosition = 0;
    // Read first line to get started
    if (!getline(this->input_file, currentLine)) {
        currentLine = "";
    }
}

bool JackTokenizer::hasMoreTokens() {
    skipWhitespace();
    return !input_file.eof() || currentPosition < currentLine.length();
}

void JackTokenizer::skipWhitespace() {
    // Skip whitespace in current line
    while (currentPosition < currentLine.length() && 
           std::isspace(currentLine[currentPosition])) {
        currentPosition++;
    }
    
    // If we've reached end of line, get next line
    while (currentPosition >= currentLine.length()) {
        if (!getline(input_file, currentLine)) {
            currentLine = "";
            return;
        }
        currentPosition = 0;
        // Skip whitespace in new line
        while (currentPosition < currentLine.length() && 
               std::isspace(currentLine[currentPosition])) {
            currentPosition++;
        }
    }
}

void JackTokenizer::skipComments() {
    while (true) {
        // Skip whitespace first
        skipWhitespace();
        
        // Check for empty line
        if (currentPosition >= currentLine.length()) {
            return;
        }

        // Check for single line comment
        if (currentPosition + 1 < currentLine.length() && 
            currentLine[currentPosition] == '/' && 
            currentLine[currentPosition + 1] == '/') {
            if (!getline(input_file, currentLine)) {
                currentLine = "";
                return;
            }
            currentPosition = 0;
            continue;
        }

        // Check for multi-line comment
        if (currentPosition + 1 < currentLine.length() && 
            currentLine[currentPosition] == '/' && 
            currentLine[currentPosition + 1] == '*') {
            // Find end of multi-line comment
            currentPosition += 2;
            bool found = false;
            while (!found) {
                while (currentPosition < currentLine.length() - 1) {
                    if (currentLine[currentPosition] == '*' && 
                        currentLine[currentPosition + 1] == '/') {
                        currentPosition += 2;
                        found = true;
                        break;
                    }
                    currentPosition++;
                }
                if (!found) {
                    if (!getline(input_file, currentLine)) {
                        throw std::runtime_error("Unterminated multi-line comment");
                    }
                    currentPosition = 0;
                }
            }
            continue;
        }        
        break;
    }
}

void JackTokenizer::advance() {
    if (!hasMoreTokens()) {
        return;
    }

    skipWhitespace();
    skipComments();

    if (currentPosition >= currentLine.length()) {
        return;
    }

    char currentChar = currentLine[currentPosition];

    // Check if the current token is a symbol
    if (symbols.find(currentChar) != symbols.end()) {
        currentToken = std::string(1, currentChar);
        currentTokenType = TokenType::SYMBOL;
        currentPosition++;
    }
    // Check if the current token is an integer constant
    else if (std::isdigit(currentChar)) {
        size_t start = currentPosition;
        while (currentPosition < currentLine.length() && std::isdigit(currentLine[currentPosition])) {
            currentPosition++;
        }
        currentToken = currentLine.substr(start, currentPosition - start);
        currentTokenType = TokenType::INT_CONST;
    }
    // Check if the current token is a string constant
    else if (currentChar == '"') {
        currentPosition++; // Skip the opening quote
        size_t start = currentPosition;
        while (currentPosition < currentLine.length() && currentLine[currentPosition] != '"') {
            currentPosition++;
        }
        currentToken = currentLine.substr(start, currentPosition - start);
        currentTokenType = TokenType::STRING_CONST;
        currentPosition++; // Skip the closing quote
    }
    // Check if the current token is a keyword or identifier
    else if (std::isalpha(currentChar) || currentChar == '_') {
        size_t start = currentPosition;
        while (currentPosition < currentLine.length() && 
               (std::isalnum(currentLine[currentPosition]) || currentLine[currentPosition] == '_')) {
            currentPosition++;
        }
        currentToken = currentLine.substr(start, currentPosition - start);
        if (keywords.find(currentToken) != keywords.end()) {
            currentTokenType = TokenType::KEYWORD;
        } else {
            currentTokenType = TokenType::IDENTIFIER;
        }
    }
}

JackTokenizer::TokenType JackTokenizer::tokenType() {
    return currentTokenType;
}

JackTokenizer::KeyWord JackTokenizer::keyWord() {
    if (currentTokenType != TokenType::KEYWORD) {
        throw std::runtime_error("Current token is not a keyword");
    }
    if (currentToken == "class") return KeyWord::CLASS;
    if (currentToken == "constructor") return KeyWord::CONSTRUCTOR;
    if (currentToken == "function") return KeyWord::FUNCTION;
    if (currentToken == "method") return KeyWord::METHOD;
    if (currentToken == "field") return KeyWord::FIELD;
    if (currentToken == "static") return KeyWord::STATIC;
    if (currentToken == "var") return KeyWord::VAR;
    if (currentToken == "int") return KeyWord::INT;
    if (currentToken == "char") return KeyWord::CHAR;
    if (currentToken == "boolean") return KeyWord::BOOLEAN;
    if (currentToken == "void") return KeyWord::VOID;
    if (currentToken == "true") return KeyWord::TRUE;
    if (currentToken == "false") return KeyWord::FALSE;
    if (currentToken == "null") return KeyWord::NULL_KEY;
    if (currentToken == "this") return KeyWord::THIS;
    if (currentToken == "let") return KeyWord::LET;
    if (currentToken == "do") return KeyWord::DO;
    if (currentToken == "if") return KeyWord::IF;
    if (currentToken == "else") return KeyWord::ELSE;
    if (currentToken == "while") return KeyWord::WHILE;
    if (currentToken == "return") return KeyWord::RETURN;
    throw std::runtime_error("Invalid keyword: " + currentToken);
}

char JackTokenizer::symbol() {
    if (currentTokenType != TokenType::SYMBOL) {
        throw std::runtime_error("Current token is not a symbol");
    }
    return currentToken[0];
}

std::string JackTokenizer::identifier() {
    if (currentTokenType != TokenType::IDENTIFIER) {
        throw std::runtime_error("Current token is not an identifier");
    }
    return currentToken;
}

int JackTokenizer::intVal() {
    if (currentTokenType != TokenType::INT_CONST) {
        throw std::runtime_error("Current token is not an integer constant");
    }
    return std::stoi(currentToken);
}

std::string JackTokenizer::stringVal() {
    if (currentTokenType != TokenType::STRING_CONST) {
        throw std::runtime_error("Current token is not a string constant");
    }
    // Remove the opening and closing quotes
    return currentToken.substr(1, currentToken.length() - 2);
}