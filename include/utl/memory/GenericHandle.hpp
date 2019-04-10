#pragma once

#include "Handle.hpp"

namespace utl
{
    template<class TPool, class TBase, class TObj> 
    class GenericHandle : public Handle<TBase>
    {
    private:
	const TPool* const pool;
	
    public:
	GenericHandle() :
	    Handle<TBase>()
	{
	    
	}

	GenericHandle(const TPool& pool, const Handle<TBase>& handle) :
	    Handle<TBase>(handle),
	    pool(&pool)
	{
	    
	}
	    
	GenericHandle(const TPool& pool, uint index, bool validity) :
	    Handle<TBase>(index, validity),
	    pool(&pool)
	{
	    
	}
	
	inline TObj* operator ->() const
	{ 
	    return static_cast<TObj*>(pool->get(Handle<TBase>::index));
	}

	inline TObj operator *() const
	{ 
	    return *static_cast<TObj>(pool->get(Handle<TBase>::index));
	}
    };
}
