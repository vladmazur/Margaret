#include "gridwidget.h"

#include <QPainter>
GridWidget::GridWidget(QWidget *parent) :
    QWidget(parent), gridShow(true)
{
}

void GridWidget::paintEvent (QPaintEvent * event)
{
#define GRIDSTEP 15
    QPainter gridPainter(this);
    gridPainter.setPen(Qt::DotLine);
    if (gridShow)
    {
        for (int x=0; x<this->width(); x=x+GRIDSTEP)
            for(int y=0; y<this->width(); y=y+GRIDSTEP) {
                gridPainter.drawLine(x,0,x,this->height());
                gridPainter.drawLine(0,y,this->width(), y);
            }
    }
}
