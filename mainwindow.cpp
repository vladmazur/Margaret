#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

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

    createActions();
    createMenus();
}

void MainWindow::createActions()
 {
     openAct = new QAction(tr("&Open..."), this);
     openAct->setShortcuts(QKeySequence::Open);
     openAct->setStatusTip(tr("Open an existing file"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     saveAct = new QAction(tr("&Save..."), this);
     saveAct->setShortcuts(QKeySequence::Save);
     saveAct->setStatusTip(tr("Save this file on a disk"));
     connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

     savePNGAct = new QAction(tr("&Save as PNG..."), this);
     saveAct->setStatusTip(tr("Save this file on a disk as PNG"));
     connect(savePNGAct, SIGNAL(triggered()), this, SLOT(saveAsPNG()));
}

void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(openAct);
     fileMenu->addAction(saveAct);
     fileMenu->addAction(savePNGAct);
 }

void MainWindow::loadFile(const QString &fileName)
{
    ui->canvas->getShapeController()->loadFromXML(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    ui->canvas->getShapeController()->saveToXML(fileName);
    curFile = fileName;
    return true;
}

void MainWindow::open()
{
    ui->canvas->setFreeze(true);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open MGT"),
                                                    QDir::currentPath(), tr("MGT files (*.mgt)"));
    if (!fileName.isEmpty())
        loadFile(fileName);
    ui->canvas->setFreeze(false);
    ui->canvas->update();
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
         return saveAs();
     } else {
         return saveFile(curFile);
     }
}

bool MainWindow::saveAs()
 {
     QString fileName = QFileDialog::getSaveFileName(this, tr("Save MGT"),
                                                     QDir::currentPath(), tr("MGT files (*.mgt)"));
     if (fileName.isEmpty())
         return false;

     return saveFile(fileName);
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

int MainWindow::getScaleThrouhDialog()
{
    int result = 100;

    QDialog * sd = new ScaleDialog(this);
    sd->show();

    return result;
}

void MainWindow::resizeEvent ( QResizeEvent * event )
{
    ui->canvas->setGeometry(150, 20, width()-160, height()-80);
    ui->grid->setGeometry(0, 0, width()-160, height()-80);
}

bool MainWindow::saveAsPNG()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PNG"),
                                                    QDir::currentPath(), tr("PNG files (*.png)"));
    if (fileName.isEmpty())
        return false;

    ui->canvas->gridShow = false;

    QPixmap pixmap(ui->canvas->size());
    ui->canvas->render(&pixmap, QPoint(), QRegion(0,0,ui->canvas->width(), ui->canvas->height()));
    return pixmap.save(fileName);

    ui->canvas->gridShow = true;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->canvas->gridShow = arg1;
    ui->canvas->update();
}
