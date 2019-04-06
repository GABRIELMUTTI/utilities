#pragma once

namespace utl
{
    using uint = unsigned int;
    
    class Type
    {
    private:
	const uint id;

    public:
	Type(uint id) : id(id) {}
	
	inline bool operator ==(const Type& other)
	{
	    return this->id == other.id;
	}

	inline bool operator <(const Type& other)
	{
	    return this->id < other.id;
	}

	inline bool operator >(const Type& other)
	{
	    return this->id > other.id;
	}
    };
}
