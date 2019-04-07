#pragma once

namespace utl
{
    template<class T>
    class Injector
    {
    public:
	virtual void inject(T& obj);
    };
}
