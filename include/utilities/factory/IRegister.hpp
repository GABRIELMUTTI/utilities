#pragma once

#include "../factory/Factory.hpp"

namespace utl
{
    template<class TBase, typename TId, class ... FuncArgs>
    class IRegister
    {
    public:
	virtual void registerTypes(Factory<TBase, TId, FuncArgs ...>& factory) = 0;
    };
}
