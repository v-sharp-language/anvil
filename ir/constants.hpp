#pragma once

#include <vector>
#include <ir/type.hpp>
#include <ir/value.hpp>

namespace anvil::ir
{
    class Constant : public Value
    {
    public:
        using Value::Value;
    };

    class ConstantInt : public Constant
    {
    public:
        ConstantInt(Type *ty, int64_t val) : Constant(ty), value_(val) {}
        int64_t getValue() const { return value_; }

        void print(std::ostream &os) const override { os << value_; }

    private:
        int64_t value_;
    };

    class ConstantFP : public Constant
    {
    public:
        ConstantFP(Type *ty, double val) : Constant(ty), value_(val) {}
        double getValue() const { return value_; }

        void print(std::ostream &os) const override { os << value_; }

    private:
        double value_;
    };

    class ConstantString : public Constant
    {
    public:
        ConstantString(Type *arrayTy, std::string value)
            : Constant(arrayTy), value_(std::move(value)) {}

        const std::string &value() const { return value_; }

        void print(std::ostream &os) const override
        {
            os << "c\"";
            for (char c : value_)
            {
                if (c == '\n')
                    os << "\\0A";
                else if (c == '\t')
                    os << "\\09";
                else if (c == '\"')
                    os << "\\22";
                else if (c == '\\')
                    os << "\\5C";
                else
                    os << c;
            }
            os << "\\00\"";
        }

    private:
        std::string value_;
    };

    class ConstantPointerNull : public Constant
    {
    public:
        explicit ConstantPointerNull(Type *ty) : Constant(ty) {}
        void print(std::ostream &os) const override { os << "null"; }
    };

    class ConstantArray : public Constant
    {
    public:
        ConstantArray(Type *ty, const std::vector<Constant *> &elems)
            : Constant(ty), elements_(elems) {}

        void print(std::ostream &os) const override
        {
            os << "[";
            for (size_t i = 0; i < elements_.size(); ++i)
            {
                if (i)
                    os << ", ";
                elements_[i]->print(os);
            }
            os << "]";
        }

    private:
        std::vector<Constant *> elements_;
    };

    class ConstantStruct : public Constant
    {
    public:
        ConstantStruct(Type *ty, const std::vector<Constant *> &elems)
            : Constant(ty), elements_(elems) {}

        void print(std::ostream &os) const override
        {
            os << "{";
            for (size_t i = 0; i < elements_.size(); ++i)
            {
                if (i)
                    os << ", ";
                elements_[i]->print(os);
            }
            os << "}";
        }

    private:
        std::vector<Constant *> elements_;
    };

    class ConstantVector : public Constant
    {
    public:
        ConstantVector(Type *ty, const std::vector<Constant *> &elems)
            : Constant(ty), elements_(elems) {}

        void print(std::ostream &os) const override
        {
            os << "<";
            for (size_t i = 0; i < elements_.size(); ++i)
            {
                if (i)
                    os << ", ";
                elements_[i]->print(os);
            }
            os << ">";
        }

    private:
        std::vector<Constant *> elements_;
    };

    class ConstantTargetNone : public Constant
    {
    public:
        ConstantTargetNone(Type *ty) : Constant(ty) {}
        void print(std::ostream &os) const override { os << "none"; }
    };

    class ExtractElementConstantExpr : public Constant
    {
    public:
        ExtractElementConstantExpr(ConstantVector *vec, Constant *idx)
            : Constant(vec->getType()), vector_(vec), index_(idx) {}

        void print(std::ostream &os) const override
        {
            os << "extractelement";
            vector_->print(os);
            os << ", ";
            index_->print(os);
        }

    private:
        ConstantVector *vector_;
        Constant *index_;
    };

    class InsertElementConstantExpr : public Constant
    {
    public:
        InsertElementConstantExpr(ConstantVector *vec, Constant *val, Constant *idx)
            : Constant(vec->getType()), vector_(vec), value_(val), index_(idx) {}

        void print(std::ostream &os) const override
        {
            os << "insertelement";
            vector_->print(os);
            os << ", ";
            value_->print(os);
            os << ", ";
            index_->print(os);
        }

    private:
        ConstantVector *vector_;
        Constant *value_;
        Constant *index_;
    };

    class ShuffleVectorConstantExpr : public Constant
    {
    public:
        ShuffleVectorConstantExpr(ConstantVector *v1, ConstantVector *v2, Constant *mask)
            : Constant(v1->getType()), vec1_(v1), vec2_(v2), mask_(mask) {}

        void print(std::ostream &os) const override
        {
            os << "shufflevector";
            vec1_->print(os);
            os << ", ";
            vec2_->print(os);
            os << ", ";
            mask_->print(os);
        }

    private:
        ConstantVector *vec1_;
        ConstantVector *vec2_;
        Constant *mask_;
    };

    class GetElementPtrConstantExpr : public Constant
    {
    public:
        GetElementPtrConstantExpr(Constant *base, const std::vector<Constant *> &indices)
            : Constant(base->getType()), base_(base), indices_(indices) {}

        void print(std::ostream &os) const override
        {
            os << "getelementptr";
            base_->print(os);
            for (Constant *idx : indices_)
            {
                os << ", ";
                idx->print(os);
            }
        }

    private:
        Constant *base_;
        std::vector<Constant *> indices_;
    };
}