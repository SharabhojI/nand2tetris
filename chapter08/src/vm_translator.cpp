#include "parser.h"
#include "code_writer.h"
#include <string>
#include <iostream>
#include <filesystem>

// static void _writeInit(std::ofstream& output_file, CodeWriter& codeWriter) {
//     output_file << "// Bootstrap Code" << std::endl
//                 << "@256" << std::endl  // Initialize SP to 256
//                 << "D=A" << std::endl
//                 << "@SP" << std::endl
//                 << "M=D" << std::endl;
//     codeWriter.writeCall("Sys.init", 0);  // Call Sys.init
// }

static void _writeInfiniteLoop(std::ofstream& output_file) {
    output_file << "(END_PROGRAM)" << std::endl
                << "@END_PROGRAM" << std::endl
                << "0;JMP" << std::endl;
}

void processFile(Parser& parser, CodeWriter& codeWriter, const std::string& vmFileName) {
    codeWriter.setCurrentVMFile(vmFileName);
    while (parser.hasMoreLines()) {
        parser.advance();
        Parser::CommandType cmdType = parser.commandType();
        
        switch (cmdType) {
            case Parser::C_ARITHMETIC:
                codeWriter.writeArithmetic(parser.arg1());
                break;
            case Parser::C_PUSH:
            case Parser::C_POP:
                codeWriter.writePushPop(
                    parser.commandType() == Parser::C_PUSH ? CodeWriter::C_PUSH : CodeWriter::C_POP,
                    parser.arg1(),
                    parser.arg2()
                );
                break;
            case Parser::C_LABEL:
                codeWriter.writeLabel(parser.arg1());
                break;
            case Parser::C_GOTO:
                codeWriter.writeGoto(parser.arg1());
                break;
            case Parser::C_IF:
                codeWriter.writeIf(parser.arg1());
                break;
            case Parser::C_FUNCTION:
                codeWriter.writeFunction(parser.arg1(), parser.arg2());
                break;
            case Parser::C_CALL:
                codeWriter.writeCall(parser.arg1(), parser.arg2());
                break;
            case Parser::C_RETURN:
                codeWriter.writeReturn();
                break;
        }
    }
}

void translate(const std::filesystem::path& input_path, const std::filesystem::path& output_path, bool needsBootstrap) {
    std::ofstream output_file(output_path);
    if (!output_file.is_open()) {
        throw std::runtime_error("Unable to open output file: " + output_path.string());
    }

    CodeWriter codeWriter(output_path.string());
    
    if (needsBootstrap) {
        codeWriter.writeInit();
    }

    if (std::filesystem::is_regular_file(input_path)) {
        Parser parser(input_path.string());
        processFile(parser, codeWriter, input_path.string());
    } else {
        for (const auto& entry : std::filesystem::directory_iterator(input_path)) {
            if (entry.path().extension() == ".vm") {
                Parser parser(entry.path().string());
                processFile(parser, codeWriter, entry.path().string());
            }
        }
    }
    codeWriter.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input.vm or folder>" << std::endl;
        return 1;
    }

    std::filesystem::path input_path(argv[1]);
    std::filesystem::path output_path;
    
    if (std::filesystem::is_regular_file(input_path)) {
        if (input_path.extension() != ".vm") {
            std::cerr << "Error: input file must have .vm extension" << std::endl;
            return 1;
        }
        output_path = input_path.parent_path() / input_path.stem().concat(".asm");
    } else {
        output_path = input_path / input_path.filename().concat(".asm");
    }

    try {
        bool needsBootstrap = std::filesystem::is_directory(input_path) || (std::filesystem::is_regular_file(input_path) && input_path.filename() == "Sys.vm");
        translate(input_path, output_path, needsBootstrap);

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