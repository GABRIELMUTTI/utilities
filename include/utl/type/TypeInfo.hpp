#pragma once

#include "Type.hpp"

#include <type_traits>

namespace utl
{
    using uint = unsigned int;

    class TypeInfo
    {
    private:
	static uint numRegistered;

	template<typename T>
	struct TypeId
	{
	    static const uint id;
	    static uint numDerivedClasses;
	};

	template<class TDerived, class TBase>
	struct DerivedClassId
	{
	    static const uint id;
	};

	template<typename T>
	static uint registerType()
	{
	    return numRegistered++;
	}

	template<class TDerived, class TBase>
	static uint registerDerivedClass()
	{
	    return TypeId<TBase>::numDerivedClasses++;
	}
	
    public:
	template<typename T>
	static uint getId()
	{
	    return TypeId<T>::id;
	}

	template<typename T>
	static uint getNumDerivedClasses()
	{
	    return TypeId<T>::numDerivedClasses;
	}

	template<class TDerived, class TBase>
	static uint getDerivedClassId()
	{
	    static_assert(std::is_base_of<TBase, TDerived>::value, "TDerived does not inherit from TBase.");
	    return DerivedClassId<TDerived, TBase>::id;
	}

	template<typename T>
	static Type getType()
	{
	    return Type(TypeId<T>::id, sizeof(T));
	}
    };

    uint TypeInfo::numRegistered = 0;

    template<class T>
    uint TypeInfo::TypeId<T>::numDerivedClasses = 0;
    
    template<typename T>
    const uint TypeInfo::TypeId<T>::id = TypeInfo::registerType<T>();

    template<class TDerived, class TBase>
    const uint TypeInfo::DerivedClassId<TDerived, TBase>::id = TypeInfo::registerDerivedClass<TDerived, TBase>();
}
