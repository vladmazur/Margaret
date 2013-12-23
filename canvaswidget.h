#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <vector>

#include "Rectangle.h"
#include "Polygon.h"
#include "Broken.h"
#include "ShapeController.h"

typedef enum {FSRect, FSPolygon, FSBroken} FIGURESELECTED;

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0); ~CanvasWidget();
    std::vector< Figure * > shapes;
    Figure* selected;
signals:
public slots:
    void setColor(Color col, COLORTYPE type);
    void deleteFigure();
    void changeFigure(FIGURESELECTED figure);
protected:
    virtual void mousePressEvent (QMouseEvent * event);
    virtual void mouseMoveEvent (QMouseEvent * event);
    virtual void mouseReleaseEvent (QMouseEvent * event);
    virtual void paintEvent (QPaintEvent * event);
    Point pressedPoint;
    bool creating, resizingLU, resizingDR;
    Color workColor, workPenColor;
    ShapeController sc;
    bool gridShow, gridAligment;
    FIGURESELECTED workFigure;
};
#endif // CANVASWIDGET_H
