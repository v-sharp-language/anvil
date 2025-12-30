#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <ir/type.hpp>

namespace anvil::ir
{
    class Type;

    class Context
    {
    public:
        Context() = default;

        Type *getVoidType()
        {
            if (!voidType_)
                voidType_ = makeType(Type::Kind::Void);
            return voidType_;
        }

        Type *getIntType(unsigned bits)
        {
            auto it = std::find_if(types_.begin(), types_.end(),
                                   [bits](const std::unique_ptr<Type> &t)
                                   {
                                       return t->isIntegerTy(bits);
                                   });
            if (it != types_.end())
                return it->get();
            auto *t = makeType(Type::Kind::Integer, bits);
            types_.emplace_back(t);
            return t;
        }

        Type *getInt1Ty() { return getIntType(1); }
        Type *getInt8Ty() { return getIntType(8); }
        Type *getInt16Ty() { return getIntType(16); }
        Type *getInt32Ty() { return getIntType(32); }
        Type *getInt64Ty() { return getIntType(64); }

        Type *getHalfTy() { return getFPType(Type::Kind::Half); }
        Type *getFloatTy() { return getFPType(Type::Kind::Float); }
        Type *getDouble() { return getFPType(Type::Kind::Double); }

        Type *getPointerType(Type *elemType)
        {
            return getDerivedType(elemType, Type::Kind::Pointer);
        }

        Type *getArrayType(Type *elemType, unsigned numElems)
        {
            return getDerivedType(elemType, Type::Kind::Array, numElems);
        }

        Type *getVectorType(Type *elemType, unsigned numElems)
        {
            return getDerivedType(elemType, Type::Kind::Vector, numElems);
        }

        Type *getStructType(const std::vector<Type *> &elements)
        {
            auto it = std::find_if(types_.begin(), types_.end(), [&](const std::unique_ptr<Type> &t)
                                   {
            if (!t->isStructTy()) return false;
            if (t->getStructElements().size() != elements.size()) return false;
            for (size_t i = 0; i < elements.size(); ++i)
                if (t->getStructElements()[i] != elements[i]) return false;
            return true; });
            if (it != types_.end())
                return it->get();
            auto *t = new Type(elements);
            types_.emplace_back(t);
            return t;
        }

        Type *getFunctionType(Type *retType, const std::vector<Type *> &params)
        {
            auto it = std::find_if(types_.begin(), types_.end(),
                                   [retType, &params](const std::unique_ptr<Type> &t)
                                   {
                                       if (!t->isFunctionTy())
                                           return false;
                                       if (t->getReturnType() != retType)
                                           return false;
                                       if (t->getParamTypes().size() != params.size())
                                           return false;
                                       for (size_t i = 0; i < params.size(); ++i)
                                           if (t->getParamTypes()[i] != params[i])
                                               return false;
                                       return true;
                                   });
            if (it != types_.end())
                return it->get();
            auto *t = new Type(retType, params);
            types_.emplace_back(t);
            return t;
        }

    private:
        Type *makeType(Type::Kind kind, unsigned bits = 0) { return new Type(kind, bits); }
        Type *getFPType(Type::Kind k)
        {
            auto it = std::find_if(types_.begin(), types_.end(), [&](const std::unique_ptr<Type> &t)
                                   { return t->getKind() == k; });
            if (it != types_.end())
                return it->get();
            auto *t = makeType(k);
            types_.emplace_back(t);
            return t;
        }
        Type *getDerivedType(Type *elem, Type::Kind k, unsigned numElems = 0)
        {
            auto it = std::find_if(types_.begin(), types_.end(), [&](const std::unique_ptr<Type> &t)
                                   {
            if (t->getKind() != k) return false;
            if (k == Type::Kind::Pointer) return t->getElementType() == elem;
            if (k == Type::Kind::Array || k == Type::Kind::Vector) return t->getElementType() == elem && t->getNumElements() == numElems;
            return false; });
            if (it != types_.end())
                return it->get();
            auto *t = new Type(elem, numElems, k);
            types_.emplace_back(t);
            return t;
        }
        std::vector<std::unique_ptr<Type>> types_;
        Type *voidType_ = nullptr;
    };
}