//
//  Color.h
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab1__Color__
#define __Lab1__Color__

#include <iostream>

typedef enum {CTBACKGROUND, CTPEN} COLORTYPE;

class Color {
    
public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    
    Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255): red(r), green(g), blue(b), alpha(a) {}
    
    friend std::ostream &operator << (std::ostream &os, const Color &c);

    Color& operator*=(const double s)
    {
        red *= s;
        green *= s;
        blue *= s;
        alpha *= s;
        return *this;
    }
};

inline Color operator*(Color lhs, const double s)
{
  lhs *= s;
  return lhs;
}

inline bool operator !=(const Color& left, const Color& right)
{
    return (!((left.red == right.red) &&
            (left.green == right.green) &&
            (left.blue == right.blue) &&
            (left.alpha == right.alpha)));
}

#endif /* defined(__Lab1__Color__) */
