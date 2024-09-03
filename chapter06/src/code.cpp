#include "code.h"
#include <stdexcept>
#include <unordered_map>
#include <iostream>

std::string Code::dest(const std::string& dest_mnemonic) {
    std::cout << "Processing dest mnemonic: " << dest_mnemonic << std::endl;

    static const std::unordered_map<std::string, std::string> dest_table = {
        {"null", "000"}, // value not stored
        {"M", "001"},    // stored in RAM[A]
        {"D", "010"},    // stored in D register (reg)
        {"MD", "011"},   // stored in D reg and RAM[A]
        {"A", "100"},    // stored in A reg
        {"AM", "101"},   // stored in A reg and RAM[A]
        {"AD", "110"},   // stored in A reg and D reg
        {"AMD", "111"}   // stored in A reg, D reg, and RAM[A]
    };

    auto it = dest_table.find(dest_mnemonic.empty() ? "null" : dest_mnemonic);
    if (it != dest_table.end()) {
        return it->second;
    } else {
        throw std::runtime_error("unknown dest mnemonic encountered: " + dest_mnemonic);
    }
}

std::string Code::comp(const std::string& comp_mnemonic) {
    std::cout << "Processing comp mnemonic: " << comp_mnemonic << std::endl;

    static const std::unordered_map<std::string, std::string> comp_table = {
        {"0", "0101010"},
        {"1", "0111111"},
        {"-1", "0111010"},
        {"D", "0001100"},
        {"A", "0110000"},
        {"!D", "0001101"},
        {"!A", "0110001"},
        {"-D", "0001111"},
        {"-A", "0110011"},
        {"D+1", "0011111"},
        {"A+1", "0110111"},
        {"D-1", "0001110"},
        {"A-1", "0110010"},
        {"D+A", "0000010"},
        {"D-A", "0010011"},
        {"A-D", "0000111"},
        {"D&A", "0000000"},
        {"D|A", "0010101"},
        {"M", "1110000"},
        {"!M", "1110001"},
        {"-M", "1110011"},
        {"M+1", "1110111"},
        {"M-1", "1110010"},
        {"D+M", "1000010"},
        {"D-M", "1010011"},
        {"M-D", "1000111"},
        {"D&M", "1000000"},
        {"D|M", "1010101"}
    };

    auto it = comp_table.find(comp_mnemonic.empty() ? "null" : comp_mnemonic);
    if (it != comp_table.end()) {
        return it->second;
    } else {
        throw std::runtime_error("unknown comp mnemonic encountered: " + comp_mnemonic);
    }
}

std::string Code::jump(const std::string& jump_mnemonic) {
    std::cout << "Processing jump mnemonic: " << jump_mnemonic << std::endl;

    static const std::unordered_map<std::string, std::string> jump_table = {
        {"null", "000"}, // no jump
        {"JGT", "001"},  // if comp > 0, jump
        {"JEQ", "010"},  // if comp = 0, jump
        {"JGE", "011"},  // if comp >= 0, jump
        {"JLT", "100"},  // if comp < 0, jump
        {"JNE", "101"},  // if comp != 0, jump
        {"JLE", "110"},  // if comp <= 0, jump
        {"JMP", "111"}   // unconditional jump
    };

    auto it = jump_table.find(jump_mnemonic.empty() ? "null" : jump_mnemonic);
    if (it != jump_table.end()) {
        return it->second;
    } else {
        throw std::runtime_error("unknown jump mnemonic encountered: " + jump_mnemonic);
    }
}