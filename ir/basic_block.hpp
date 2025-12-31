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

        void print(std::ostream &os) const
        {
            os << name_ << ":\n";
            for (Instruction *inst : instructions_)
            {
                os << "  ";
                inst->print(os);
                os << "\n";
            }
        }

    private:
        std::string name_;
        std::vector<Instruction *> instructions_;
    };
}
