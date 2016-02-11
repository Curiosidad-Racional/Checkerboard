#ifndef __location_hpp__
#define __location_hpp__

template<typename T>
class Location {
    friend class Piece;
    
    bool valid, valid_x, valid_y;
    unsigned long int size;
    void updateValid() { valid = valid_x && valid_y; }

    T x, y;
    bool setX(T _x) {
        
        if (_x < size) {
            x = _x;
            valid_x = true;
        } else
            valid_x = false;
        updateValid();
        
        return valid_x;
    }
    bool setY(T _y) {
        
        if (_y < size) {
            y = _y;
            valid_y = true;
        } else
            valid_y = false;
        updateValid();
        
        return valid_y;
    }
    void setSize(unsigned long int _size) { size = _size; }

    Location() : size(0), x(0), y(0) {}
    
public:
    
    Location(unsigned long int _size, T _x, T _y) : size(_size) {
        setX(_x);
        setY(_y);
    }
    bool isValid() const { return valid; }
    unsigned long int getSize() const { return size; }
    T getX() const { return x; }
    T getY() const { return y; }
};

#endif // __location_hpp__
