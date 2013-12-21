//
//  Rectangle.h
//  Lab2
//
//  Created by Влад Мазур on 11/13/13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab2__Rectangle__
#define __Lab2__Rectangle__

#include <iostream>

#include "Figure.h"

class Rectangle: public Figure {
protected:

public:
    Point leftBottomPoint() const
    {
        return Point(this->leftUpperPoint.x, this->rightBottomPoint.y);
    }
    
    Point rightUpperPoint() const
    {
        return Point(this->rightBottomPoint.x, this->leftUpperPoint.y);
    }
    
    void reflect(REFLECT_TYPE type)
    {
        return;
    }
    
    void move(float dx, float dy)
    {
        this->leftUpperPoint.x += dx;
        this->leftUpperPoint.y += dy;
        
        this->rightBottomPoint.x += dx;
        this->rightBottomPoint.y += dy;
    }
    
    void scale(float scale_)
    {
        if (scale_ <= 0)
            return;
        rightBottomPoint.x *= scale_;
        rightBottomPoint.y *= scale_;
    }
    
    vector<Point> getVertexes() const
    {
        vector<Point> points;
        points.push_back(this->leftUpperPoint);
        points.push_back(this->rightUpperPoint());
        points.push_back(this->rightBottomPoint);
        points.push_back(this->leftBottomPoint());
        
        return points;
    }
    
    friend std::ostream &operator << (std::ostream &os, const Rectangle &r)
    {
        os << "\n* Rectangle #" << r.getNumber() << ":\n\t- Corners:\n\t" << r.leftUpperPoint << "\t" << r.rightBottomPoint
        << "\t- Color:\n\t" << r.backGroundColor << "\t- " << r.line;
        os << "\t-Center: " << r.getCenter();
        os << "\tVertexes:\n";
        for (vector<Point>::iterator it = r.getVertexes().begin(); it != r.getVertexes().end(); ++it) {
            cout << "\t" << (Point) *it;
        }
        os << "End of #" << r.number;
        os << "\n\n\n";
        return os;
    }
    
    void print()
    {
        cout << *this;
    }
    
    Rectangle(Point leftUp_, Point rightBot_)
    {
        leftUpperPoint = leftUp_;
        rightBottomPoint = rightBot_;
    }
    Rectangle()
    {
        leftUpperPoint = Point(10, 20);
        rightBottomPoint = Point(30, 40);
    }
};

#endif /* defined(__Lab2__Rectangle__) */
