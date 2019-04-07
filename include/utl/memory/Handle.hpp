#pragma once

namespace utl
{
    using uint = unsigned int;
    
    template<typename TPool>
    class Handle
    {
	friend TPool;
	
    protected:
	TPool* pool;
	uint index;
	bool validity;

    public:
	Handle() :
	    pool(nullptr),
	    index(0),
	    validity(false)
	{
	    
	}
	
	Handle(TPool* pool, uint index, bool validity) :
	    pool(pool),
	    index(index),
	    validity(validity)
	{

	}

	bool isValid() const
	{
	    return validity;
	}

	inline void operator =(const Handle<TPool>& other)
	{
	    pool = other.pool;
	    index = other.index;
	    validity = other.validity;
	}
	
	inline bool operator ==(const Handle<TPool>& other) const
	{
	    return (index == other.index) && (pool == other.pool);
	}

	inline bool operator >(const Handle<TPool>& other) const
	{
	    return index > other.index;
	}

	inline bool operator <(const Handle<TPool>& other) const
	{
	    return index < other.index;
	}
    };
}
