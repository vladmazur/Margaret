//
//  Broken.h
//  Lab2
//
//  Created by Влад Мазур on 11/13/13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab2__Broken__
#define __Lab2__Broken__

#include <iostream>

#include "Figure.h"

class Broken : public Figure
{
protected:
    vector<Point> vertexes;
    
    
public:
//    vector<Point> getVertexes() const;
    
    void addPoint(Point poi)
    {
        vertexes.push_back(poi);
        makeCorners();
    }
    
    void makeCorners()
    {
        float minX=vertexes[0].x, minY=vertexes[0].y;
        for (vector<Point>::iterator it = vertexes.begin(); it != vertexes.end(); ++it) {
            if(it->x < minX) minX = it->x;
            if(it->y < minY) minY = it->y;
        }
        leftUpperPoint = Point(minX, minY);
        
        float maxX=vertexes[0].x, maxY=vertexes[0].y;
        for (vector<Point>::iterator it = vertexes.begin(); it != vertexes.end(); ++it) {
            if(it->x > maxX) maxX = it->x;
            if(it->y > maxY) maxY = it->y;
        }
        rightBottomPoint = Point(maxX, maxY);
    }
    
    Broken()
    {
        addPoint(Point(0,0));
        addPoint(Point(10,10));
        addPoint(Point(15,5));
    }
    
    Broken(const vector<Point> points)
    {
        this->vertexes = points;
        makeCorners();
    }
    
    void reflect(REFLECT_TYPE type) {}
    void move(float dx, float dy) {}
    void scale(float scale_) {}
    
    vector<Point> getVertexes() const
    {
        return vertexes;
    }
    
    friend std::ostream &operator << (std::ostream &os, const Broken &b)
    {
        os << "\n* Broken #" << b.getNumber() << ":\n\t- Corners:\n\t" << b.getLeftUpperPoint() << "\t" << b.getRightBottomPoint() << "\t- Color:\n\t" << b.backGroundColor << "\t- " << b.line;
        os << "\t-Center: " << b.getCenter();
        os << "\tVertexes:\n";
        for (vector<Point>::iterator it = b.getVertexes().begin(); it != b.getVertexes().end(); ++it) {
            cout << "\t" << (Point) *it;
        }
        os << "End of #" << b.number;
        os << "\n\n\n";
        return os;
    }
    
    void print()
    {
        cout << *this;
    }
    
};

#endif /* defined(__Lab2__Broken__) */
