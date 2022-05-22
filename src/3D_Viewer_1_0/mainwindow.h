#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opengl.h"
#include "qt_lib_includes.h"
#include "dockwidget.h"
#include "Figure.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    std::string filename;
    QColor color_lines = QColorConstants::Black;
    QColor color_background = QColorConstants::Gray;
    QColor color_polygon = QColorConstants::Cyan;
    QColor color_vertex = QColorConstants::Red;
    int lines_type = CONTINUOUS_LINE;
    double lines_width = 2.0;
    int vertex_type = EMPTY_VERTEX;
    int vertex_size = 5;
    int view_type = CENTRAL;
    QString settings_filename = "settings_3d_view.conf";

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionShow_Hide_triggered(bool hh);
    void on_actionSettings_triggered();
    void get_settings();
    void on_actionTake_screenshoot_triggered();

private:
    Ui::MainWindow *ui;
    DockWidget *dock = new DockWidget();
    settings *sett = new settings();
    void copy_figure(std::string filename);
};

#endif // MAINWINDOW_H
