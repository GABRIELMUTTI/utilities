#pragma once

#include <exception>

namespace utl
{
    class OutOfRange : public std::exception
    {
    public:
	const char* what() const throw ()
	{
	    return "Out of range.";
	}
    };
}
