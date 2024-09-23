#ifndef CODE_WRITER_H
#define CODE_WRITER_H
#include <string>
#include <fstream>

class CodeWriter {
private:
    int label_num;
    std::string file_name;
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
    void writeArithmetic(std::string command);
    void writePushPop(CommandType command, std::string segment, int index);
    void close();
};

#endif