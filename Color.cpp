//
//  Color.cpp
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#include "Color.h"

std::ostream& operator<<(std::ostream &os, const Color &c)
{
    os << "Color(" << (int) c.red << "," << (int) c.green << "," << (int) c.blue << "," <<
         (int) c.alpha << ")\n";
    return os;
}