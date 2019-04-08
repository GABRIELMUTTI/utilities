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
	char* array;
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

	Handle<ArrayPool> getHandle(uint index)
	{
	    return handles[index];
	}
	
	void* get(uint index) const
	{
	    return (void*)(&array[index * objSize]);
	}

	void add(uint index)
	{
	    if (count == capacity)
	    {
		allocate(allocationStep);
	    }

	    handles[index] = Handle<ArrayPool>(this, index, true);
	}
	
        void remove(uint index)
	{
	    count--;
	    handles[index].validity = false;
	}
	
        void allocate(uint amount)
	{
	    uint newCapacity = capacity + amount;
	    char* newArray = new char[sizeof(char) * objSize];
	    
	    handles.resize(newCapacity, Handle<ArrayPool>(nullptr, 0, false));
	
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
	    handles.resize(newCapacity, Handle<ArrayPool>(nullptr, 0, false));

	    if (newCapacity > 0)
	    {
		if (array != nullptr)
		{
		    char* newArray = new char[sizeof(char) * objSize];
		    
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
		char* tmp = new char[objSize];

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
