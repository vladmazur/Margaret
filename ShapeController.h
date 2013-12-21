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

using namespace std;

//template <typename FigureType>
class ShapeController {
private:
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
        if (index > figures.size())
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
};

#endif /* defined(__Lab1__ShapeController__) */
