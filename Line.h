//
//  Line.h
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab1__Line__
#define __Lab1__Line__

#include <iostream>
#include "Color.h"

typedef enum {
    LineStyleSolid=0,
    LineStyleDotted,
    LineStyleDashed,
} LineStyle;

class Line {
    
public:
    int         thickness;
    Color       color;
    LineStyle   style;
    
    Line() : thickness(3), color(Color()), style(LineStyleSolid) {}
    Line(int thick, Color col, LineStyle styl) : thickness(thick), color(col), style(styl) {}
    
    friend std::ostream &operator << (std::ostream &os, const Line &l);
};

#endif /* defined(__Lab1__Line__) */
