#include "canvaswidget.h"
//#include "mainwindow.h"

CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent), selected(NULL), creating(false), resizingLU(false),
    resizingDR(false), gridShow(false), gridAligment(false)
{
    workColor = Color(255,212,22,255);
    workPenColor = Color(195,25,172,255);
}
CanvasWidget::~CanvasWidget()
{
        sc.deleteAll();
}
void CanvasWidget::mousePressEvent (QMouseEvent * event)
{
    pressedPoint.x = event->localPos().x();
    pressedPoint.y = event->localPos().y();
    if (selected) selected->select(false); selected = NULL;
//    emit setPolygonSettingsVisible(false);
    for (unsigned i = sc.getCount(); i > 0; --i)
    {
        if (sc.figureAtIndex(i-1)->includesPoint(pressedPoint))
        {
            selected = sc.figureAtIndex(i-1);
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
        }
    }

    if (selected)
    {
        emit changingLineWidth(selected->getLine().thickness);
        emit changingLineStyle(selected->getLine().style);
        emit changingColors(selected->getColor(), selected->getLine().color);

        if (selected->getType() == FTPolygon)
            emit setPolygonSettingsVisible(true);
        else
            emit setPolygonSettingsVisible(false);
    }
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
            sc.allFigures().back()->setBounds(pressedPoint, currentPoint);
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

            switch (workFigure) {
            case FSRect: {
                selected = new Rectangle(pressedPoint, pressedPoint);
                selected->setType(FTRect);
                break; }
            case FSPolygon: {
                selected = new Polygon(pressedPoint, pressedPoint, 5, Color(), Line());
                selected->setType(FTPolygon);
                ((Polygon *) selected)->setCountOfCorners(workPolygonCorCount);
                emit setPolygonSettingsVisible(true);
                break; }
            case FSBroken: {
                std::vector<Point>pois;
                selected = new Broken(pois);
                selected->setType(FTBroken);
                break; }
            default: {
                selected = new Rectangle(pressedPoint, pressedPoint);
                break; }
            }
            selected->setColor(workColor);
            selected->setLineStyle(workLineStyle);
            selected->setLineColor(workPenColor);
            selected->setLineWidth(workLineWidth);
            sc.addFigure(selected);
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
    for (unsigned i = 0; i < sc.getCount(); ++i)
    {
        sc.figureAtIndex(i)->draw(painter);
    }    
}

void CanvasWidget::setColor(Color col, COLORTYPE type)
{
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

void CanvasWidget::deleteFigure()
{
    if (selected) {
        sc.deleteByNumber(selected->getNumber());
        update();
    }
}

void CanvasWidget::changeFigure(FIGURESELECTED figure)
{
    workFigure = figure;
}

void CanvasWidget::changeLineStyle(LineStyle style)
{
    workLineStyle = style;
    if (selected) {
        selected->setLineStyle(style);
        update();
    }
}

void CanvasWidget::changeLineWidth(int width)
{
    workLineWidth = width;
    if (selected) {
        selected->setLineWidth(width);
        update();
    }
}

void CanvasWidget::PolygonCornerCountChange(int count)
{
    workPolygonCorCount = count;
    if(selected) {
        ((Polygon *)selected)->setCountOfCorners(count);
        update();
    }
}
