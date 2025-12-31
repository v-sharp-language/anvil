#pragma once

#include <vector>
#include <ir/instruction.hpp>
#include <ir/basic_block.hpp>
#include <ir/context.hpp>

namespace anvil::ir
{

    class IRBuilder
    {
    public:
        IRBuilder(Context *ctx, BasicBlock *bb)
            : ctx_(ctx), block_(bb) {}

        Instruction *CreateAdd(Value *lhs, Value *rhs)
        {
            Instruction *inst = new Instruction(lhs->getType(), Instruction::Opcode::Add, {lhs, rhs});
            block_->addInstruction(inst);
            return inst;
        }

        Instruction *CreateRet(Value *val)
        {
            Instruction *inst = new Instruction(val->getType(), Instruction::Opcode::Ret, {val});
            block_->addInstruction(inst);
            return inst;
        }

        Instruction *CreateGEP(Value *base, const std::vector<Value *> &indices)
        {
            std::vector<Value *> ops;
            ops.push_back(base);
            ops.insert(ops.end(), indices.begin(), indices.end());
            Type *elemTy = base->getType()->getElementType();
            Type *ptrTy = ctx_->getPointerType(elemTy);
            Instruction *inst = new Instruction(ptrTy, Instruction::Opcode::GetElementPtr, ops);
            block_->addInstruction(inst);
            return inst;
        }

    private:
        Context *ctx_;
        BasicBlock *block_;
    };

}