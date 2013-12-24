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
    
    unsigned getCountOfCorners() const;
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

    void move(Point p);

    void draw(QPainter & painter) const
    {
        Point tl = center - size * 0.5;
        Color f = getColor();
        Color p = getLine().color;
        if (isSelected()) f *= 0.5;
        QPen pen(QBrush(QColor(p.red, p.green, p.blue, p.alpha)), line.thickness);
        switch (line.style) {
        case LineStyleDotted:
            pen.setStyle(Qt::DotLine);
            break;
        case LineStyleDashed:
            pen.setStyle(Qt::DashLine);
            break;
        default:
            break;
        }
        painter.setPen(pen);
        painter.setBrush(QBrush(QColor(f.red, f.green, f.blue, f.alpha)));

        QPoint *pois = new QPoint[getCountOfCorners()];
        std::vector<Point> vertxs = getVertexes();
        for (int i=0; i<getCountOfCorners(); i++) {
            pois[i] = QPoint(vertxs[i].x, vertxs[i].y);
        }

        painter.drawConvexPolygon(pois, getCountOfCorners());

        if (isSelected())
            drawMarkers(painter);
    }
    
    friend std::ostream &operator << (std::ostream &os, const Polygon &p);
};

#endif /* defined(__Lab1__Polygon__) */
