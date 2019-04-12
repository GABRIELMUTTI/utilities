#pragma once

namespace utl
{
    using uint = unsigned int;
    template<class T>
    class Handle;

    template<class TObj>
    class IPool
    {
    public:
	TObj* get(uint index) const;
	const Handle<TObj>& getHandle(uint index) const;
	
	void add(uint index);
        void remove(uint index);
	
        void allocate(uint amount);
        void deallocate(uint amount);
        void swap(uint indexA, uint indexB);
	
        uint getCapacity() const;
        uint getCount() const;
    };
}
