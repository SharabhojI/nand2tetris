#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>

class SymbolTable {
private:
    std::unordered_map<std::string, int> table;
public:
    SymbolTable();
    void addEntry(const std::string& symbol, int address);
    bool contains(const std::string& symbol) const;
    int getAddress(const std::string& symbol) const;
};


#endif // SYMBOL_TABLE_H