#ifndef __location_hpp__
#define __location_hpp__

template<typename T>
class Location {
protected:
    T x, y;
public:
    Location(T _x, T _y) : x(_x), y(_y) {}
};

#endif // __location_hpp__
