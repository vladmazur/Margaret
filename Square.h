//
//  Square.h
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab1__Square__
#define __Lab1__Square__

#include <iostream>

#include "Point.h"
#include "Color.h"
#include "Line.h"

class Square {
private:
    float sideSize;
    void swapCorners(Point *c1, Point *c2);
    
public:
    Point   leftUpperPoint, rightBottomPoint;
    Color   backGroundColor;
    Line    line;
    
    Square();
    Square(Point leftUp, Point rightBo);
    Square(Point leftUp, float size, Color backGrCol, Line lin);
    Square(Point leftUp, Point rightBo, Color backGrCol, Line lin);
    
    void getAdditionalCorners(Point *leftDown, Point *rightUpper);
    
    void scale(float scale_);
    
    Point getCenter() const;
    
    void move(float dx, float dy);
    void resize(float newSideSize);
    
    float getSideSize();
    
    friend std::ostream &operator << (std::ostream &os, const Square &s);
};

#endif /* defined(__Lab1__Square__) */
