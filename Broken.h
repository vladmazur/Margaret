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
    void addPoint(Point poi)
    {
        vertexes.push_back(poi);
        makeVertexes();
    }
    
    void makeVertexes()
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

        center = (leftUpperPoint + rightBottomPoint) * 0.5;
        size = (leftUpperPoint - rightBottomPoint).makePositive();
    }
    
    Broken()
    {}
    
    Broken(const vector<Point> points)
    {
        this->vertexes = points;
        makeVertexes();
    }
    
    void reflect(REFLECT_TYPE type) {}
    
    vector<Point> getVertexes() const
    {
        return vertexes;
    }

    unsigned getCountofVertexes() const
    {
        return vertexes.size();
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

    virtual void drawMarkers(QPainter & painter) const
    {
        vector<Point> shadows(vertexes);
        if (reflectedGor) {
            for (vector<Point>::iterator it = shadows.begin(); it != shadows.end(); ++it) {
                it->x = 2 * center.x - it->x;
            }
        }
        if (reflectedVer) {
            for (vector<Point>::iterator it = shadows.begin(); it != shadows.end(); ++it) {
                it->y = 2 * center.y - it->y;
            }
        }

        double markerSize = size.x/20;
        markerSize = min(10.0, markerSize);
        painter.setPen(QColor(0,0,0,255));
        painter.setBrush(QBrush(QColor(255,0,255,255)));

        painter.drawRect(leftUpperPoint.x, leftUpperPoint.y,
                         markerSize, markerSize);
        painter.drawRect(rightBottomPoint.x-markerSize,
                         rightBottomPoint.y-markerSize,
                         markerSize, markerSize);

        painter.setBrush(QBrush(QColor(0,0,0,255)));
        double r = line.thickness*2;
        for (unsigned i=0; i<getCountofVertexes(); i++) {
            painter.drawEllipse(shadows[i].x- r/2, shadows[i].y- r/2, r, r);
        }
    }

    void draw(QPainter & painter) const
    {
        vector<Point> shadows(vertexes);
        if (reflectedGor) {
            for (vector<Point>::iterator it = shadows.begin(); it != shadows.end(); ++it) {
                it->x = 2 * center.x - it->x;
            }
        }
        if (reflectedVer) {
            for (vector<Point>::iterator it = shadows.begin(); it != shadows.end(); ++it) {
                it->y = 2 * center.y - it->y;
            }
        }

        QPoint *pois = new QPoint[getCountofVertexes()];
//        std::vector<Point> vertxs = getVertexes();
        for (int i=0; i<getCountofVertexes(); i++) {
            pois[i] = QPoint(shadows[i].x, shadows[i].y);
        }
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

        painter.drawPolyline(pois, getCountofVertexes());

        if(selected)
            drawMarkers(painter);
    }

    void move(Point p)
    {
        Point delta = p - center;
        center = p;

        for (vector<Point>::iterator it = vertexes.begin(); it != vertexes.end(); ++it) {
            (*it) = (*it)+delta;
        }

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

    void setBounds(Point p1, Point p2)
    {
        center = (p1 + p2) * 0.5;
        size = (p1 - p2).makePositive();

        leftUpperPoint = p1;
        rightBottomPoint = p2;

        makeVertexes();
    }

    QDomElement getDomElement(QDomDocument doc) const
    {
        return QDomElement();
    }

    void scale(double scale)
    {
        if (scale == 1)
            return;

        if (scale < 1)
            scale = 1 - scale;

        double maxDeltaX = (center-leftUpperPoint).x;
        double maxDeltaY = (center-leftUpperPoint).y;

        for(int i=0; i<getVertexes().size(); i++)
        {
            int sgnx = 1, sgny=1;
            if (vertexes[i].x < center.x)
                sgnx = -1;
            if (vertexes[i].y < center.y)
                sgny = -1;
            if (scale > 1) {
                sgnx *= -1;
                sgny *= -1;
            }
            Point delta = (center - vertexes[i]);
            if (scale > 1)
                delta *= 0.75;
            delta.x *= sgnx * scale * delta.x/maxDeltaX;
            delta.y *= sgny * scale * delta.y/maxDeltaY;
            vertexes[i] -= delta;
        }
        makeVertexes();
    }
    
};

#endif /* defined(__Lab2__Broken__) */
