#ifndef MATHTOOL_H_INCLUDED
#define MATHTOOL_H_INCLUDED

#include <math.h>
#define NumType float
#define PI 3.14159265359

struct vec2{
    NumType x,y;
    vec2(){}
    vec2(NumType a, NumType b){
        x = a;
        y = b;
    }
    vec2& operator+=(const vec2 &a){
        x += a.x;
        y += a.y;
        return *this;
    }
    vec2& operator-=(const vec2 &a){
        x -= a.x;
        y -= a.y;
        return *this;
    }
    vec2& operator/=(NumType s){
        x /= s;
        y /= s;
        return *this;
    }
    friend vec2 operator+(const vec2 &a, const vec2 &b){
        vec2 ret;
        ret.x = a.x + b.x;
        ret.y = a.y + b.y;
        return ret;
    }
    friend vec2 operator-(const vec2 &a, const vec2 &b){
        vec2 ret;
        ret.x = a.x - b.x;
        ret.y = a.y - b.y;
        return ret;
    }
    friend vec2 operator*(NumType s, const vec2 &v){
        vec2 ret;
        ret.x = v.x * s;
        ret.y = v.y * s;
        return ret;
    }
    friend vec2 operator/(const vec2 &v, NumType s){
        vec2 ret;
        ret.x = v.x / s;
        ret.y = v.y / s;
        return ret;
    }
    NumType lenSquare()const{
        return x*x + y*y;
    }
    NumType len()const{
        return sqrt(lenSquare());
    }
};

#endif // MATHTOOL_H_INCLUDED
