#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QDialog>
#include "ui_dialogwindow.h"
#include "Line.h"

#include <QString>

namespace Ui {
class DialogWindow;
}

class DialogWindow : public QDialog
{
public:
    Q_OBJECT
    int line;
public:
    explicit DialogWindow(QWidget *parent = nullptr);
    ~DialogWindow();
    void setLine(int ll){
        this->line = ll;
    }

private:
    Ui::DialogWindow *ui;
};

#endif // DIALOGWINDOW_H
