//
//  Color.h
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab1__Color__
#define __Lab1__Color__

#include <iostream>

class Color {
    
public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    
    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255): red(r), green(g), blue(b), alpha(a) {}
    
    friend std::ostream &operator << (std::ostream &os, const Color &c);
};

#endif /* defined(__Lab1__Color__) */
