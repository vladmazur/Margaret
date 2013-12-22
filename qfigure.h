#ifndef QFIGURE_H
#define QFIGURE_H

#include "Figure.h"
#include <QPainter>

class QFigure : public Figure
{
public:
    QFigure();

    virtual void draw(QPainter & painter) const = 0;
    virtual void select(bool sel) { selected = sel; }
    virtual bool isSelected() const { return selected; }

protected:
    bool selected;

};

#endif // QFIGURE_H
