#pragma once

#include "IPool.hpp"

#include <vector>
#include <cstring>
#include <stdexcept>

#include "Handle.hpp"

namespace utl
{
    using uint = unsigned int;

    template<typename T>
    class ArrayPool : public IPool<T>
    {
    private: 
	T* array;
	uint capacity;
	uint count;
	uint allocationStep;
	std::vector<Handle<ArrayPool>> handles;
	
    public:
	ArrayPool(uint allocationStep) :
	    array(nullptr),
	    capacity(0),
	    count(0),
	    allocationStep(allocationStep)
	{
	    
	}

	Handle<ArrayPool> getHandle(uint index)
	{
	    return handles[index];
	}
	
	T& get(uint index) const
	{
	    return &array[index];
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
	    T* newArray = new T[newCapacity];
	    
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
		    T* newArray = new T[newCapacity];
		    
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
		T tmp = array[indexA];
		array[indexA] = array[indexB];
		array[indexB] = tmp;

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
