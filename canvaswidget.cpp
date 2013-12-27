#include "canvaswidget.h"
//#include "mainwindow.h"

#include <QFileDialog>
#include <QSvgGenerator>

#include "scaledialog.h"

int clickCount = 0;

CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent), selected(NULL), creating(false), resizingLU(false),
    resizingDR(false), gridAligment(false)
{
    workColor = Color(255,212,22,255);
    workPenColor = Color(195,25,172,255);
    workLineStyle = LineStyleSolid;
    workFigure = FSRect;
    workPolygonCorCount = 5;
}
CanvasWidget::~CanvasWidget()
{
    sc.deleteAll();
}
void CanvasWidget::mousePressEvent (QMouseEvent * event)
{
    pressedPoint.x = event->localPos().x();
    pressedPoint.y = event->localPos().y();

    if (gridShow) {
        pressedPoint.x = round(event->localPos().x()/20)*20;
        pressedPoint.y = round(event->localPos().y()/20)*20;
    }

    if(isInSpecialBrokenMode)
    {
        if (event->button() == Qt::RightButton) {
            isInSpecialBrokenMode = false;
            clickCount = 0;
        }
        else
        {
            pressedPoint.x = event->localPos().x();
            pressedPoint.y = event->localPos().y();

            if (gridShow) {
                pressedPoint.x = round(event->localPos().x()/20)*20;
                pressedPoint.y = round(event->localPos().y()/20)*20;
            }

            if (clickCount++ == 0)
            {
                if (selected)
                    selected->select(false);
                selected = NULL;
                std::vector<Point>pois;
                pois.push_back(pressedPoint);
                selected = new Broken(pois);
                selected->setType(FTBroken);
                emit setReflectionSettings(false, false);
                selected->setColor(workColor);
                selected->setLineStyle(workLineStyle);
                selected->setLineColor(workPenColor);
                selected->setLineWidth(workLineWidth);
                sc.addFigure(selected);
                selected->select(true);
            }
            else {
                ((Broken *)selected)->addPoint(pressedPoint);
            }
        }
    }
    else // not in Broken mode
    {
        if (selected)
            selected->select(false);
        selected = NULL;
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
            emit setReflectionSettings(selected->getReflectedVer(), selected->getReflectedGor());

            if (selected->getType() == FTPolygon)
                emit setPolygonSettingsVisible(true);
            else
                emit setPolygonSettingsVisible(false);

            if (event->button() == Qt::RightButton &&
                    selected->getType() == FTBroken) {
                ScaleDialog * sd = new ScaleDialog(this);
                selected->scale(sd->getNewScale()/100.0);
                selected->select(false);
                selected = NULL;
                event->ignore();
                delete sd;
            }
        }
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

        if (gridShow) {
            currentPoint.x = round(event->localPos().x()/20)*20;
            currentPoint.y = round(event->localPos().y()/20)*20;
        }

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
        else if (selected and !isInSpecialBrokenMode)
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
                return; }
            default: {
                selected = new Rectangle(pressedPoint, pressedPoint);
                break; }
            }
            emit setReflectionSettings(false, false);
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
    if (creating || resizingLU || resizingDR) {
        creating = false;
        resizingLU = false;
        resizingDR = false;
    }

//    if ((m_mouseClick) && (event->pos() == m_lastPoint)) {
//        emit mouseClickEvent;
//    }
}

void CanvasWidget::mouseClickEvent (QMouseEvent * event)
{
//    cout << "ass";
}

void CanvasWidget::paintEvent (QPaintEvent *)
{
    if(freeze)
        return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (gridShow) {
    QImage background("d:/grid.gif");

    for (int x=-10; x< width(); x=x+background.width())
        for (int y=-10; y< height(); y=y+background.height())
            painter.drawImage(x, y, background);
    }

    for (unsigned i = 0; i < sc.getCount(); ++i)
    {
        Figure * fig = sc.figureAtIndex(i);
        if (fig) {
            sc.figureAtIndex(i)->makeVertexes();
            sc.figureAtIndex(i)->draw(painter);
        }
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
        selected = NULL;
        update();
    }
}

void CanvasWidget::changeFigure(FIGURESELECTED figure)
{
    workFigure = figure;
    if (figure == FTBroken) {
        isInSpecialBrokenMode = true;
        clickCount = 0;
    }
    else
        isInSpecialBrokenMode = false;
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

void CanvasWidget::setVerticalReflection(bool isReflecting)
{
    if (selected) {
        selected->setVertReflection(isReflecting);
        update();
    }
}

void CanvasWidget::setHorizontalReflection(bool isReflecting)
{
    if (selected) {
        selected->setHoriReflection(isReflecting);
        update();
    }
}

void CanvasWidget::save()
{
    if (selected)
        selected->select(false);
    selected = NULL;
}

ShapeController * CanvasWidget::getShapeController()
{
    return &sc;
}

void CanvasWidget::setFreeze(bool f)
{
    freeze = f;
}
