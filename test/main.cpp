#include "mywidget.h"
#include <QApplication>
#include "mydialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myWidget w;
    myDialog my;
    if(my.exec()==QDialog::Accepted)
    {
    w.show();
    
    return a.exec();
    }
    else
        return 0;
}
