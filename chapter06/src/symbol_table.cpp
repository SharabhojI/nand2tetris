#include "symbol_table.h"
#include <stdexcept>

SymbolTable::SymbolTable() : table() { }

void SymbolTable::addEntry(const std::string& symbol, int address) {
    table.insert({symbol, address});
}

bool SymbolTable::contains(const std::string& symbol) const {
    return table.find(symbol) != table.end();
}

int SymbolTable::getAddress(const std::string& symbol) const {
    auto it = table.find(symbol);
    if (it != table.end()) {
        return it->second;
    } else {
        throw std::runtime_error("symbol not found");
    }
}