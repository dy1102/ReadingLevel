#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mydialog.h"

namespace Ui {
class myWidget;
}

class myWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit myWidget(QWidget *parent = 0);
    ~myWidget();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::myWidget *ui;
    myDialog my2;
};

#endif // MYWIDGET_H
