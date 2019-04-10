#pragma once

#include "Handle.hpp"

namespace utl
{
    template<class TPool, typename TObj> 
    class GenericHandle : public Handle<TPool>
    {
    private:
	const TPool* const pool;
	
    public:
	GenericHandle() :
	    Handle<TObj>()
	{
	    
	}

	GenericHandle(const TPool& pool, const Handle<TObj>& handle) :
	    Handle<TPool>(handle),
	    pool(&pool)
	{
	    
	}
	    
	GenericHandle(const TPool& pool, uint index, bool validity) :
	    Handle<TPool>(index, validity),
	    pool(&pool)
	{
	    
	}
	
	inline TObj* operator ->() const
	{ 
	    return static_cast<TObj*>(pool->get(Handle<TObj>::index));
	}

	inline TObj operator *() const
	{ 
	    return *static_cast<TObj*>(pool->get(Handle<TObj>::index));
	}
    };
}
