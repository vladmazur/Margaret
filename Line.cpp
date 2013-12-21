//
//  Line.cpp
//  Lab1
//
//  Created by Влад Мазур on 03.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#include "Line.h"

std::ostream& operator<<(std::ostream &os, const Line &l)
{
    std::string lineName;
    switch (l.style) {
        case 0:
            lineName = "Solid";
            break;
        case 1:
            lineName = "Dotted";
            break;
        case 2:
            lineName = "Dashed";
            break;
        case 3:
            lineName = "Double Line";
            break;
            
        default:
            break;
    }
    
    os << "Line:\n\tThikness:" << l.thickness << "\n\tColor: " << l.color
		<< "\tStyle: " << l.style << "\n"; //(std::string)lineName << "\n";
    return os;
}