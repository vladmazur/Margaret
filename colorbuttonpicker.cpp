#include "colorbuttonpicker.h"
#include <QPainter>
#include <QColorDialog>
#include <QMouseEvent>
#include "Point.h"

ColorButtonPicker::ColorButtonPicker(QWidget *parent) :
    QWidget(parent)
{
    color = Color(255,212,22,255);
    penColor = Color(195,25,172,255);
}

void ColorButtonPicker::mousePressEvent (QMouseEvent * event)
{
    Point p(event->localPos().x(), event->localPos().y());
    Point p1(15,15), p2(45,45);
    COLORTYPE ctype;
    QColor initCol;
    if ((p1.x <= p.x) && (p1.y <= p.y) &&
            (p2.x >= p.x) && (p2.y >= p.y)) {
        ctype = CTBACKGROUND;
        initCol = QColor(color.red, color.green, color.blue, color.alpha);
    }
    else {
        ctype = CTPEN;
        initCol = QColor(penColor.red, penColor.green, penColor.blue, penColor.alpha);
    }

    QColor col = QColorDialog::getColor(initCol, this, "Choose color",
                                        QColorDialog::ShowAlphaChannel);
    if (col.isValid()) {
        Color c(col.red(), col.green(), col.blue(), col.alpha());
        setColor(c, ctype);
        update();
    }
}

void ColorButtonPicker::paintEvent (QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing);

    painter.setPen(Qt::black/*QColor(penColor.red, penColor.green, penColor.blue, penColor.alpha)*/);
    painter.setBrush(QBrush(QColor(penColor.red, penColor.green, penColor.blue, penColor.alpha)));
    QRectF rectangle(0.5, 0.5, 60, 60);
    painter.drawRoundedRect(rectangle, 10.0, 10.0);

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(QColor(color.red, color.green, color.blue, color.alpha)));
    QRectF rectangleInside(15, 15, 30, 30);
    painter.drawRoundedRect(rectangleInside, 5.0, 5.0);
}

void ColorButtonPicker::setColor(Color col, COLORTYPE type)
{
    if (type == CTBACKGROUND) {
        if(color != col) {
            color = col;
        }
    } else {
        if(penColor != col) {
            penColor = col;
        }
    }

    emit colorChanged(col, type);
}
