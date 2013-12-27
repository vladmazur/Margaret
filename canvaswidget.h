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
    bool gridShow = true;

    ShapeController * getShapeController();
signals:
    void changingLineWidth(int width);
    void changingLineStyle(LineStyle style);
    void changingColors(Color back, Color pen);
    void setPolygonSettingsVisible(bool visible);
    void setReflectionSettings(bool vert, bool horiz);
public slots:
    void setColor(Color col, COLORTYPE type);
    void deleteFigure();
    void changeFigure(FIGURESELECTED figure);
    void changeLineStyle(LineStyle style);
    void changeLineWidth(int width);
    void PolygonCornerCountChange(int count);
    void setVerticalReflection(bool isReflecting);
    void setHorizontalReflection(bool isReflecting);

    void setFreeze(bool f);

    void save();
protected:
    virtual void mousePressEvent (QMouseEvent * event);
    virtual void mouseMoveEvent (QMouseEvent * event);
    virtual void mouseReleaseEvent (QMouseEvent * event);
    virtual void paintEvent (QPaintEvent * event);
    virtual void mouseClickEvent (QMouseEvent * event);
    Point pressedPoint;
    bool creating, resizingLU, resizingDR;
    Color workColor, workPenColor;
    LineStyle workLineStyle;
    int workLineWidth=3;
    ShapeController sc;
    bool /*gridShow,*/ gridAligment;
    FIGURESELECTED workFigure;
    int workPolygonCorCount=5;
    bool isInSpecialBrokenMode = false;
    bool freeze = false;

//    QPoint m_lastPoint;
//    bool m_mouseClick = false;
};
#endif // CANVASWIDGET_H
