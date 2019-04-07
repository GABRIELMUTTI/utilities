#pragma once

#include "IPool.hpp"

#include <vector>
#include <cstring>
#include <stdexcept>

#include "Handle.hpp"

namespace utl
{
    using uint = unsigned int;
    
    class ArrayPool
    {
    private: 
	uint* array;
	std::size_t objSize;
	uint capacity;
	uint count;
	uint allocationStep;
	std::vector<Handle<ArrayPool>> handles;
	
    public:
	ArrayPool(std::size_t objSize, uint allocationStep) :
	    array(nullptr),
	    objSize(sizeof(uint) * objSize),
	    capacity(0),
	    count(0),
	    allocationStep(allocationStep)
	{
	    
	}

	void* get(uint index) const
	{
	    return (void*)(&array[index]);
	}

	void add(uint index)
	{
	    count++;
	}
	
        void remove(uint index)
	{
	    count--;
	    handles[index].validity = false;
	}
	
        void allocate(uint amount)
	{
	    uint newCapacity = capacity + amount;
	    uint* newArray = new uint[sizeof(uint) * objSize];
	    
	    handles.resize(newCapacity, Handle<ArrayPool>(*this, 0, false));
	
	    if (array != nullptr)
	    {
		for (uint i = 0; i < capacity; i++)
		{
		    newArray[i] = array[i];
		}

		delete[] array;  
	    }

	    array = newArray;
	    capacity = newCapacity;
	}

	    
        void deallocate(uint amount)
	{
	    int newCapacity = capacity - amount;
	    handles.resize(newCapacity, Handle<ArrayPool>(*this, 0, false));

	    if (newCapacity > 0)
	    {
		if (array != nullptr)
		{
		    uint* newArray = new uint[sizeof(uint) * objSize];
		    
		    for (int i = 0; i < newCapacity; i++)
		    {
			newArray[i] = array[i];
		    }

		    delete[] array;
		    array = newArray;
		}
	    }
	    else
	    {
		if (array != nullptr)
		{
		    capacity = 0;
		    delete[] array;
		    array = nullptr;		    
		}
	    }
	}
	
        void swap(uint indexA, uint indexB)
	{
	    if (indexA < capacity && indexB < capacity)
	    {
		uint* tmp = new uint[objSize];

		memcpy(tmp, &array[indexB], objSize);
		memcpy(&array[indexB], &array[indexA], objSize);
		memcpy(&array[indexA], tmp, objSize);
	    }
	    else
	    {
		throw std::out_of_range("Index out of range.");
	    }
	}
	
        uint getCapacity() const
	{
	    return capacity;
	}
	
        uint getCount() const
	{
	    return count;
	}
    };	
}
