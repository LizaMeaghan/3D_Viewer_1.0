#include "dockwidget.h"
#include "ui_dockwidget.h"

DockWidget::DockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DockWidget)
{
    ui->setupUi(this);
    ui->rotate_Y_slider->setRange(-180,180);
    ui->rotate_X_slider->setRange(-180,180);
    ui->rotate_Z_slider->setRange(-180,180);
    this->reset_control();
}

DockWidget::~DockWidget()
{
    this->reset_control();
    if(this->filename_to_reset) free(this->filename_to_reset);
    delete ui;
}

void DockWidget::set_op(OpenGL *op)
{
    this->op = op;
}

void DockWidget::set_filename(char *filename, int size)
{
    this->size = size;
    this->filename_to_reset = (char*)malloc(sizeof(char)*size);
    strncpy(this->filename_to_reset,filename,size);
    //
    std::string info_(filename);
    info_ += "\nNumber of lines: " + std::to_string(this->op->get_edge()) + "\nNumber of vertices: " + std::to_string(this->op->get_vertices());
    QString info = QString::fromStdString("Path to file: " + info_);
    ui->info_label->setText(info);
    //
}

void DockWidget::on_scale_plus_1_clicked()
{
    this->op->scale_(POSITIVE);
    this->op->update();
}
void DockWidget::on_scale_minus_1_clicked()
{
    this->op->scale_(NEGATIVE);
    this->op->update();
}

void DockWidget::on_reset_clicked()
{
    this->op->setfilename(this->filename_to_reset,this->size);
    this->reset_control();
    this->op->update();
}

void DockWidget::reset_control()
{
    ui->rotate_Y_slider->setValue(0);
    ui->slide_rotate_Y_info->setText(QString::number(0));
    ui->rotate_X_slider->setValue(0);
    ui->slide_rotate_X_info->setText(QString::number(0));
    ui->rotate_Z_slider->setValue(0);
    ui->slide_rotate_Z_info->setText(QString::number(0));
    ui->doubleSpinBox_X->setValue(1.0);
    ui->doubleSpinBox_Y->setValue(1.0);
    ui->doubleSpinBox_Z->setValue(1.0);
}

void DockWidget::rotate_slide_movied(QSlider *slider, QLabel *info, axis ax, int position, int current_pos)
{
    slider->valueChanged(position);
    this->op->rotate_(POSITIVE,ax,(current_pos - position));
    this->op->update();
    info->setText(QString::number(position));
}

void DockWidget::on_rotate_Y_slider_sliderMoved(int position)
{
    this->rotate_slide_movied(ui->rotate_Y_slider,ui->slide_rotate_Y_info,X,position,this->current_rot_pos_y);
    this->current_rot_pos_y = position;
}

void DockWidget::on_rotate_X_slider_sliderMoved(int position)
{
    this->rotate_slide_movied(ui->rotate_X_slider,ui->slide_rotate_X_info,Y,position,this->current_rot_pos_x);
    this->current_rot_pos_x = position;
}

void DockWidget::on_rotate_Z_slider_sliderMoved(int position)
{
    this->rotate_slide_movied(ui->rotate_Z_slider,ui->slide_rotate_Z_info,Z,position,this->current_rot_pos_z);
    this->current_rot_pos_z = position;
}

void DockWidget::on_translate_butt_pos_clicked()
{
    this->op->translate_(NEGATIVE,X,this->current_tran_pos_x);
    this->op->update();
}

void DockWidget::on_translate_but_neg_clicked()
{
    this->op->translate_(POSITIVE,X,this->current_tran_pos_x);
    this->op->update();
}

void DockWidget::on_translate_butt_pos_y_clicked()
{
    this->op->translate_(POSITIVE,Y,this->current_tran_pos_y);
    this->op->update();
}

void DockWidget::on_translate_butt_neg_y_clicked()
{
    this->op->translate_(NEGATIVE,Y,this->current_tran_pos_y);
    this->op->update();
}

void DockWidget::on_translate_butt_pos_z_clicked()
{
    this->op->translate_(POSITIVE,Z,this->current_tran_pos_z);
    this->op->update();
}


void DockWidget::on_translate_butt_neg_z_clicked()
{
    this->op->translate_(NEGATIVE,Z,this->current_tran_pos_z);
    this->op->update();
}

void DockWidget::on_doubleSpinBox_Z_valueChanged(double arg1)
{
    this->current_tran_pos_z = arg1;
}

void DockWidget::on_doubleSpinBox_Y_valueChanged(double arg1)
{
    this->current_tran_pos_y = arg1;
}

void DockWidget::on_doubleSpinBox_X_valueChanged(double arg1)
{
    this->current_tran_pos_x = arg1;
}

