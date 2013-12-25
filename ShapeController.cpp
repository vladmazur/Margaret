//
//  ShapeController.cpp
//  Lab1
//
//  Created by Влад Мазур on 17.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//
//
#include "ShapeController.h"
unsigned ShapeController::count =0;

//void ShapeController::saveToXML()
//{
//    QDomDocument doc;
//    for (unsigned i=0; i< getCount(); i++)
//    {
//        Figure * fig = figureAtIndex(i);
//        if (fig->getType() == FTRect)
//        {
//            QDomElement root =  doc.createElement("Rectangle");

//            QDomElement temp = doc.createElement("LeftUpperPoint");
//            temp.setAttribute("x", fig->getLeftUpperPoint().x);
//            temp.setAttribute("y", fig->getLeftUpperPoint().y);
//            root.appendChild(temp);

//            temp = doc.createElement("RightBottomPoint");
//            temp.setAttribute("x", fig->getRightBottomPoint().x);
//            temp.setAttribute("y", fig->getRightBottomPoint().y);
//            root.appendChild(temp);

//            temp = doc.createElement("BackGroundColor");
//            temp.setAttribute("red", fig->getColor().red);
//            temp.setAttribute("green", fig->getColor().green);
//            temp.setAttribute("blue", fig->getColor().blue);
//            temp.setAttribute("alpha", fig->getColor().alpha);
//            root.appendChild(temp);

//            temp = doc.createElement("Line");
//            temp.setAttribute("Width", QString::number(fig->getLine().thickness));
//            temp.setAttribute("Style", QString::number((int)fig->getLine().style));
//            QDomElement lineSets = doc.createElement("Color");
//            lineSets.setAttribute("red", fig->getLine().color.red);
//            lineSets.setAttribute("green", fig->getLine().color.green);
//            lineSets.setAttribute("blue", fig->getLine().color.blue);
//            lineSets.setAttribute("alpha", fig->getLine().color.alpha);
//            temp.appendChild(lineSets);
//            root.appendChild(temp);

//            doc.appendChild(root);
//        }
//    }
//    QFile file("/Users/vladmazur/Desktop/123.xml");
//    if (file.open(QIODevice::WriteOnly | QIODevice ::Text))
//    {
//        QTextStream str(&file);
//        str << doc.toString();
//        file.close();
//    }
//}
