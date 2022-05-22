#include "dialogwindow.h"


DialogWindow::DialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
    ui->label->setText(QString::number(this->line));
}


DialogWindow::~DialogWindow()
{
    delete ui;
}
