#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
//#include "QRectangle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();

    void on_rectangleBu_pressed();

    void on_polygonBu_pressed();

    void on_brokenBu_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
