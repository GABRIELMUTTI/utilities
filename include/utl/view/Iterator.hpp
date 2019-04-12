#pragma once

namespace utl
{
    template<class TDerived, class TContainer, class TObj>
    class Iterator
    {
	using iterator = typename TContainer::iterator;
	using ClassType = Iterator<TDerived, TContainer, TObj>;
	
    private:
	iterator containerIterator;
	
    public:
	Iterator(iterator& begin) :
	    containerIterator(begin)
	{
	    
	}
	
	bool operator ==(const ClassType& other) const
	{
	    return containerIterator == other.containerIterator;
	}
	
	bool operator !=(const ClassType& other) const
	{
	    return containerIterator != other.containerIterator;
	}

	TObj operator *()
	{
	    return *static_cast<TDerived*>(this);
	}

	void operator++()
	{
	    static_cast<TDerived*>(this)++;
	}
    };
}
