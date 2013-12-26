#include "gridwidget.h"

#include <QPainter>
GridWidget::GridWidget(QWidget *parent) :
    QWidget(parent), gridShow(false)
{
}

void GridWidget::paintEvent (QPaintEvent * event)
{
    QPainter painter(this);

}
