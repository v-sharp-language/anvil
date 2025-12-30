#pragma once

#include <ostream>
#include <cstdint>

namespace anvil::ir
{
    class Context;

    class Type
    {
        friend class Context;

    public:
        enum class Kind
        {
            Void,
            Integer,
            Pointer,
            Function,
            Struct,
            Array,
            Vector,
            Half,
            Float,
            Double
        };

        Kind getKind() const { return kind_; }
        bool isVoidTy() const { return kind_ == Kind::Void; }
        bool isIntegerTy() const { return kind_ == Kind::Integer; }
        bool isIntegerTy(unsigned bits) const { return isIntegerTy() && bitWidth_ == bits; }
        bool isPointerTy() const { return kind_ == Kind::Pointer; }
        bool isFunctionTy() const { return kind_ == Kind::Function; }
        bool isStructTy() const { return kind_ == Kind::Struct; }
        bool isArrayTy() const { return kind_ == Kind::Array; }
        bool isVectorTy() const { return kind_ == Kind::Vector; }

        bool isHalfTy() const { return kind_ == Kind::Half; }
        bool isFloatTy() const { return kind_ == Kind::Float; }
        bool isDoubleTy() const { return kind_ == Kind::Double; }

        bool isIEEELikeFPTy() const { return isHalfTy() || isFloatTy() || isDoubleTy(); }
        bool isFloatingPointTy() const { return isIEEELikeFPTy(); }

        unsigned getBitWidth() const { return bitWidth_; }
        Type *getElementType() const { return elementType_; }
        Type *getReturnType() const { return returnType_; }
        const std::vector<Type *> &getParamTypes() const { return paramTypes_; }
        const std::vector<Type *> &getStructElements() const { return structElements_; }
        unsigned getNumElements() const { return numElements_; }

    private:
        explicit Type(Kind k, unsigned bits = 0) : kind_(k), bitWidth_(bits) {}
        explicit Type(Type *elem) : kind_(Kind::Pointer), elementType_(elem) {}
        explicit Type(Type *ret, const std::vector<Type *> &params)
            : kind_(Kind::Function), returnType_(ret), paramTypes_(params) {}
        explicit Type(const std::vector<Type *> &elems)
            : kind_(Kind::Struct), structElements_(elems) {}
        explicit Type(Type *elem, unsigned num, Kind k)
            : kind_(k), elementType_(elem), numElements_(num) {}

        Kind kind_;
        unsigned bitWidth_ = 0;
        Type *elementType_ = nullptr;
        unsigned numElements_ = 0;
        Type *returnType_ = nullptr;
        std::vector<Type *> paramTypes_;
        std::vector<Type *> structElements_;
    };
}