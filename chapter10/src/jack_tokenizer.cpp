#include "jack_tokenizer.h"
#include <iostream>

JackTokenizer::JackTokenizer(std::string input_file) {
    this->input_file.open(input_file);
    if (!this->input_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + input_file);
    }
    std::cout << "JackTokenizer initialized with: " << input_file << std::endl;
}

bool JackTokenizer::hasMoreTokens() {
    return !this->input_file.eof();
}

void JackTokenizer::advance() {
    if (!hasMoreTokens()) {
        return;
    }
    std::string line;
    std::getline(this->input_file, line);
    std::cout << "Read line: " << line << std::endl;
}

std::string JackTokenizer::tokenType() {

}

std::string JackTokenizer::keyWord() {

}

char JackTokenizer::symbol() {

}

std::string JackTokenizer::identifier() {

}

int JackTokenizer::intVal() {

}

std::string JackTokenizer::stringVal() {

}