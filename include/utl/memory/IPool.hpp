#pragma once

namespace utl
{
    using uint = unsigned int;
    
    class IPool
    {
    public:
	void* get(uint index) const;
	void add(uint index);
        void remove(uint index);
	
        void allocate(uint amount);
        void deallocate(uint amount);
        void swap(uint indexA, uint indexB);
	
        uint getCapacity() const;
        uint getCount() const;
    };	
}
