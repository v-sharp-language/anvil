#pragma once
#include <ostream>
#include <string>
#include <helpers/helpers.hpp>
#include <ir/value.hpp>

namespace anvil::ir
{

    class Instruction : public Value
    {
    public:
        enum class Opcode
        {
            Add,
            Sub,
            Mul,
            Div,
            Ret,
            GetElementPtr,
        };

        Instruction(Type *type, Opcode op, const std::vector<Value *> &operands = {})
            : Value(type), opcode_(op), operands_(operands), id_(nextId_++) {}

        Opcode getOpcode() const { return opcode_; }
        const std::vector<Value *> &getOperands() const { return operands_; }
        unsigned getId() const { return id_; }

        void print(std::ostream &os) const override
        {
            if (opcode_ != Opcode::Ret)
                os << local(id_) << " = ";

            std::string typeStr;
            if (type_->isIntegerTy())
                typeStr = "i" + std::to_string(type_->getBitWidth());
            else if (type_->isHalfTy())
                typeStr = "float";
            else if (type_->isFloatTy())
                typeStr = "float";
            else if (type_->isDoubleTy())
                typeStr = "double";
            else
                typeStr = "unknown";

            switch (opcode_)
            {
            case Opcode::Add:
                os << "add " << typeStr << " ";
                operands_[0]->print(os);
                os << ", ";
                operands_[1]->print(os);
                break;
            case Opcode::Sub:
                os << "sub " << typeStr << " ";
                operands_[0]->print(os);
                os << ", ";
                operands_[1]->print(os);
                break;
            case Opcode::Mul:
                os << "mul " << typeStr << " ";
                operands_[0]->print(os);
                os << ", ";
                operands_[1]->print(os);
                break;
            case Opcode::Div:
                os << "div " << typeStr << " ";
                operands_[0]->print(os);
                os << ", ";
                operands_[1]->print(os);
                break;
            case Opcode::Ret:
                os << "ret ";
                operands_[0]->getType()->print(os);
                os << " ";
                operands_[0]->printAsOperand(os);
                break;
            case Opcode::GetElementPtr:
                Type *elemTy = operands_[0]->getType()->getElementType();

                os << "getelementptr ";
                elemTy->print(os);
                os << ", ";

                operands_[0]->getType()->print(os);
                os << " ";
                operands_[0]->printAsOperand(os);

                for (size_t i = 1; i < operands_.size(); ++i)
                {
                    os << ", ";
                    operands_[i]->getType()->print(os);
                    os << " ";
                    operands_[i]->printAsOperand(os);
                }
                break;
            }
        }

        void printAsOperand(std::ostream &os) const override
        {
            os << local(id_);
        }

    private:
        Opcode opcode_;
        std::vector<Value *> operands_;
        unsigned id_;
        inline static unsigned nextId_ = 0;
    };

}