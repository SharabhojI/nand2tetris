#ifndef COMPILATION_ENGINE_H
#define COMPILATION_ENGINE_H
#include <fstream>
#include <string>
#include "jack_tokenizer.h"

class CompilationEngine {
private:
    JackTokenizer tokenizer;
    std::ofstream output_file;
    int indentLevel;
    
    // Helper methods
    void writeToken();
    void writeXMLTag(const std::string& tag, bool isClosing);
    void advance();
    bool isOperator(char symbol);
    void writeIndentation();

public:
    CompilationEngine(std::string input_file, std::string output_file);
    void compileClass();
    void compileClassVarDec();
    void compileSubroutine();
    void compileParameterList();
    void compileSubroutineBody();
    void compileVarDec();
    void compileStatements();
    void compileLet();    
    void compileIf();
    void compileWhile();
    void compileDo();
    void compileReturn();
    void compileExpression();
    void compileTerm();
    int compileExpressionList();
};

#endif