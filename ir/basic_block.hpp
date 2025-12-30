#pragma once
#include <vector>
#include <string>
#include <ir/instruction.hpp>

namespace anvil::ir
{

    class BasicBlock
    {
    public:
        explicit BasicBlock(std::string name) : name_(name) {}

        void addInstruction(Instruction *inst) { instructions_.push_back(inst); }
    private:
        std::string name_;
        std::vector<Instruction *> instructions_;
    };

}
