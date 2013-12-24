//
//  Square.cpp
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#include "Square.h"

float Square::getSideSize()
{
    return sideSize;
}

void Square::swapCorners(Point *c1, Point *c2)
{
    bool wasChanged = false;
    if (c1->x > c2->x) {
        float temp = c2->x;
        c2->x = c1->x; c1->x = temp;
        wasChanged = true;
    }
    if (c1->y > c2->y) {
        float temp = c2->y;
        c2->y = c1->y; c1->y = temp;
        wasChanged = true;
    }
}

Square::Square()
{
    leftUpperPoint = Point(0,0);
    rightBottomPoint = Point(10,10);
    backGroundColor = Color();
    line = Line();
    sideSize = 10.0;
}

Square::Square(Point leftUp, Point rightBo)
{
    swapCorners(&leftUp, &rightBo);
    if (rightBo.x - leftUp.x != rightBo.y - leftUp.y) { // теперь точно квадрат
        rightBo = Point(rightBo.x, leftUp.y + rightBo.x - leftUp.x);
	}
    backGroundColor = Color();
    line = Line();
    sideSize = rightBo.x - leftUp.x;
    
    leftUpperPoint = leftUp;
    rightBottomPoint = rightBo;
    
//    circle = new Circle(getCenter(), sideSize /2, Color());
}

Square::Square(Point leftUp, float size, Color backGrCol, Line lin)
{
    leftUpperPoint = leftUp;
    rightBottomPoint = Point(leftUp.x + size, leftUp.y + size);
    backGroundColor = backGrCol;
    line = lin;
    sideSize = size;
}

Square::Square(Point leftUp, Point rightBo, Color backGrCol, Line lin)
{
    swapCorners(&leftUp, &rightBo);
    if (rightBo.x - leftUp.x != rightBo.y - leftUp.y) { // теперь точно квадрат
        rightBo = Point(rightBo.x, leftUp.y + rightBo.x - leftUp.x);
		std::cout << "Square: given coordinates were bad, so I've fixed them\n";
	}
    
    leftUpperPoint = leftUp;
    rightBottomPoint = rightBo;
    backGroundColor = backGrCol;
    line = lin;
    sideSize = rightBo.x - leftUp.x;
}

std::ostream& operator << (std::ostream &os, const Square &s)
{
    os << "\n* Square: \n\t- Corners:\n\t" << s.leftUpperPoint << "\t" << s.rightBottomPoint
        << "\t- Color:\n\t" << s.backGroundColor << "\t- " << s.line;
    os << "\t-Center: " << s.getCenter();
    return os;
}

Point Square::getCenter() const
{
    float x, y;
    x = leftUpperPoint.x + sideSize/2;
    y = leftUpperPoint.y + sideSize/2;
    return Point(x, y);
}

void Square::move(float dx, float dy)
{
    leftUpperPoint.x += dx;
    leftUpperPoint.y += dy;
    rightBottomPoint.x += dx;
    rightBottomPoint.y += dy;
}

void Square::resize(float newSideSize)
{
    sideSize = newSideSize;
    rightBottomPoint = Point(leftUpperPoint.x + sideSize, leftUpperPoint.y + sideSize);
}

void Square::getAdditionalCorners(Point *leftDown, Point *rightUpper)
{
    leftDown->x = leftUpperPoint.x;
    leftDown->y = rightBottomPoint.y;
    rightUpper->x = rightBottomPoint.x;
    rightUpper->y = leftUpperPoint.y;
}

void Square::scale(float scale_)
{
    float newSideSize = sideSize * scale_;
    resize(newSideSize);
}
