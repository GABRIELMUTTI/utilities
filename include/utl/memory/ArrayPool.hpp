#pragma once

#include "IPool.hpp"

#include <vector>
#include <cstring>
#include <stdexcept>

#include "Handle.hpp"

namespace utl
{
    using uint = unsigned int;

    template<class TBase, class TObj>
    class ArrayPool : public IPool<TBase>
    {
    private: 
	TObj* array;
	uint capacity;
	uint count;
	uint allocationStep;
	std::vector<Handle<TBase>>handles;
	
    public:
	ArrayPool(uint allocationStep) :
	    array(nullptr),
	    capacity(0),
	    count(0),
	    allocationStep(allocationStep)
	{
	    
	}

	const Handle<TBase>& getHandle(uint index)
	{
	    return handles[index];
	}
	
	TBase* get(uint index) const
	{
	    return &array[index];
	}

	void add(uint index)
	{
	    if (count == capacity)
	    {
		allocate(allocationStep);
	    }

	    handles[index] = Handle<TObj>(index, true);
	}
	
        void remove(uint index)
	{
	    count--;
	    handles[index].validity = false;
	}
	
        void allocate(uint amount)
	{
	    uint newCapacity = capacity + amount;
	    TObj* newArray = new TObj[newCapacity];
	    
	    handles.resize(newCapacity, Handle<TObj>(0, false));
	
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
	    handles.resize(newCapacity, Handle<TObj>(0, false));

	    if (newCapacity > 0)
	    {
		if (array != nullptr)
		{
		    TObj* newArray = new TObj[newCapacity];
		    
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
		TObj tmp = array[indexA];
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
