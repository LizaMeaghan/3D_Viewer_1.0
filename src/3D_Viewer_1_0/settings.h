#ifndef SETTINGS_H
#define SETTINGS_H

#define CONTINUOUS_LINE 0
#define DASHED_LINE 1
#define CENTRAL 0
#define PARALLEL 1
#define EMPTY_VERTEX 0
#define CIRCLE_VERTEX 1
#define SQUARE_VERTEX 2

#include <QWidget>
#include <QSettings>
#include <QColorDialog>

namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT
    QColor color_lines = QColorConstants::Black;
    QColor color_background = QColorConstants::Gray;
    QColor color_polygon = QColorConstants::DarkCyan;
    QColor color_vertex = QColorConstants::Red;
    int lines_type = CONTINUOUS_LINE;
    int view_type = CENTRAL;
    int vertex_type = EMPTY_VERTEX;
    int vertex_size = 5;
    double lines_width = 2.0;
    QString settings_filename = "settings_3d_view.conf";
    QString default_settings_filename = "default_settings_3d_view.conf";
public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();
    bool flag_ok = false;

public slots:
    void get_color(QColor *lines, QColor *background, QColor *polygon, QColor *vertex);
    void get_lines_type(int *type);
    void get_lines_width(double *width);
    void get_view_type(int *type);
    void save_settings();
    void get_settings(QString filename);
    void get_vertices_type(int *type);
    void get_vertices_size(int *size);
private slots:
    void on_pushButton_3_clicked();
    void on_button_color_polygon_clicked();
    void on_button_color_background_clicked();
    void on_button_accept_clicked();
    void on_button_cancel_clicked();
    void on_comboBox_lines_type_activated(int index);
    void on_doubleSpinBox_width_lines_valueChanged(double arg1);
    void on_checkBox_central_clicked(bool checked);
    void on_checkBox_parallel_clicked(bool checked);
    void on_comboBox_vertices_type_activated(int index);
    void on_spinBox_vertices_size_valueChanged(int arg1);
    void on_pushButton_color_vertices_clicked();

private:
    Ui::settings *ui;
};

#endif // SETTINGS_H
