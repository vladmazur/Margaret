#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->colorPickerButton, SIGNAL(colorChanged(Color, COLORTYPE)),
                     ui->canvas, SLOT(setColor(Color, COLORTYPE)));

    QObject::connect(ui->canvas, SIGNAL(changingLineWidth(int)),
                     this, SLOT(selectLineWidth(int)));

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

void MainWindow::on_LineWidthChooser_valueChanged(int arg1)
{
    ui->canvas->changeLineWidth(arg1);
}

void MainWindow::on_LineStyleChooser_currentIndexChanged(int index)
{
    ui->canvas->changeLineStyle(LineStyle(index));
}

void MainWindow::selectLineWidth(int width)
{
    ui->LineWidthChooser->setValue(width);
}
