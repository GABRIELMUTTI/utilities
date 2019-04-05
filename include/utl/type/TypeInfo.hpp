#pragma once

namespace utl
{
    using uint = unsigned int;
    
    class TypeInfo
    {
    private:
	template<typename T>
	struct Type
	{
	    static const uint id;
	    static const char* name;
	};
	
	static uint numRegistered;
	
    public:
	template<typename T>
	static const uint getId()
	{
	    return Type<T>::id;
	}

	template<typename T>
	static const uint getName()
	{
	    return Type<T>::name;
	}

	template<typename T>
	static uint registerType()
	{
	    return numRegistered++;
	}
    };

    template<typename T>
    const uint TypeInfo::Type<T>::id = TypeInfo::registerType<T>();

    uint TypeInfo::numRegistered = 0;
}
