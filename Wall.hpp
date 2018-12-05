#include "float2.hpp"
#ifndef WALL_HPP
#define WALL_HPP

class Wall {
    float2 one;
    float2 two;
public:
    Wall(float2 a, float2 b) : one(a), two(b) {}
    ~Wall() {}
    float2 GetOne(){
        return one;
    }
    float2 GetTwo() {
        return two;
    }
};


#endif
