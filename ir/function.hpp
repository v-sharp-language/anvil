#pragma once

#include <ir/basic_block.hpp>
#include <ir/type.hpp>
#include <ir/value.hpp>
#include <helpers/helpers.hpp>

namespace anvil::ir
{

    class Function : public Value
    {
    public:
        Function(Type *retType, std::string name, const std::vector<Type *> &params = {})
            : Value(nullptr, std::move(name)), retType_(retType), paramTypes_(params) {}

        void addBlock(BasicBlock *bb) { blocks_.push_back(bb); }

        void print(std::ostream &os) const override
        {
            os << "define ";
            retType_->print(os);
            os << global(name_) << "(";
            for (size_t i = 0; i < paramTypes_.size(); ++i)
            {
                if (i > 0)
                    os << ", ";
                paramTypes_[i]->print(os);
            }
            os << ") {\n";
            for (BasicBlock *bb : blocks_)
            {
                bb->print(os);
                os << "\n";
            }
            os << "}\n";
        }

    private:
        Type *retType_;
        std::vector<Type *> paramTypes_;
        std::vector<BasicBlock *> blocks_;
    };
}
