#pragma once

#include "Type.hpp"

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
	};

	template<typename T>
	static uint registerType()
	{
	    return numRegistered++;
	}
	
    public:
	template<typename T>
	static const uint getId()
	{
	    return TypeId<T>::id;
	}

	template<typename T>
	static Type getType()
	{
	    return Type(TypeId<T>::id);
	}
    };

    uint TypeInfo::numRegistered = 0;
    
    template<typename T>
    const uint TypeInfo::TypeId<T>::id = TypeInfo::registerType<T>();
}
