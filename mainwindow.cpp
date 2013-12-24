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
    QObject::connect(ui->canvas, SIGNAL(changingLineStyle(LineStyle)),
                     this, SLOT(selectLineStyle(LineStyle)));
    QObject::connect(ui->canvas, SIGNAL(changingColors(Color,Color)),
                     this, SLOT(selectColors(Color,Color)));
    QObject::connect(ui->canvas, SIGNAL(setPolygonSettingsVisible(bool)),
                     this, SLOT(setPolygonSettingsVisible(bool)));

//    ui->canvas->raise();
//    ui->grid->lower();

    setPolygonSettingsVisible(false);
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
    setPolygonSettingsVisible(false);
}

void MainWindow::on_polygonBu_pressed()
{
    ui->canvas->changeFigure(FSPolygon);
    setPolygonSettingsVisible(true);
}

void MainWindow::on_brokenBu_pressed()
{
    ui->canvas->changeFigure(FSBroken);
    setPolygonSettingsVisible(false);
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

void MainWindow::selectLineStyle(LineStyle style)
{
    ui->LineStyleChooser->setCurrentIndex((int)style);
}

void MainWindow::selectColors(Color back, Color pen)
{
    ui->colorPickerButton->selectColors(back, pen);
}

void MainWindow::setPolygonSettingsVisible(bool visible)
{
    ui->PolygonCornersSplitter->setVisible(visible);
    ui->PolygonCornersSplitterLabel->setVisible(visible);
}

void MainWindow::on_PolygonCornersSplitter_valueChanged(int arg1)
{
    ui->canvas->PolygonCornerCountChange(arg1);
}
