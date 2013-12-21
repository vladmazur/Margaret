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
    
};

#endif /* defined(__Lab1__Point__) */
