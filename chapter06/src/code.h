#ifndef CODE_H
#define CODE_H

#include <string>

class Code {
public:
    std::string dest(const std::string& dest_mnemonic);
    std::string comp(const std::string& comp_mnemonic);
    std::string jump(const std::string& jump_mnemonic);
};

#endif // CODE_H