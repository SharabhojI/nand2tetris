#include "jack_tokenizer.h"
#include "compilation_engine.h"
#include <iostream>
#include <filesystem>

void processFile(const std::filesystem::path& input_path) {
    // generate output file name and path by replacing .jack extension with .xml
    std::filesystem::path output_path = input_path.parent_path() / input_path.stem().concat(".xml");

    // create tokenizer and compilation engine objects
    JackTokenizer tokenizer(input_path.string());
    CompilationEngine compilationEngine(input_path.string(), output_path.string());

    // start compilation process
    compilationEngine.compileClass();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input .jack file or directory>" << std::endl;
        return 1;
    }

    std::filesystem::path input_path(argv[1]);

    if (std::filesystem::is_regular_file(input_path)) {
        if (input_path.extension() != ".jack") {
            std::cerr << "Error: input file must have .jack extension" << std::endl;
            return 1;
        }
        processFile(input_path);
    } else if (std::filesystem::is_directory(input_path)) {
        for (const auto& file : std::filesystem::directory_iterator(input_path)) {
            if (file.path().extension() == ".jack") {
                processFile(file.path());
            }
        }
    } else {
        std::cerr << "Invalid input file/directory" << std::endl;
        return 1;
    }
}
