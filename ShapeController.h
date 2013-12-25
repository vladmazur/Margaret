//
//  ShapeController.h
//  Lab1
//
//  Created by Влад Мазур on 17.10.13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab1__ShapeController__
#define __Lab1__ShapeController__

#include <iostream>
#include <vector>
#include <algorithm>

#include "Figure.h"

#include <QDebug>
#include <QFile>

#include "Polygon.h"
#include "Broken.h"
#include "Rectangle.h"

using namespace std;

class ShapeController {
protected:
    vector <Figure *> figures;
    unsigned number;
public:
    static unsigned count;
    
    void addFigure(Figure * newFigure)
    {
        figures.push_back(newFigure);
    }
    
    Figure * figureAtIndex(unsigned index)
    {
        if (index > figures.size()-1)
            return NULL;
        return figures[index];
    }
    
    Figure * figureByNumber(unsigned number)
    {
        for (typename vector<Figure *>::iterator it = figures.begin(); it != figures.end(); ++it) {
            if((*it)->getNumber() == number)
                return *it;
        }
        return NULL;
    }
    
    Figure * figureByPoint(Point poi)
    {
        for (typename vector<Figure *>::iterator it = figures.begin(); it != figures.end(); ++it) {
            if((*it)->includesPoint(poi))
                return *it;
        }
        return NULL;
    }
    
    void deleteByNumber(unsigned number)
    {
        Figure * fig = figureByNumber(number);
        auto fig2 = std::find(figures.begin(), figures.end(), fig);
        figures.erase(fig2);
        delete fig;
    }
    
    void deleteAtIndex(unsigned index)
    {
        if (index > figures.size()-1)
            return;
        delete figures[index];
        figures.erase(figures.begin() + index);
    }
    
    void deleteAll()
    {
        for (int i=0; i<figures.size(); ++i) {
            delete figureAtIndex(i);
        }
        figures.clear();
    }
    
    unsigned getCount()
    {
        return (unsigned) figures.size();
    }
    
    unsigned getNumber()
    {
        return number;
    }
    
    ShapeController()
    {
        number = ++ShapeController::count;
    }
    
    vector<Figure*> allFigures()
    {
        return figures;
    }

