#pragma once

namespace utl
{
    template<class TIterator>
    class View
    {
	TIterator begin()
	{
	    return static_cast<TDerived*>(this)->begin();
	}

	TIterator end()
	{
	    return static_cast<TDerived*>(this)->end();
	}
    };
}
