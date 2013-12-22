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
    void colorChanged(Color col);
public slots:

protected:
    virtual void mousePressEvent (QMouseEvent * event);
    virtual void paintEvent (QPaintEvent * event);
    void setColor(Color col);
    Color color;
};

#endif // COLORBUTTONPICKER_H