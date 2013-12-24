#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "Figure.h"

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

    void on_LineWidthChooser_valueChanged(int arg1);

    void on_LineStyleChooser_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

public slots:
    void selectLineWidth(int width);
    void selectLineStyle(LineStyle style);
    void selectColors(Color back, Color pen);
};

#endif // MAINWINDOW_H
