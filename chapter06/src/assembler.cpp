#include "parser.h"
#include "code.h"
#include "symbol_table.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <bitset>

bool isNumeric(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

std::string intToBinary(int value) {
    return std::bitset<16>(value).to_string();
}

void initializeSymbolTable(SymbolTable& table) {
    for (int i = 0; i < 16; i++) {
        std::string symbol = "R" + std::to_string(i);
        table.addEntry(symbol, i);
    }
    table.addEntry("SP", 0);
    table.addEntry("LCL", 1);
    table.addEntry("ARG", 2);
    table.addEntry("THIS", 3);
    table.addEntry("THAT", 4);
    table.addEntry("SCREEN", 16384);
    table.addEntry("KBD", 24576);
}

void firstPass(Parser& parser, SymbolTable& table) {
    int rom_address = 0;
    std::cout << "Starting first pass..." << std::endl;
    while (parser.hasMoreLines()) {
        parser.advance();
        if (parser.instructionType() == Parser::InstructionType::EOF_REACHED) {
            break;
        }
        if (parser.instructionType() != Parser::InstructionType::L_INSTRUCTION) {
            rom_address++;
        } else {
            std::string symbol = parser.symbol();
            table.addEntry(symbol, rom_address);
            std::cout << "Added label: " << symbol << " at address: " << rom_address << std::endl;
        }
    }
    std::cout << "First pass completed." << std::endl;
}

void secondPass(Parser& parser, SymbolTable& table, Code& code, std::ofstream& output_file) {
    int variable_address = 16;
    std::cout << "Starting second pass..." << std::endl;
    while (parser.hasMoreLines()) {
        parser.advance();
        if (parser.instructionType() == Parser::InstructionType::EOF_REACHED) {
            break;
        }
        if (parser.instructionType() == Parser::InstructionType::A_INSTRUCTION) {
            std::string symbol = parser.symbol();
            int address;
            if (isNumeric(symbol)) {
                address = std::stoi(symbol);
            } else if (table.contains(symbol)) {
                address = table.getAddress(symbol);
            } else {
                address = variable_address;
                table.addEntry(symbol, address);
                variable_address++;
                std::cout << "Added variable: " << symbol << " at address: " << address << std::endl;
            }
            std::string binary = intToBinary(address);
            std::cout << "Writing A-instruction: " << binary << std::endl;
            output_file << binary << std::endl;
            
        } else if (parser.instructionType() == Parser::InstructionType::C_INSTRUCTION) {
            std::string dest = code.dest(parser.dest());
            std::string comp = code.comp(parser.comp());
            std::string jump = code.jump(parser.jump());
            
            std::string c_inst = "111" + comp + dest + jump;
            std::cout << "Writing C-instruction: " << c_inst << std::endl;
            output_file << c_inst << std::endl;
        }
    }
    std::cout << "Second pass completed." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <assembly_file.asm>" << std::endl;
        return 1;
    }

    // get input file path and check file for '.asm' extension
    std::filesystem::path file_path(argv[1]); 
    if(file_path.extension() != ".asm") {
        std::cerr << "Error: file must have .asm extension" << std::endl;
        return 1; 
    }

    // if input file has parent path, set it as the dir path, else use path of current working dir
    std::filesystem::path dir_path = file_path.has_parent_path() ? file_path.parent_path() : std::filesystem::current_path();

    // concatenate the '.hack' ext to the stem (raw filename) and append it to the dir path
    std::filesystem::path output_path = dir_path / file_path.stem().concat(".hack");

    // initialize symbol table
    SymbolTable table;
    initializeSymbolTable(table);
    
    // First pass
    Parser parser(file_path.string());
    firstPass(parser, table);

    // Second pass
    parser = Parser(file_path.string());
    std::ofstream output_file(output_path.string());
    if(!output_file.is_open()) {
        std::cerr << "Error: unable to open output file" << std::endl;
        return 1;
    }
    Code code;
    secondPass(parser, table, code, output_file);

    // close file and exit
    output_file.close();
    std::cout << "Assembly completed successfully. Output written to " << output_path << std::endl;
    return 0;
}