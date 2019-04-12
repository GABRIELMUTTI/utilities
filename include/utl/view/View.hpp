#pragma once

#include <vector>
#include <tuple>

namespace utl
{
    template<class TDerived, class TContainer, class TIterator>
    class View
    {
    protected:
	const TContainer& values;
	
    public:
	View(const TContainer& values) :
	    values(values)
	{

	}

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

