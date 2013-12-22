#ifndef COLORBUTTONPICKER_H
#define COLORBUTTONPICKER_H

#include <QWidget>
#include "Color.h"

class ColorButtonPicker : public QWidget
{
    Q_OBJECT
public:
    explicit ColorButtonPicker(QWidget *parent = 0);

signals:
    void colorChanged(Color col, COLORTYPE ctype);
public slots:

protected:
    virtual void mousePressEvent (QMouseEvent * event);
    virtual void paintEvent (QPaintEvent * event);
    void setColor(Color col, COLORTYPE type);
    Color color, penColor;
};

#endif // COLORBUTTONPICKER_H
