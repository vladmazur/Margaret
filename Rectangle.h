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

        painter.drawRect(tl.x, tl.y, size.x, size.y);

        if (isSelected())
            drawMarkers(painter);
    }

//    void loadFromDom(QDomDocument doc)
//    {
//        QDomElement root = doc.firstChildElement();

//    }

//    QDomElement getDomElement(QDomDocument doc) const
//    {
//        QDomElement root =  doc.createElement("Rectangle");

//        QDomElement temp = doc.createElement("LeftUpperPoint");
//        temp.setAttribute("x", leftUpperPoint.x);
//        temp.setAttribute("y", leftUpperPoint.y);
//        root.appendChild(temp);

//        temp = doc.createElement("RightBottomPoint");
//        temp.setAttribute("x", rightBottomPoint.x);
//        temp.setAttribute("y", rightBottomPoint.y);
//        root.appendChild(temp);

//        temp = doc.createElement("BackGroundColor");
//        temp.setAttribute("red", backGroundColor.red);
//        temp.setAttribute("green", backGroundColor.green);
//        temp.setAttribute("blue", backGroundColor.blue);
//        temp.setAttribute("alpha", backGroundColor.alpha);
//        root.appendChild(temp);

//        temp = doc.createElement("Line");
//        temp.setAttribute("Width", QString::number(line.thickness));
//        temp.setAttribute("Style", QString::number((int)line.style));
//        QDomElement lineSets = doc.createElement("Color");
//        lineSets.setAttribute("red", line.color.red);
//        lineSets.setAttribute("green", line.color.green);
//        lineSets.setAttribute("blue", line.color.blue);
//        lineSets.setAttribute("alpha", line.color.alpha);
//        temp.appendChild(lineSets);
//        root.appendChild(temp);

//        doc.appendChild(root);
//        qDebug() << doc.toString();

////        QFile file("/Users/vladmazur/Desktop/123.xml");
////        if (file.open(QIODevice::WriteOnly | QIODevice ::Text))
////        {
////            QTextStream str(&file);
////            str << doc.toString();
////            file.close();
////        }

//        return root;
//    }

};

#endif /* defined(__Lab2__Rectangle__) */
