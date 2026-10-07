
// TODO: Place right error code
template <ConstantType LType, ConstantType RType>
ConstantContainer Add(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = typename ConstantTrait<LType>::cpp;
    using TRight = typename ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires { left + right; })    // TODO: fix pointer artithmetic problem => str* + int is valide but supposed not to work
    {
        auto result = left + right;
        
        using ResultType = decltype(result);
        return ConstantTrait<ToEnum<ResultType>::value>::make(result);
    }
    else
    {
        std::cout << "Sum between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(401);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Sub(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = typename ConstantTrait<LType>::cpp;
    using TRight = typename ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left - right; })
    {
        auto result = left - right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Sub between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(406);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Mul(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right= ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left * right; })
    {
        auto result = left * right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Mul between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(407);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Div(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left / right; })
    {
        auto result = left / right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Div between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(408);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Mod(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left % right; })
    {
        auto result = left % right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Mod between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(409);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Pow(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left * right; })
    {
        auto result = left * right;
        for(int i = 0; i < right - 1; i++)
            result *= right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Pow between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(409);
    }
}

template <ConstantType LType>
ConstantContainer Neg(const ConstantContainer& rLeft)
{
    using TLeft = ConstantTrait<LType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);

    if constexpr(requires{ -left; })
    {
        auto result = -left;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Neg for: " << static_cast<int>(LType) << " doesn't exist" << std::endl;
        exit(412);
    }
}


template <ConstantType LType, ConstantType RType>
ConstantContainer And(const ConstantContainer &rLeft, const ConstantContainer &rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left & right; })
    {
        auto result = left & right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "And between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(409);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Or(const ConstantContainer &rLeft, const ConstantContainer &rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left | right; })
    {
        auto result = left | right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Or between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(410);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Xor(const ConstantContainer &rLeft, const ConstantContainer &rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left ^ right; })
    {
        auto result = left ^ right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Xor between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}

template <ConstantType LType>
ConstantContainer Not(const ConstantContainer &rLeft)
{
    using TLeft = ConstantTrait<LType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);

    if constexpr(requires{ ~left; })
    {
        auto result = ~left;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Not for: " << static_cast<int>(LType) << " doesn't exist" << std::endl;
        exit(412);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Shl(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left << right; })
    {
        auto result = left << right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Left-shift between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer Shr(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left >> right; })
    {
        auto result = left >> right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Right-shift between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer CmpEq(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left == right; })
    {
        auto result = left == right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Is equal between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer CmpNe(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left != right; })
    {
        auto result = left != right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Is different between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer CmpLt(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left < right; })
    {
        auto result = left < right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Lesser than between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer CmpLe(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left <= right; })
    {
        auto result = left <= right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Lesser or equal between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer CmpGt(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left > right; })
    {
        auto result = left > right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Greater than between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}

template <ConstantType LType, ConstantType RType>
ConstantContainer CmpGe(const ConstantContainer& rLeft, const ConstantContainer& rRight)
{
    using TLeft = ConstantTrait<LType>::cpp;
    using TRight = ConstantTrait<RType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);
    TRight right = ConstantTrait<RType>::get(rRight);

    if constexpr(requires{ left >= right; })
    {
        auto result = left >= right;

        using resultType = decltype(result);
        return ConstantTrait<ToEnum<resultType>::value>::make(result);
    }
    else
    {
        std::cout << "Greater or equal between: " << static_cast<int>(LType) << " and: " << static_cast<int>(RType) << " doesn't exist" << std::endl;
        exit(411);
    }
}


template <ConstantType LType>
void Print(const ConstantContainer &rLeft)
{
    using TLeft = ConstantTrait<LType>::cpp;

    TLeft left = ConstantTrait<LType>::get(rLeft);

    if constexpr(requires{ std::cout << left << std::endl; })
    {
        std::cout << left << std::endl;
    }
    else
    {
        std::cout << "Print for: " << static_cast<int>(LType) << " doesn't exist" << std::endl;
        exit(413);
    }
}