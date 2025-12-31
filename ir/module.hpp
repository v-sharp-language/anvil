#pragma once

#include <ir/function.hpp>
#include <ir/global.hpp>

namespace anvil::ir
{

    class Module
    {
    public:
        explicit Module(std::string name)
            : name_(std::move(name)) {}

        const std::string &name() const { return name_; }

        void addGlobal(Value *g)
        {
            globals_.push_back(g);
        }

        GlobalVariable *createStringLiteral(Context &ctx, const std::string &str)
        {
            static unsigned stringId = 0;

            Type *i8 = ctx.getInt8Ty();
            Type *arrayTy = ctx.getArrayType(i8, str.size() + 1);
            Type *ptrTy = ctx.getPointerType(arrayTy);
            ConstantString *cstr = new ConstantString(arrayTy, str);
            GlobalVariable *gv = new GlobalVariable(ptrTy, ".str." + std::to_string(stringId++), cstr);
            addGlobal(gv);
            return gv;
        }

        void addFunction(Function *fn)
        {
            functions_.push_back(fn);
        }

        auto globals_begin() const { return globals_.begin(); }
        auto globals_end() const { return globals_.end(); }
        size_t global_size() const { return globals_.size(); }
        bool global_empty() const { return globals_.empty(); }

        auto functions_begin() const { return functions_.begin(); }
        auto functions_end() const { return functions_.end(); }
        size_t function_size() const { return functions_.size(); }
        bool function_empty() const { return functions_.empty(); }

        void setTargetTriple(std::string tt) { targetTriple_ = std::move(tt); }
        const std::string &targetTriple() const { return targetTriple_; }

        void setDataLayout(std::string dl) { dataLayout_ = std::move(dl); }
        const std::string &dataLayout() const { return dataLayout_; }

        void print(std::ostream &os) const
        {
            os << "; ModuleID = '" << name_ << "'\n";
            if (!targetTriple_.empty())
                os << "target triple = \"" << targetTriple_ << "\"\n";
            if (!dataLayout_.empty())
                os << "target datalayout = \"" << dataLayout_ << "\"\n";

            os << "\n";

            for (Value *g : globals_)
            {
                g->print(os);
                os << "\n";
            }

            if (!globals_.empty())
                os << "\n";

            for (Function *fn : functions_)
            {
                fn->print(os);
                os << "\n";
            }
        }

    private:
        std::string name_;
        std::vector<Value *> globals_;
        std::vector<Function *> functions_;

        std::string targetTriple_;
        std::string dataLayout_;
    };
}
