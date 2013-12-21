//
//  Figure.h
//  Lab2
//
//  Created by Влад Мазур on 11/13/13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab2__Figure__
#define __Lab2__Figure__

#include <iostream>
#include <vector>

using namespace std;

#include "Color.h"
#include "Line.h"
#include "Point.h"

typedef enum{REFLECT_HORIZONTAL, REFLECT_VERTICAL} REFLECT_TYPE;

class Figure {
protected:
    Point       leftUpperPoint, rightBottomPoint;
    Point       center;
    Color       backGroundColor;
    Line        line;
    unsigned    number;
    unsigned    type;
    
public:
    static unsigned count;

    Point getLeftUpperPoint() const {
        return leftUpperPoint;
    }
    
    void setLeftUpperPoint(Point point) {
        leftUpperPoint = point;
    }

    Point getRightBottomPoint() const {
        return rightBottomPoint;
    }
    
    void setRightBottomPoint(Point point) {
        rightBottomPoint = point;
    }

    Line getLine() {
        return line;
    }
    
    void setLine(float thikness, Color color_, LineStyle style_)
    {
        line.thickness = thikness;
        line.color = color_;
        line.style = style_;
    }
    
    void setLine(Line line_)
    {
        line = line_;
    }
    
    void setColor(Color color_) {
        backGroundColor = color_;
    }
    
    Color getColor() {
        return backGroundColor;
    }
    
    virtual void reflect(REFLECT_TYPE type) {}
    virtual void move(float dx, float dy) {}
    virtual void scale(float scale_) {}
    virtual vector<Point> getVertexes() const = 0;
    /*
     virtual void funcFoo() const = 0;     
     virtual void funcFoo() = 0;
     
     The difference is that the first function can be called on const objects, while the second can't. Moreover, the first function can only call other const member functions on the same object. Regarding inheritance, they behave the same way.
     */
    virtual void print() {}

    unsigned getNumber() const
    {
        return number;
    }
    
    bool includesPoint(Point p)
    {
        if (p.x >= leftUpperPoint.x && p.x <= rightBottomPoint.x)
            if(p.y >= leftUpperPoint.y && p.x <= rightBottomPoint.y)
                return true;
        
        return false;
    }
    
    int getType() {
        return type;
    }
    
    unsigned getWidth() const
    {
        return this->rightBottomPoint.x - this->leftUpperPoint.x;
    }
    
    unsigned getHeight() const
    {
        return this->rightBottomPoint.y - this->leftUpperPoint.y;
    }
    
    Point getCenter() const
    {
        float x, y;
        x = leftUpperPoint.x + getWidth()/2;
        y = leftUpperPoint.y + getHeight()/2;
        return Point(x, y);
    }

    Figure()
    {
        number = ++Figure::count;
    }
};


#endif /* defined(__Lab2__Figure__) */
