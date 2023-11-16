#pragma once

#include <string>
#include <cstdint>
#include <vector>

namespace rbrown::m68000 {

class Instruction {
public:
    Instruction() : words{} {}
    auto AppendWord(uint16_t v) { words.push_back(v); }
    [[nodiscard]] const auto& GetWords() const { return words; }
private:
    std::vector<uint16_t> words;
};

bool Assemble(const std::string&, Instruction&);

}