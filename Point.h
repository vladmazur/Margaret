//
//  Point.h
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab1__Point__
#define __Lab1__Point__

#include <iostream>

class Point {
    
public:
    float x, y;
// In cases where you don't care what a member gets set to (i.e. any possible data is valid),
// then you can make them public.
    
    Point() : x(0), y(0) {}
    Point(const float xNew, const float yNew): x(xNew), y(yNew) {}
    
    friend std::istream &operator>>(std::istream &input,Point &p);
    friend std::ostream &operator << (std::ostream &os, const Point &p);

    Point& operator+=(const Point& poi)
    {
        x+=poi.x;
        y+=poi.y;
        return *this;
    }

    Point& operator-=(const Point& poi)
    {
        x-=poi.x;
        y-=poi.y;
        return *this;
    }

    Point& operator*=(const double s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    Point makePositive()
    {
        if (x < 0) x*=-1;
        if (y < 0) y*=-1;
        return *this;
    }
};

inline Point operator+(Point lhs, const Point& rhs)
{
  lhs += rhs;
  return lhs;
}

inline Point operator-(Point lhs, const Point& rhs)
{
  lhs -= rhs;
  return lhs;
}

inline Point operator*(Point lhs, const double s)
{
  lhs *= s;
  return lhs;
}

#endif /* defined(__Lab1__Point__) */
