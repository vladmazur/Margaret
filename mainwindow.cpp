#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->colorPickerButton, SIGNAL(colorChanged(Color, COLORTYPE)),
                     ui->canvas, SLOT(setColor(Color, COLORTYPE)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    ui->canvas->deleteFigure();
}
