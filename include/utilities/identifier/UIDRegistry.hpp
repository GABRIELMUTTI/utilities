#pragma once

#include <unordered_map>
#include <typeindex>

namespace utility
{
    template<typename T>
    class UIDRegistry
    {
	typedef unsigned int uint;
	
    private:
	std::unordered_map<T, uint> uIds;
	uint numRegistered = 0;

    public:

	void enroll(const T& key)
	{
	    auto it = uIds.find(key);
	    if (it != uIds.end())
	    {
		uIds[key] = numRegistered;
		numRegistered++;
	    }
	}

	uint getUId(const T& key) const
	{
	    auto it = uIds.find(key);
	    if (it != uIds.end())
	    {
		return uIds[key];
	    }

	    return 0;
	}
    };
}
