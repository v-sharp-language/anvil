#pragma once

#include <string>
#include <ir/type.hpp>

namespace anvil::ir
{
    class Value
    {
    public:
        explicit Value(Type *type, std::string name = "")
            : type_(type), name_(std::move(name)) {}

        virtual ~Value() = default;

        Type *getType() const { return type_; }
        const std::string &getName() const { return name_; }

        virtual void print(std::ostream &os) const = 0;

        virtual void printAsOperand(std::ostream &os) const
        {
            print(os);
        }

    protected:
        Type *type_;
        std::string name_;
    };
}