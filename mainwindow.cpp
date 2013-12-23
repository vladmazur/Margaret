#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->colorPickerButton, SIGNAL(colorChanged(Color, COLORTYPE)),
                     ui->canvas, SLOT(setColor(Color, COLORTYPE)));

    ui->canvas->raise();
//    ui->grid->lower();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    ui->canvas->deleteFigure();
}

void MainWindow::on_rectangleBu_pressed()
{
    ui->canvas->changeFigure(FSRect);
}

void MainWindow::on_polygonBu_pressed()
{
    ui->canvas->changeFigure(FSPolygon);
}

void MainWindow::on_brokenBu_pressed()
{
    ui->canvas->changeFigure(FSBroken);
}
