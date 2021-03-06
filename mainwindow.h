#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "Figure.h"

#include "scaledialog.h"

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

    void on_PolygonCornersSplitter_valueChanged(int arg1);

    void on_VerticalReflCheck_stateChanged(int arg1);

    void on_HorizontalReflCheck_stateChanged(int arg1);

    void resizeEvent ( QResizeEvent * event );

    void open();
    bool save();
    bool saveAs();
    bool saveAsPNG();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

    QString curFile;

    QMenu   *fileMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *savePNGAct;

public slots:
    void selectLineWidth(int width);
    void selectLineStyle(LineStyle style);
    void selectColors(Color back, Color pen);
    void setPolygonSettingsVisible(bool visible);
    void setReflectionSettings(bool reflectedVer, bool reflectedGor);
    int  getScaleThrouhDialog();
};

#endif // MAINWINDOW_H
