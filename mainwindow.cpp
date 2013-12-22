#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    scene = new QGraphicsScene(this);
//    ui->graphicsView->setScene(scene);

//    QBrush greenBrush(Qt::green);
//    QBrush blueBrush(Qt::blue);
//    QPen outlinePen(Qt::black);
//    outlinePen.setWidth(2);

//    rectangle = scene->addRect(100, 0, 80, 100, outlinePen, blueBrush);
//    rectangle->setFlag(QGraphicsItem::ItemIsMovable);

//    // addEllipse(x,y,w,h,pen,brush)
//    ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);
//    ellipse->setFlag(QGraphicsItem::ItemIsMovable);

//    text = scene->addText("bogotobogo.com", QFont("Arial", 20) );
//    // movable text
//    text->setFlag(QGraphicsItem::ItemIsMovable);

//    QPolygonF Triangle;
//    Triangle.append(QPointF(-10.,0));
//    Triangle.append(QPointF(0.,-10));
//    Triangle.append(QPointF(10.,0));
//    Triangle.append(QPointF(-10.,0));

//    poly = scene->addPolygon(Triangle, outlinePen, greenBrush);
//    poly->setFlag(QGraphicsItem::ItemIsMovable);

//    ui->graphicsView->scale(0.8, 0.5);
}

MainWindow::~MainWindow()
{
    delete ui;
}
