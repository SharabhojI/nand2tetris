#ifndef COMPILATION_ENGINE_H
#define COMPILATION_ENGINE_H
#include <fstream>

class CompilationEngine {
private:
    std::ifstream input_file;
    std::ofstream output_file;

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