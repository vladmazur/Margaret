//
//  GroupsController.h
//  Lab2
//
//  Created by Влад Мазур on 11/14/13.
//  Copyright (c) 2013 Vlad Mazur. All rights reserved.
//

#ifndef __Lab2__GroupsController__
#define __Lab2__GroupsController__

#include <iostream>
#include <vector>
#include "ShapeController.h"

class GroupsController {
protected:
    vector<ShapeController *> figures;
    unsigned currentGroup;
public:
    ShapeController * getGroupByNumber(unsigned number)
    {
        for (typename vector<ShapeController *>::iterator it = figures.begin(); it != figures.end(); ++it) {
            if((*it)->getNumber() == number)
                return *it;
        }
        return NULL;
    }
    
    void addGroup()
    {
        ShapeController * s = new ShapeController();
        figures.push_back(s);
        currentGroup = s->getNumber();
    }
    
    void deleteGroup(unsigned number)
    {
        ShapeController *s = getGroupByNumber(number);
        auto s2 = std::find(figures.begin(), figures.end(), s);
        figures.erase(s2);
        delete *s2;
    }
    
    unsigned getCurrentNumber()
    {
        return currentGroup;
    }
    
    void setCurrentNumber(unsigned number)
    {
        if (number <= ShapeController::count)
            currentGroup = number;
    }
    
    ShapeController * getCurrentGroup()
    {
        return getGroupByNumber(currentGroup);
    }
};

#endif /* defined(__Lab2__GroupsController__) */
