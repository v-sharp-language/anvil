#pragma once

#include <ir/basic_block.hpp>

namespace anvil::ir
{

    class Function : public Value
    {
    public:
        using Value::Value;

        void addBlock(BasicBlock *bb)
        {
            blocks_.push_back(bb);
        }

    private:
        std::vector<BasicBlock *> blocks_;
    };
}
