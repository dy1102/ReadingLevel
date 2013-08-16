#include "mydialog.h"
#include "ui_mydialog.h"

myDialog::myDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog)
{
    ui->setupUi(this);
}

myDialog::~myDialog()
{
    delete ui;
}

void myDialog::on_pushButton_clicked()
{
    if(ui->lineEdit1->text()==tr("qt")&&ui->lineEdit2->text()==tr("123"))
        accept();
    else
        return;
}
