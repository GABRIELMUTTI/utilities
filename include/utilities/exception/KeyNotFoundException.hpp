#pragma once

#include <exception>

namespace utility
{
    class KeyNotFoundException : public std::exception
    {
    public:
	
	const char* what() const throw ()
	{
	    return "Key not found.";
	}
    };
}
