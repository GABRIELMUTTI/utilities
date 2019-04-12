#pragma once

#include "Handle.hpp"

namespace utl
{
    template<class TPool, class TBase, class TObj> 
    class GenericHandle : public Handle<TBase>
    {
    public:
	GenericHandle() :
	    Handle<TBase>()
	{
	    
	}

	GenericHandle(const Handle<TBase>& handle) :
	    Handle<TBase>(handle)
	{
	    
	}
	    
	GenericHandle(TPool& pool, uint index, bool validity) :
	    Handle<TBase>(*pool, index, validity)
	{
	    
	}
	
	inline TObj* operator ->() const
	{ 
	    return static_cast<TObj*>(static_cast<TPool*>(Handle<TBase>::pool)->get(Handle<TBase>::index));
	}

	inline TObj operator *() const
	{ 
	    return *static_cast<TObj*>(static_cast<TPool*>(Handle<TBase>::pool)->get(Handle<TBase>::index));
	}
    };
}
