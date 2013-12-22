
#include "canvaswidget.h"

//#include <QPainter>
CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent), selected(NULL), creating(false), resizingLU(false),
    resizingDR(false)
{
    workColor = Color(255,212,22,255);
    workPenColor = Color(195,25,172,255);
}
CanvasWidget::~CanvasWidget() {
    for (unsigned i = 0; i < shapes.size(); ++i)
    {
        delete shapes[i];
    }
}
void CanvasWidget::mousePressEvent (QMouseEvent * event)
{
    pressedPoint.x = event->localPos().x();
    pressedPoint.y = event->localPos().y();
    if (selected) selected->select(false); selected = NULL;
    for (unsigned i = shapes.size(); i > 0; --i)
    {
        if (shapes[i - 1]->includesPoint(pressedPoint))
        {
            selected = shapes[i - 1];
            pressedPoint.x -= selected->getCenter().x;
            pressedPoint.y -= selected->getCenter().y;
            selected->select(true);

            if (selected->inBoundCornersLeftUpper(pressedPoint+selected->getCenter())) {
                resizingLU = true;
                pressedPoint.x = event->localPos().x();
                pressedPoint.y = event->localPos().y();
            }
            if (selected->inBoundCornersRightBottom(pressedPoint+selected->getCenter())) {
                resizingDR = true;
                pressedPoint.x = event->localPos().x();
                pressedPoint.y = event->localPos().y();
            }

            break;
        } }
    update();
}
void CanvasWidget::mouseMoveEvent (QMouseEvent * event)
{
    if ((event->buttons()) & Qt::LeftButton)
    {
        Point currentPoint;
        currentPoint.x = event->localPos().x();
        currentPoint.y = event->localPos().y();
        if (creating)
        {
            shapes.back()->setBounds(pressedPoint, currentPoint);
        }
        else if(resizingLU)
        {
                selected->setBounds(currentPoint, selected->getRightBottomPoint());
        }
        else if (resizingDR)
        {
            selected->setBounds(selected->getLeftUpperPoint(), currentPoint);
        }
        else if (selected)
        {
                selected->move(currentPoint - pressedPoint);
        }
        else
        {
            creating = true;
            selected = new Rectangle(pressedPoint, pressedPoint);
            selected->setColor(workColor);
            selected->setLineColor(workPenColor);
            shapes.push_back(selected);
            selected->select(true);
        }
        update();
    }
}
void CanvasWidget::mouseReleaseEvent (QMouseEvent *)
{
    if (creating || resizingLU || resizingDR)
    {
        creating = false;
        resizingLU = false;
        resizingDR = false;
    }
}
void CanvasWidget::paintEvent (QPaintEvent *)
{
    QPainter painter(this);
    for (unsigned i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->draw(painter);
    }
}

void CanvasWidget::setColor(Color col, COLORTYPE type)
{
    cout << col;
    if (type == CTBACKGROUND) {
        workColor = col;
        if (selected)
            selected->setColor(col);
    }
    else {
        workPenColor = col;
        if (selected)
            selected->setLineColor(col);
    }
    update();
}

