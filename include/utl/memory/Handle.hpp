#pragma once

#include "IPool.hpp"

namespace utl
{
    using uint = unsigned int;
    
    template<class T>
    class Handle
    {	
    protected:
	IPool<T>* pool;
	uint index;
	bool validity;

    public:
	Handle() :
	    pool(nullptr),
	    index(0),
	    validity(false)
	{
	    
	}

	Handle(IPool<T>& pool, uint index, bool validity) :
	    pool(&pool),
	    index(index),
	    validity(validity)
	{

	}

	bool isValid() const
	{
	    return validity;
	}
	
	inline bool operator ==(const Handle<T>& other) const
	{
	    return (index == other.index) && (validity == other.validity);
	}

	inline bool operator >(const Handle<T>& other) const
	{
	    return index > other.index;
	}

	inline bool operator <(const Handle<T>& other) const
	{
	    return index < other.index;
	}
    };
}
