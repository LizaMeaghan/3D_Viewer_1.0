#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QOpenGLWidget>

namespace Ui {
class Form;
}

class Form : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private:
    Ui::Form *ui;
};

#endif // FORM_H
