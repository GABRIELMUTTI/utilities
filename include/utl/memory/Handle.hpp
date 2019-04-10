#pragma once

namespace utl
{
    using uint = unsigned int;
    
    template<class T>
    class Handle
    {	
    protected:
	uint index;
	bool validity;

    public:
	Handle() :
	    index(0),
	    validity(false)
	{
	    
	}

	Handle(uint index, bool validity) :
	    index(index),
	    validity(validity)
	{

	}

	Handle(const Handle<T>& handle)
	{
	    index = handle.index;
	    validity = handle.validity;
	}

	~Handle()
	{
	    
	}

	bool isValid() const
	{
	    return validity;
	}

	/*
	inline void operator =(const Handle<T>& other)
	{
	    index = other.index;
	    validity = other.validity;
	}
	*/
	
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
