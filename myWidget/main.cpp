#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myWidget w;
    myDialog myd;
    if(myd.exec()==myDialog::Accepted)
    {
    w.show();
    return a.exec();
    }
    else
        return 0;
}
