#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(QWidget *parent = 0);
    bool gridShow;
signals:

public slots:

protected:
    virtual void paintEvent (QPaintEvent * event);
};

#endif // GRIDWIDGET_H
