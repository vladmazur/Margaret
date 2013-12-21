//
//  Point.cpp
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#include "Point.h"

std::ostream& operator<<(std::ostream &os, const Point &p)
{
    os << "Point(" << p.x << "," << p.y << ")\n";
    return os;
}

std::istream &operator>>(std::istream &input,Point &p)
{
	std::cout<<"Enter your x, y\t";
	input>> p.x >> p.y;
	std::cout<<"\n";
	return input;
}