#ifndef CODE_WRITER_H
#define CODE_WRITER_H
#include <string>
#include <fstream>

class CodeWriter {
private:
    int label_num;
    int return_counter;
    std::string current_function;
    std::string file_name;
    std::string current_vm_file;
    std::ofstream output_file;
    void writeAdd();
    void writeSub();
    void writeNeg();
    void writeCompare(std::string comparisonType);
    void writeAnd();
    void writeOr();
    void writeNot();
    void writePush(std::string segment, int index);
    void writePop(std::string segment, int index);

public:
    enum CommandType { C_PUSH, C_POP };
    CodeWriter(std::string output_file);
    void setCurrentVMFile(std::string output_file);
    void writeArithmetic(std::string command);
    void writePushPop(CommandType command, std::string segment, int index);
    void writeLabel(std::string label);
    void writeGoto(std::string label);
    void writeIf(std::string label);
    void writeFunction(std::string functionName, int nVars);
    void writeCall(std::string functionName, int nArgs);
    void writeReturn();
    void writeInit();
    void close();
};

#endif