#pragma once

#include <ir/value.hpp>
#include <ir/constants.hpp>

namespace anvil::ir
{
    class GlobalVariable : public Value
    {
    public:
        GlobalVariable(Type *ty, std::string name, Constant *init, bool isConstant = true)
            : Value(ty, std::move(name)), initializer_(init), isConstant_(isConstant) {}

        void print(std::ostream &os) const override
        {
            os << "@" << name_ << " = ";

            if (isConstant_)
                os << "private unnamed_addr constant ";
            else
                os << "global ";

            type_->getElementType()->print(os);
            os << " ";
            initializer_->print(os);
        }

        void printAsOperand(std::ostream &os) const override
        {
            os << "@" << name_;
        }

    private:
        Constant *initializer_;
        bool isConstant_;
    };
}