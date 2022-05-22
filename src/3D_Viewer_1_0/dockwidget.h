#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include "opengl.h"
#include "qslider.h"

namespace Ui {
class DockWidget;
}

class DockWidget : public QDockWidget
{
    Q_OBJECT
    OpenGL *op;
    char *filename_to_reset = new char();
    int current_rot_pos_y = 0;
    int current_rot_pos_x = 0;
    int current_rot_pos_z = 0;
    double current_tran_pos_x = 1;
    double current_tran_pos_y = 1;
    double current_tran_pos_z = 1;
public:
    explicit DockWidget(QWidget *parent = nullptr);
    ~DockWidget();
    void set_op(OpenGL *op);
    void set_filename(char* filename,int size);
    void reset_control();
    int size = 0;

private slots:
    void on_scale_plus_1_clicked();
    void on_scale_minus_1_clicked();
    void on_reset_clicked();
    void on_rotate_Y_slider_sliderMoved(int position);
    void on_rotate_X_slider_sliderMoved(int position);
    void rotate_slide_movied(QSlider *slider, QLabel *info, axis ax, int position, int current_pos);
    void on_rotate_Z_slider_sliderMoved(int position);
    void on_translate_butt_pos_clicked();
    void on_translate_but_neg_clicked();
    void on_translate_butt_pos_y_clicked();
    void on_translate_butt_neg_y_clicked();

    void on_translate_butt_pos_z_clicked();

    void on_translate_butt_neg_z_clicked();

    void on_doubleSpinBox_Z_valueChanged(double arg1);

    void on_doubleSpinBox_Y_valueChanged(double arg1);

    void on_doubleSpinBox_X_valueChanged(double arg1);

private:
    Ui::DockWidget *ui;
};

#endif // DOCKWIDGET_H
