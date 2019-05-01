#pragma once

#include <vector>
#include <utility>
#include <type_traits>
#include <stdexcept>

namespace utl
{
    template<typename TValue,
	     typename TKey,
	     typename = std::enable_if_t<std::is_integral<TKey>::value>>
    class SparseSet
    {
	using SizeType = typename std::vector<TValue>::size_type;
	
    private:
	class Iterator;
	
	std::vector<TValue> dense;
	std::vector<TKey> sparse;

	const std::string exceptionMessage = "utl::SparseSet";

    public:
	SparseSet()
	{
	    
	}
	
	template<typename T,
		 typename = std::enable_if_t<std::is_same<T, TValue>::value>>
	void insert(TKey key, T&& value)
	{
	    if (key >= sparse.size())
	    {
		sparse.resize(key + 1);
	    }
	    
	    sparse[key] = dense.size() + 1;
	    dense.push_back(std::forward(value));
	}
	
	template<class ... Args> void insert(TKey key, Args&& ... args)
	{
	    insert<TValue>(key, TValue(std::forward(args) ...));
	}

	void remove(TKey key)
	{
	    if (key >= sparse.size()) throw std::out_of_range(exceptionMessage);;
	    if (sparse[key] == 0) throw std::out_of_range(exceptionMessage);;

	    dense[sparse[key] - 1] = dense.back();
	    dense.erase(dense.size() - 1);
	}

	TValue& get(TKey key) const
	{
	    if (key >= sparse.size()) throw std::out_of_range(exceptionMessage);

	    TKey denseIndex = sparse[key];
	    if (denseIndex == 0 || denseIndex - 1 >= dense.size()) throw std::out_of_range(exceptionMessage);

	    return dense[denseIndex - 1];
	}

	void resize(SizeType size)
	{
	    dense.resize(size);
	}

	Iterator begin() const
	{
	    return Iterator(dense, 0);
	}
	
	Iterator end() const
	{
	    return Iterator(dense, dense.size() - 1);
	}
    };


    template<typename TValue,
	     typename TKey,
	     typename TEnableIf>
    class SparseSet<TValue, TKey, TEnableIf>::Iterator
    {
	using Container = std::vector<TValue>;

    private:
	const Container& container;
	TKey index;

    public:
	Iterator(const Container& container, TKey index) :
	    container(container),
	    index(index)
	{
	    
	}

	bool operator ==(const Iterator& other)
	{
	    return index == other.index && container == other.container;
	}
	
	void operator ++()
	{
	    index++;
	}
	    
	TValue& operator *()
	{
	    return container[index];
	}
	
	TValue* operator ->()
	{
	    return &container[index];
	}
    };
}
