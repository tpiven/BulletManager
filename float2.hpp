
#ifndef FLOAT2_HPP
#define FLOAT2_HPP

class float2 {
private:
    float _x;
    float _y;
public:
    float2(){}
    float2(float x, float y) : _x(x), _y(y) {}
    ~float2() {}
    float2 operator+ (const float2 &f)
    {
        return float2(this->_x + f._x, this->_y + f._y);
    }
    float2 operator- (const float2 &f)
    {
        return float2(this->_x - f._x, this->_y - f._y);
    }

    float2 operator * (float k)
    {
        return float2(this->_x * k, this->_y * k);
    }
    float2 operator = (const float2 &f)
    {
        this->_x = f._x;
        this->_y = f._y;
        return (*this);
    }
    float GetX(){
        return _x;
    }
    float GetY() {
        return _y;
    }
};

#endif
