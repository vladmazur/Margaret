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

QDataStream &operator<<(QDataStream &out, const Color &col)
{
    out << col.red << col.green << col.blue << col.alpha;
    return out;
}

QDataStream &operator>>(QDataStream &in, Color &col)
{
    unsigned char red, green, blue, alpha;

    in >> red >> green >> blue >> alpha;
    col = Color(red, green, blue, alpha);
    return in;
}
