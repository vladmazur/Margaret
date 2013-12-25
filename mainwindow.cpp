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
    QObject::connect(ui->canvas, SIGNAL(setReflectionSettings(bool, bool)),
                     this, SLOT(setReflectionSettings(bool,bool)));

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
    switch (style) {
    case LineStyleSolid:
        ui->LineStyleChooser->setCurrentIndex(0);
        break;
    case LineStyleDotted:
        ui->LineStyleChooser->setCurrentIndex(1);
        break;
    case LineStyleDashed:
        ui->LineStyleChooser->setCurrentIndex(2);
        break;
    default:
        break;
    }
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

void MainWindow::setReflectionSettings(bool reflectedVer, bool reflectedGor)
{
    ui->VerticalReflCheck->setChecked(reflectedVer);
    ui->HorizontalReflCheck->setChecked(reflectedGor);
}

void MainWindow::on_PolygonCornersSplitter_valueChanged(int arg1)
{
    ui->canvas->PolygonCornerCountChange(arg1);
}

void MainWindow::on_VerticalReflCheck_stateChanged(int arg1)
{
    ui->canvas->setVerticalReflection(bool(arg1));
}

void MainWindow::on_HorizontalReflCheck_stateChanged(int arg1)
{
    ui->canvas->setHorizontalReflection(bool(arg1));
}

void MainWindow::on_saveBu_pressed()
{
    ui->canvas->saveSVG();
}
