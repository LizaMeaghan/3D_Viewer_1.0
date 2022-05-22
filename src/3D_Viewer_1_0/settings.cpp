#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    this->get_settings(settings_filename);
    ui->comboBox_lines_type->setCurrentIndex(this->lines_type);
    ui->doubleSpinBox_width_lines->setValue(this->lines_width);
    ui->spinBox_vertices_size->setValue(this->vertex_size);
    ui->comboBox_vertices_type->setCurrentIndex(this->vertex_type);
    this->view_type == CENTRAL ? ui->checkBox_central->setChecked(true) : ui->checkBox_parallel->setChecked(true);
}

settings::~settings()
{
    delete ui;
}

void settings::save_settings()
{
    QSettings settings(settings_filename, QSettings::IniFormat);

    settings.beginGroup("Color Set");
    settings.setValue("color_lines_r",this->color_lines.redF());
    settings.setValue("color_lines_g",this->color_lines.greenF());
    settings.setValue("color_lines_b",this->color_lines.blueF());
    settings.setValue("color_lines_a",this->color_lines.alphaF());
    settings.setValue("color_background_r",this->color_background.redF());
    settings.setValue("color_background_g",this->color_background.greenF());
    settings.setValue("color_background_b",this->color_background.blueF());
    settings.setValue("color_background_a",this->color_background.alphaF());
    settings.setValue("color_polygon_r",this->color_polygon.redF());
    settings.setValue("color_polygon_g",this->color_polygon.greenF());
    settings.setValue("color_polygon_b",this->color_polygon.blueF());
    settings.setValue("color_polygon_a",this->color_polygon.alphaF());
    settings.setValue("color_vertex_r",this->color_vertex.redF());
    settings.setValue("color_vertex_g",this->color_vertex.greenF());
    settings.setValue("color_vertex_b",this->color_vertex.blueF());
    settings.setValue("color_vertex_a",this->color_vertex.alphaF());
    settings.endGroup();

    settings.beginGroup("Lines Set");
    settings.setValue("lines_type", this->lines_type);
    settings.setValue("view_type", this->view_type);
    settings.setValue("lines_width", this->lines_width);
    settings.setValue("vertex_type", this->vertex_type);
    settings.setValue("vertex_size", this->vertex_size);
    settings.endGroup();
}

void settings::get_settings(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    settings.beginGroup("Color Set");
    this->color_lines.setRgbF(settings.value("color_lines_r").value<qreal>(),settings.value("color_lines_g").value<qreal>(),settings.value("color_lines_b").value<qreal>(),settings.value("color_lines_a").value<qreal>());
    this->color_background.setRgbF(settings.value("color_background_r").value<qreal>(),settings.value("color_background_g").value<qreal>(),settings.value("color_background_b").value<qreal>(),settings.value("color_background_a").value<qreal>());
    this->color_polygon.setRgbF(settings.value("color_polygon_r").value<qreal>(),settings.value("color_polygon_g").value<qreal>(),settings.value("color_polygon_b").value<qreal>(),settings.value("color_polygon_a").value<qreal>());
    this->color_vertex.setRgbF(settings.value("color_vertex_r").value<qreal>(),settings.value("color_vertex_g").value<qreal>(),settings.value("color_vertex_b").value<qreal>(),settings.value("color_vertex_a").value<qreal>());
    settings.endGroup();

    settings.beginGroup("Lines Set");
    this->lines_type = settings.value("lines_type").toInt();
    this->view_type = settings.value("view_type").toInt();
    this->lines_width = settings.value("lines_width").toDouble();
    this->vertex_type = settings.value("vertex_type").toInt();
    this->vertex_size = settings.value("vertex_size").toInt();
    settings.endGroup();
}

void settings::on_pushButton_3_clicked()
{
    QColorDialog *neww = new QColorDialog();
    neww->setCurrentColor(this->color_lines);
    this->color_lines = neww->getColor();
    if(!this->color_lines.isValid()) this->color_lines = QColorConstants::Black;
}

void settings::on_button_color_polygon_clicked()
{    QColorDialog *neww = new QColorDialog();
     neww->setCurrentColor(this->color_polygon);
     this->color_polygon = neww->getColor();
     if(!this->color_polygon.isValid()) this->color_polygon = QColorConstants::Cyan;
}

void settings::on_button_color_background_clicked()
{    QColorDialog *neww = new QColorDialog();
     neww->setCurrentColor(this->color_background);
     this->color_background = neww->getColor();
     if(!this->color_background.isValid()) this->color_background = QColorConstants::Gray;
}

void settings::get_color(QColor *lines, QColor *background, QColor *polygon, QColor *vertex)
{
    *lines = this->color_lines;
    *background = this->color_background;
    *polygon = this->color_polygon;
    *vertex = this->color_vertex;
}

void settings::get_lines_type(int *type)
{
    *type = this->lines_type;
}

void settings::get_lines_width(double *width)
{
    *width = this->lines_width;
}

void settings::get_view_type(int *type)
{
    *type = this->view_type;
}

void settings::get_vertices_type(int *type)
{
    *type = this->vertex_type;
}

void settings::get_vertices_size(int *size)
{
    *size = this->vertex_size;
}

void settings::on_button_accept_clicked()
{
    this->flag_ok = true;
    this->save_settings();
    this->hide();
}

void settings::on_button_cancel_clicked()
{
    this->flag_ok = false;
    this->get_settings(default_settings_filename);
    this->save_settings();
    ui->comboBox_lines_type->setCurrentIndex(this->lines_type);
    ui->doubleSpinBox_width_lines->setValue(this->lines_width);
    ui->comboBox_vertices_type->setCurrentIndex(this->vertex_type);
    ui->spinBox_vertices_size->setValue(this->vertex_size);
    this->view_type == CENTRAL ? ui->checkBox_central->setChecked(true) : ui->checkBox_parallel->setChecked(true);
}

void settings::on_comboBox_lines_type_activated(int index)
{
    this->lines_type = index;
}

void settings::on_doubleSpinBox_width_lines_valueChanged(double arg1)
{
    this->lines_width = arg1;
}

void settings::on_checkBox_central_clicked(bool checked)
{
    if(ui->checkBox_parallel->isChecked())
    {
        if(checked)
        {
            ui->checkBox_parallel->setChecked(false);
            this->view_type = CENTRAL;
        }
    }
    else
    {
        if(!checked)
        {
            ui->checkBox_central->setChecked(true);
            this->view_type = CENTRAL;
        }
    }
}


void settings::on_checkBox_parallel_clicked(bool checked)
{
    if(ui->checkBox_central->isChecked())
    {
        if(checked)
        {
            ui->checkBox_central->setChecked(false);
            this->view_type = PARALLEL;
        }
    }
    else
    {
        if(!checked)
        {
            ui->checkBox_parallel->setChecked(true);
            this->view_type = PARALLEL;
        }
    }
}


void settings::on_comboBox_vertices_type_activated(int index)
{
    this->vertex_type = index;
}


void settings::on_spinBox_vertices_size_valueChanged(int arg1)
{
    this->vertex_size = arg1;
}


void settings::on_pushButton_color_vertices_clicked()
{
     QColorDialog *neww = new QColorDialog();
     neww->setCurrentColor(this->color_vertex);
     this->color_vertex = neww->getColor();
     if(!this->color_vertex.isValid()) this->color_vertex = QColorConstants::Red;
}

