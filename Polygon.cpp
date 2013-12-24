//
//  Polygon.cpp
//  Lab1
//
//  Created by Влад Мазур on 16.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#include "Polygon.h"
#include "Square.h"

#include <math.h>

#define rad(x) ((x)*M_PI/180)

//unsigned Polygon::count = 0;

unsigned Polygon::getCountOfCorners() const
{
    return cornersCount;
}

void Polygon::setCountOfCorners(unsigned newCornersCount)
{
    cornersCount = newCornersCount;
    alpha = 360/cornersCount;
    
    sideSize = 2*Radius*sin(rad(alpha/2));
    
    makeVertexes();
}

void Polygon::makeVertexes()
{
    vertexes.clear();
    int n=0;
    Square sq(leftUpperPoint, rightBottomPoint);
    Radius = sq.getSideSize() / 2;
    for (float alp=90+alpha/2; n++ < cornersCount; alp= alp+alpha) {
        float x = Radius * cos(rad(alp));
        float y = Radius * sin(rad(alp));
        vertexes.push_back(Point(center.x+x, center.y+y));
    }
    if (reflectedGor) {
        for (vector<Point>::iterator it = vertexes.begin(); it != vertexes.end(); ++it) {
            it->x = 2 * center.x - it->x;
        }
    }
    if (reflectedVer) {
        for (vector<Point>::iterator it = vertexes.begin(); it != vertexes.end(); ++it) {
            it->y = 2 * center.y - it->y;
        }
    }
}

Polygon::Polygon(Point leftUpper, Point rightBottom, unsigned newCornersCount, Color newColor, Line newLine)
{
//    используем Square чтобы сделать правильный квадрат и получить центр
    Square sq(leftUpper, rightBottom);
    leftUpperPoint = sq.leftUpperPoint;
    rightBottomPoint = sq.rightBottomPoint;
    center = sq.getCenter();
    Radius = sq.getSideSize() / 2;
    backGroundColor = newColor;
    line = newLine;
    setCountOfCorners(newCornersCount);
}

vector<Point> Polygon::getVertexes() const
{
    return vertexes;
}

void Polygon::move(Point p)
{
    center = p;
    leftUpperPoint = p - size*0.5;
    rightBottomPoint  = p + size*0.5;
    makeVertexes();
}

std::ostream &operator << (std::ostream &os, const Polygon &p)
{
    os << "Polygon #" <<p.number << ":\n\tKey points:\n\t" << p.leftUpperPoint << "\t" << p.rightBottomPoint << "\n\tCenter: " << p.center << "\tNumber of cornerns: " << p.cornersCount << "\n";
    os << "\tColor: " << p.backGroundColor << "\n\tLine Style:\n\t" << p.line << "\n";
    os << "\tAlpha corner:" << p.alpha << "\n";
    os << "\tSize of sides:" << p.sideSize << "\n\n";
    os << "\tVertexes:\n";
    for (vector<Point>::iterator it = p.getVertexes().begin(); it != p.getVertexes().end(); ++it) {
        cout << "\t" << (Point) *it;
    }
    os << "End of #" << p.number;
    os << "\n\n\n";
    return os;
}
