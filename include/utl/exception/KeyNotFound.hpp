#pragma once

#include <exception>

namespace utl
{
    class KeyNotFound : public std::exception
    {
    public:
	const char* what() const throw ()
	{
	    return "Key not found.";
	}
    };
}
