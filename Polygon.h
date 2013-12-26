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

#define M_PI 3.1415926

#include "Figure.h"

using namespace std;

class Polygon: public Figure {
protected:
    unsigned    cornersCount;
    float       alpha;
    float       sideSize;
    float       Radius;
    
    vector<Point> vertexes;
public:
    void makeVertexes();
    vector<Point> getVertexes() const;
    
    unsigned getCountOfCorners() const;
    void setCountOfCorners(unsigned newCornersCount);
    
    void reflect(REFLECT_TYPE type)
    {
        if (type == REFLECT_VERTICAL)
            reflectedVer = ! reflectedVer;
        else
            reflectedGor = ! reflectedGor;
    }
    
    void print()
    {
        cout << *this;
    }
    
    Polygon(): Polygon(Point(0,0), Point(20,20), 6, Color(), Line()) {}
    Polygon(Point leftUpper, Point rightBottom, unsigned newCornersCount, Color newColor, Line newLine);

    void move(Point p);

    void draw(QPainter & painter) const
    {
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
        for (unsigned i=0; i<getCountOfCorners(); i++) {
            pois[i] = QPoint(vertxs[i].x, vertxs[i].y);
        }
        painter.drawConvexPolygon(pois, getCountOfCorners());

        if (isSelected())
            drawMarkers(painter);
    }

    QDomElement getDomElement(QDomDocument doc) const
    {
        return QDomElement();
    }

    
    friend std::ostream &operator << (std::ostream &os, const Polygon &p);
};

#endif /* defined(__Lab1__Polygon__) */
