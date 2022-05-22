#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->openGLWidget->hide();
    this->dock->set_op(ui->openGLWidget);
    ui->actionShow_Hide->setEnabled(ui->openGLWidget->open_flag);
    ui->actionTake_screenshoot->setEnabled(ui->openGLWidget->open_flag);
    sett->get_settings(settings_filename);
}

MainWindow::~MainWindow()
{
    sett->save_settings();
    delete ui;
}

void MainWindow::copy_figure(std::string filename)
{
    char buffer[filename.length()+1];
    strncpy(buffer,filename.c_str(),filename.length()+1);
    ui->openGLWidget->setfilename(buffer,filename.length()+1);
    //
    this->get_settings();
    ui->openGLWidget->set_view_type(view_type);
    ui->openGLWidget->set_lines_width(lines_width);
    ui->openGLWidget->set_colors(color_lines,color_background,color_polygon,color_vertex);
    ui->openGLWidget->set_lines_type(lines_type);
    ui->openGLWidget->set_vertex_type(vertex_type);
    ui->openGLWidget->set_vertex_size(vertex_size);
    //
    ui->openGLWidget->show();
    this->dock->set_filename(buffer,filename.length()+1);
    ui->actionShow_Hide->setEnabled(ui->openGLWidget->open_flag);
    ui->actionTake_screenshoot->setEnabled(ui->openGLWidget->open_flag);
}

void MainWindow::on_actionOpen_triggered()
{
    this->filename = QFileDialog::getOpenFileName(this,tr("Open file"), "/home" ,tr("Object's  files (*.obj)")).toUtf8().constData();
    if(this->filename != "")
        copy_figure(this->filename);
}

void MainWindow::on_actionClose_triggered()
{
    //
    dock->hide();
    dock->reset_control();
    //
    if(ui->openGLWidget->open_flag) ui->openGLWidget->figure.free_figure();
    ui->openGLWidget->open_flag = false;
    ui->actionShow_Hide->setEnabled(ui->openGLWidget->open_flag);
    ui->actionShow_Hide->setChecked(ui->openGLWidget->open_flag);
    ui->actionTake_screenshoot->setEnabled(ui->openGLWidget->open_flag);
    ui->openGLWidget->close();
}

void MainWindow::on_actionShow_Hide_triggered(bool hh)
{
    if(ui->openGLWidget->open_flag)
    {
    addDockWidget(Qt::LeftDockWidgetArea,dock);
    hh ? dock->show() : dock->hide();
    }
}

void MainWindow::get_settings()
{
        sett->get_view_type(&view_type);
        sett->get_lines_width(&lines_width);
        sett->get_lines_type(&lines_type);
        sett->get_color(&color_lines,&color_background,&color_polygon,&color_vertex);
        sett->get_vertices_type(&vertex_type);
        sett->get_vertices_size(&vertex_size);
}


void MainWindow::on_actionSettings_triggered()
{
    this->sett->show();
}

void MainWindow::on_actionTake_screenshoot_triggered()
{
    if(ui->openGLWidget->open_flag)
    {
        const time_t tm = time(nullptr);
        char buf[128];
        strftime(buf,std::size(buf),"%d.%m.%Y_%H:%M:%S", localtime(&tm));
        std::string jpeg(buf);
        std::string bmp(buf);
        jpeg += "_screen_3D.jpeg";
        bmp += "_screen_3D.bmp";
        QPixmap screenshot(ui->openGLWidget->size());
        ui->openGLWidget->render(&screenshot);
        screenshot.save(QString::fromStdString(jpeg),"JPEG");
        screenshot.save(QString::fromStdString(bmp),"BMP");
    }
}


