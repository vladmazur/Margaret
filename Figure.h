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

#include <QPainter>

using namespace std;

#include "Color.h"
#include "Line.h"
#include "Point.h"

#include <QtCore>
#include <QtXml>

typedef enum {REFLECT_HORIZONTAL, REFLECT_VERTICAL} REFLECT_TYPE;
typedef enum {FTRect, FTPolygon, FTBroken} FIGURETYPE;

class Figure {
protected:
    Point       leftUpperPoint, rightBottomPoint;
    Point       center;
    Point       size; // ширина и высота
    Color       backGroundColor;
    Line        line;
    unsigned    number;
    FIGURETYPE  type;
    bool        selected;
    bool        reflectedVer=false,
                reflectedGor=false;
    
public:
    static unsigned count;

    FIGURETYPE getType()
    {
        return type;
    }

    void setType(FIGURETYPE type_)
    {
        type = type_;
    }

    bool getReflectedVer() {
        return reflectedVer;
    }

    bool getReflectedGor() {
        return reflectedGor;
    }


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

    Line getLine() const {
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

    void setLineColor(Color col)
    {
        line.color = col;
    }

    void setLineWidth(int width)
    {
        line.thickness = width;
    }

    void setLineStyle(LineStyle style)
    {
        line.style = style;
    }
    
    void setColor(Color color_) {
        backGroundColor = color_;
    }
    
    Color getColor() const {
        return backGroundColor;
    }
    
    virtual void reflect(REFLECT_TYPE type) = 0;
    void setVertReflection(bool isRefl)
    {
        reflectedVer = isRefl;
    }
    void setHoriReflection(bool isRefl)
    {
        reflectedGor = isRefl;
    }
//    virtual void move(float dx, float dy) {}
//    virtual void scale(float scale_) {}
    virtual vector<Point> getVertexes() const = 0;
    virtual void print() {}

    virtual QDomElement getDomElement(QDomDocument doc) const
    {}

    unsigned getNumber() const
    {
        return number;
    }
    
    bool includesPoint(Point p)
    {
        Point p1 = center - size * 0.5;
        Point p2 = center + size * 0.5;
        return ((p1.x <= p.x) && (p1.y <= p.y) &&
                (p2.x >= p.x) && (p2.y >= p.y));
    }
    
    bool inBoundCornersLeftUpper(Point p)
    {
        double markerSize = size.x/10;
        markerSize = max(10.0, markerSize);
        Point p1 = center - size * 0.5;
        Point p2 = center - size * 0.5 +Point(markerSize, markerSize);

        return ((p1.x <= p.x) && (p1.y <= p.y) &&
                (p2.x >= p.x) && (p2.y >= p.y));
    }

    bool inBoundCornersRightBottom(Point p)
    {
        double markerSize = size.x/10;
        markerSize = max(10.0, markerSize);
        Point p2 = center + size * 0.5;
        Point p1 = center + size * 0.5 -Point(markerSize, markerSize);

        return ((p1.x <= p.x) && (p1.y <= p.y) &&
                (p2.x >= p.x) && (p2.y >= p.y));
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
       return center;
    }

    Figure()
    {
        number = ++Figure::count;
    }

    void select(bool sel)
    {
        selected = sel;
    }

    bool isSelected() const
    {
        return selected;
    }

    virtual void makeVertexes()
    {}

    virtual void setBounds(Point p1, Point p2)
    {
        center = (p1 + p2) * 0.5;
        size = (p1 - p2).makePositive();

        leftUpperPoint = p1;
        rightBottomPoint = p2;

        makeVertexes();
    }

    virtual void move(Point p)
    {
        center = p;

        leftUpperPoint = p - size*0.5;
        rightBottomPoint  = p + size*0.5;
    }

    virtual void draw(QPainter & painter) const =0;

    virtual void drawMarkers(QPainter & painter) const
    {
        Point tl = center - size * 0.5;
        double markerSize = size.x/10;
        markerSize = max(10.0, markerSize);
        painter.setPen(QColor(0,0,0,255));
        painter.setBrush(QBrush(QColor(0,0,0,255)));
        painter.drawRect(tl.x, tl.y, markerSize, markerSize);
        painter.drawRect(tl.x+size.x-markerSize, tl.y+size.y-markerSize,
                         markerSize, markerSize);
    }

    void swapCorners(Point *c1, Point *c2)
    {
//        работает не правильно
        if (c1->x > c2->x) {
            float temp = c2->x;
            c2->x = c1->x; c1->x = temp;
        }
        if (c1->y > c2->y) {
            float temp = c2->y;
            c2->y = c1->y; c1->y = temp;
        }
    }
};


#endif /* defined(__Lab2__Figure__) */