    void saveToXML(QString fileName)
    {
        QDomDocument doc;

        QDomElement mainRoot = doc.createElement("Figures");
        doc.appendChild(mainRoot);

        for (unsigned i=0; i< getCount(); i++)
        {
            Figure * fig = figureAtIndex(i);

            QString typeName;
            switch (fig->getType()) {
            case FTRect:
                typeName = "Rectangle";
                break;
            case FTPolygon:
                typeName = "Polygon";
                break;
            case FTBroken:
                typeName = "Broken";
                break;
            default:
                typeName = "Fake";
                break;
            }

            QDomElement root =  doc.createElement(typeName);

            QDomElement temp = doc.createElement("LeftUpperPoint");
            temp.setAttribute("x", fig->getLeftUpperPoint().x);
            temp.setAttribute("y", fig->getLeftUpperPoint().y);
            root.appendChild(temp);

            temp = doc.createElement("RightBottomPoint");
            temp.setAttribute("x", fig->getRightBottomPoint().x);
            temp.setAttribute("y", fig->getRightBottomPoint().y);
            root.appendChild(temp);

            temp = doc.createElement("BackGroundColor");
            temp.setAttribute("red", fig->getColor().red);
            temp.setAttribute("green", fig->getColor().green);
            temp.setAttribute("blue", fig->getColor().blue);
            temp.setAttribute("alpha", fig->getColor().alpha);
            root.appendChild(temp);

            temp = doc.createElement("Line");
            temp.setAttribute("Width", QString::number(fig->getLine().thickness));
            temp.setAttribute("Style", QString::number((int)fig->getLine().style));
            QDomElement lineSets = doc.createElement("Color");
            lineSets.setAttribute("red", fig->getLine().color.red);
            lineSets.setAttribute("green", fig->getLine().color.green);
            lineSets.setAttribute("blue", fig->getLine().color.blue);
            lineSets.setAttribute("alpha", fig->getLine().color.alpha);
            temp.appendChild(lineSets);
            root.appendChild(temp);

            mainRoot.appendChild(root);

            if (fig->getType() == FTPolygon)
            {
                temp = doc.createElement("CornerCount");
                temp.setAttribute("count", QString::number(((Polygon*)fig)->getCountOfCorners()));
                root.appendChild(temp);

                temp = doc.createElement("Reflection");
                temp.setAttribute("Vertical", QString::number((fig)->getReflectedVer()));
                temp.setAttribute("Horizontal", QString::number((fig)->getReflectedGor()));
                root.appendChild(temp);
            }

            if (fig->getType() == FTBroken)
            {
                fig = (Broken *)fig;
                vector<Point> pois(fig->getVertexes());
                for(unsigned i=0; i < pois.size(); i++) {
                    temp = doc.createElement("Vertex");
                    temp.setAttribute("x", QString::number(pois[i].x));
                    temp.setAttribute("y", QString::number(pois[i].y));
                    root.appendChild(temp);
                }
            }
        }

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice ::Text))
        {
            QTextStream str(&file);
            QDomNode node( doc.createProcessingInstruction( "xml", "version=\"1.0\" standalone=\"no\"" ) );
            doc.insertBefore( node, doc.firstChild() );
            doc.save(str, 4);
            file.close();
        }
    }

    void loadFromXML(QString fileName)
    {
        deleteAll();

        QFile file(fileName);
        if ( ! file.open(QIODevice::ReadOnly | QIODevice ::Text)) {
            qDebug() << "no file!";
            return;
        }
        QString error;
        int line, col;
        QDomDocument doc;
        if ( ! doc.setContent(&file, &error, &line, &col)) {
            qDebug() << error <<"  "<<line<<"  "<<col;
            return;
        }
        file.close();

        QDomElement root = doc.firstChildElement();

//        rectangles:
        QDomNodeList items = root.elementsByTagName("Rectangle");
        for (int i=0; i< items.count(); i++)
        {
            QDomNode item = items.at(i);
            if ( ! item.isElement())
                continue;
            QDomElement elem = item.toElement();
            QDomElement LUpoint = elem.firstChildElement();
            QDomElement RDpoint = elem.elementsByTagName("RightBottomPoint").at(0).toElement();

            Figure * rect = new Rectangle(Point(LUpoint.attribute("x").toDouble(), LUpoint.attribute("y").toDouble()),
                                          Point(RDpoint.attribute("x").toDouble(), RDpoint.attribute("y").toDouble()));
            QDomElement col = elem.elementsByTagName("BackGroundColor").at(0).toElement();
            Color back(col.attribute("red").toInt(), col.attribute("green").toInt(),
                       col.attribute("blue").toInt(), col.attribute("alpha").toInt());
            rect->setColor(back);

            QDomElement line = elem.elementsByTagName("Line").at(0).toElement();
            int width, style;
            width = line.attribute("Width").toInt();
            style = line.attribute("Style").toInt();
            col = line.elementsByTagName("Color").at(0).toElement();
            Color lineCol(col.attribute("red").toInt(), col.attribute("green").toInt(),
                       col.attribute("blue").toInt(), col.attribute("alpha").toInt());
            rect->setLine(width, lineCol, LineStyle(style));

            rect->setType(FTRect);
            rect->select(false);
            addFigure(rect);
        }

//        polygons:
        items = root.elementsByTagName("Polygon");
        for (int i=0; i< items.count(); i++)
        {
            QDomNode item = items.at(i);
            if ( ! item.isElement())
                continue;
            QDomElement elem = item.toElement();
            QDomElement LUpoint = elem.firstChildElement();
            QDomElement RDpoint = elem.elementsByTagName("RightBottomPoint").at(0).toElement();

            QDomElement col = elem.elementsByTagName("BackGroundColor").at(0).toElement();
            Color back(col.attribute("red").toInt(), col.attribute("green").toInt(),
                       col.attribute("blue").toInt(), col.attribute("alpha").toInt());

            QDomElement line = elem.elementsByTagName("Line").at(0).toElement();
            int width, style;
            width = line.attribute("Width").toInt();
            style = line.attribute("Style").toInt();
            col = line.elementsByTagName("Color").at(0).toElement();
            Color lineCol(col.attribute("red").toInt(), col.attribute("green").toInt(),
                       col.attribute("blue").toInt(), col.attribute("alpha").toInt());

            QDomElement corCount = elem.elementsByTagName("CornerCount").at(0).toElement();

            Figure * poly = new Polygon(Point(LUpoint.attribute("x").toDouble(), LUpoint.attribute("y").toDouble()),
                                          Point(RDpoint.attribute("x").toDouble(), RDpoint.attribute("y").toDouble()),
                                        corCount.attribute("count").toInt(), back, Line(width, lineCol, LineStyle(style)));

            poly->setType(FTPolygon);
            poly->select(false);
            addFigure(poly);
        }

//        brokens:
        items = root.elementsByTagName("Broken");
        for (int i=0; i< items.count(); i++)
        {
            QDomNode item = items.at(i);
            if ( ! item.isElement())
                continue;
            QDomElement elem = item.toElement();
            QDomElement LUpoint = elem.firstChildElement();
            QDomElement RDpoint = elem.elementsByTagName("RightBottomPoint").at(0).toElement();

            QDomElement col = elem.elementsByTagName("BackGroundColor").at(0).toElement();
            Color back(col.attribute("red").toInt(), col.attribute("green").toInt(),
                       col.attribute("blue").toInt(), col.attribute("alpha").toInt());

            QDomElement line = elem.elementsByTagName("Line").at(0).toElement();
            int width, style;
            width = line.attribute("Width").toInt();
            style = line.attribute("Style").toInt();
            col = line.elementsByTagName("Color").at(0).toElement();
            Color lineCol(col.attribute("red").toInt(), col.attribute("green").toInt(),
                       col.attribute("blue").toInt(), col.attribute("alpha").toInt());

            vector<Point> pois;
            QDomNodeList vertexes = elem.elementsByTagName("Vertex");
            for (int i=0; i< vertexes.count(); i++)
            {
                QDomElement ver =  vertexes.at(i).toElement();
                double x,y;
                x = ver.attribute("x").toDouble();
                y = ver.attribute("y").toDouble();
                Point p(x, y);
                pois.push_back(p);
            }

            Figure * brok = new Broken(pois);
            brok->setColor(back);
            brok->setLine(Line(width, lineCol, LineStyle(style)));

            brok->setType(FTBroken);
            brok->select(false);
            addFigure(brok);
        }
    }
};

#endif /* defined(__Lab1__ShapeController__) */
