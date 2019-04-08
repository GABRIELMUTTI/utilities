#pragma once

#include "Handle.hpp"

namespace utl
{
    using uint = unsigned int;

    template<class T>
    class IPool
    {
    public:
	T& get(uint index) const;
	void add(uint index);
        void remove(uint index);
	
        void allocate(uint amount);
        void deallocate(uint amount);
        void swap(uint indexA, uint indexB);
	
        uint getCapacity() const;
        uint getCount() const;
    };	
}
