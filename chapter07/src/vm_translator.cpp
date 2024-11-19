#include "parser.h"
#include "code_writer.h"
#include <string>
#include <iostream>
#include <filesystem>

void translate(const std::string& input_file, std::string output_file) {
    Parser parser(input_file);
    CodeWriter codeWriter(output_file);

    while (parser.hasMoreLines()) {
        parser.advance();

        switch (parser.commandType()) {
            case Parser::C_ARITHMETIC:
                codeWriter.writeArithmetic(parser.arg1());
                break;
            case Parser::C_PUSH:
            case Parser::C_POP:
                codeWriter.writePushPop(parser.commandType() == Parser::C_PUSH ? CodeWriter::C_PUSH : CodeWriter::C_POP, parser.arg1(), parser.arg2());
                break;
            default:
                throw std::runtime_error("Unknown or unsupported command encountered");
        }
    }
    codeWriter.close();
}

static void _writeInfiniteLoop(std::ofstream& output_file) {
    output_file << "(END_PROGRAM)" << std::endl
                << "@END_PROGRAM" << std::endl
                << "0;JMP" << std::endl;
}

int main(int argc, char* argv[]) {
    // check if correct number of arguments were passed from command line
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <VM_file.vm>" << std::endl;
        return 1;
    }

    // check if file has correct '.vm' extension
    std::filesystem::path file_name(argv[1]);
    if (file_name.extension() != ".vm") {
        std::cerr << "Error: file must have .vm extension" << std::endl;
        return 1; 
    }
    
    // if input file has parent path, set it as the dir path, else use path of current working dir
    std::filesystem::path dir_path = file_name.has_parent_path() ? file_name.parent_path() : std::filesystem::current_path();

    // concatenate the '.asm' ext to the stem (raw filename) and append it to the dir path
    std::filesystem::path output_path = dir_path / file_name.stem().concat(".asm");

    try {
        translate(file_name.string(), output_path.string());

        // write infinite loop after translation process    
        std::ofstream output_file(output_path, std::ios::app); // open output file in append mode
        if(!output_file.is_open()) {
            throw std::runtime_error("Error: unable to open output file to append infinite loop");
        }
        _writeInfiniteLoop(output_file);

        // close output file and exit
        output_file.close();
        std::cout << "Translation completed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error during translation: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}