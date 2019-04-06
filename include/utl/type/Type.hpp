#pragma once

#include <cstdlib>

namespace utl
{
    using uint = unsigned int;
    
    class Type
    {
    private:
	const uint id;

    public:
	const std::size_t size;
	
	Type(uint id, std::size_t size) : id(id), size(size) {}
	
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
