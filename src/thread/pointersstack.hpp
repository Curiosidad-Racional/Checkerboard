#ifndef __pointersstack_hpp__
#define __pointersstack_hpp__

#include <cstddef> // size_t


template<typename T>
class PointersStack
{
    typedef std::size_t size_t;
    size_t stackSize;
    T** items;

    PointersStack(const PointersStack<T>& );
    
public:

    template<typename... Args>
    PointersStack(Args... args);
    ~PointersStack();

    T* operator[] (size_t i) { return items[i]; }
    size_t size() const { return stackSize; }
};


template<typename T>
template<typename... Args>
PointersStack<T>::PointersStack(Args... args) {
    stackSize = sizeof...(args);
    items = new T* [stackSize] {args...};
}


template<typename T>
PointersStack<T>::~PointersStack() {
    for (size_t i = 0; i < stackSize; ++i) delete items[i];
    delete[] items;
}


#endif // __pointersstack_hpp__
