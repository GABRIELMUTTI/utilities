#pragma once

#include "Type.hpp"

#include <type_traits>

namespace utl
{
    using uint = unsigned int;

    class TypeInfo
    {
    private:
	static inline uint& numRegistered()
	{
	    static uint numRegistered = 0;
	    return numRegistered;
	}
	
	template<typename T>
	struct TypeId
	{
	    inline static const uint& id()
	    {
		static const uint id = registerType<T>();
		return id;
	    }

	    inline static uint& numDerivedClasses()
	    {
		static uint numDerivedClasses = 0;
		return numDerivedClasses;
	    }
	};

	template<class TDerived, class TBase>
	struct DerivedClassId
	{
	    inline static const uint& id()
	    {
		static const uint id = registerDerivedClass<TDerived, TBase>();
		return id;
	    }
	};

	template<typename T>
	static uint registerType()
	{
	    return numRegistered()++;
	}

	template<class TDerived, class TBase>
	static uint registerDerivedClass()
	{
	    return TypeId<TBase>::numDerivedClasses()++;
	}
	
    public:
	template<typename T>
	static uint getId()
	{
	    return TypeId<T>::id();
	}

	template<typename T>
	static uint getNumDerivedClasses()
	{
	    return TypeId<T>::numDerivedClasses();
	}

	template<class TDerived, class TBase>
	static uint getDerivedClassId()
	{
	    static_assert(std::is_base_of<TBase, TDerived>::value, "TDerived does not inherit from TBase.");
	    return DerivedClassId<TDerived, TBase>::id();
	}

	template<typename T>
	static Type getType()
	{
	    return Type(TypeId<T>::id(), sizeof(T));
	}
    };
}
