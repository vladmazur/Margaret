#include "colorbuttonpicker.h"
#include <QPainter>
#include <QColorDialog>

ColorButtonPicker::ColorButtonPicker(QWidget *parent) :
    QWidget(parent)
{
}

void ColorButtonPicker::mousePressEvent (QMouseEvent * event)
{
    QColor col = QColorDialog::getColor(Qt::white, this);
    color.red = col.red();
    color.green = col.green();
    color.blue = col.blue();
    color.alpha = col.alpha();
    update();
}

void ColorButtonPicker::paintEvent (QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing);
    painter.setPen(QColor(color.red, color.green, color.blue, color.alpha));
    painter.setBrush(QBrush(QColor(color.red, color.green, color.blue, color.alpha)));
    QRectF rectangle(0.5, 0.5, 60, 60);
    painter.drawRoundedRect(rectangle, 10.0, 10.0);
}
