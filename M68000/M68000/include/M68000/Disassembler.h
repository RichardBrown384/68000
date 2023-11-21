#pragma once

#include <cstdint>
#include <string>

namespace rbrown::m68000 {

class InstructionStream {
public:
    virtual ~InstructionStream() = default;
    virtual auto ReadWord() -> uint16_t = 0;
};

std::string Disassemble(InstructionStream&);

}