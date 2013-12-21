//
//  Polygon.h
//  Lab1
//
//  Created by Влад Мазур on 16.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab1__Polygon__
#define __Lab1__Polygon__

#include <iostream>
#include <vector>

#include "Figure.h"

using namespace std;

class Polygon: public Figure {
private:
    unsigned    cornersCount;
    float       alpha;
    float       sideSize;
    float       Radius;
    
    vector<Point> vertexes;
    void makeVertexes();
public:
    vector<Point> getVertexes() const;
    
    unsigned getCountOfCorners();
    void setCountOfCorners(unsigned newCornersCount);
    
    void scale(float scale);
    void move(float dx, float dy);
    void reflect(REFLECT_TYPE type);
    
    void print()
    {
        cout << *this;
    }
    
    Polygon(): Polygon(Point(0,0), Point(20,20), 6, Color(), Line()) {}
    Polygon(Point leftUpper, Point rightBottom, unsigned newCornersCount, Color newColor, Line newLine);
    
    friend std::ostream &operator << (std::ostream &os, const Polygon &p);
};

#endif /* defined(__Lab1__Polygon__) */
