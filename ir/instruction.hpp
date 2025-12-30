#pragma once
#include <ostream>
#include <ir/value.hpp>

namespace anvil::ir
{

    class Instruction : public Value
    {
    public:
        enum class Opcode
        {
            Add,
            Ret
        };

        Instruction(Type *type, Opcode op)
            : Value(type), opcode_(op), id_(nextId_++) {}

        Opcode getOpcode() const { return opcode_; }
        unsigned getId() const { return id_; }

    private:
        Opcode opcode_;
        unsigned id_;
        inline static unsigned nextId_ = 0;
    };

}