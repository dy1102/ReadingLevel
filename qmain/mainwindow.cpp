#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_nlesson=0;
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QFile file("nce4.txt");
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,"Information",tr("anything you want tell user"));
        return ;
    }
    QTextStream in(&file);
    QString LessonString("Lesson");
    ui->label->setText("请稍等");
    while(!in.atEnd())
    {
        m_ReadLine=in.readLine();
        ++m_linecount;//行号计数，由于QTextStream类没有提供查询行号的函数，人工计数
        if(m_ReadLine.indexOf(LessonString)!=-1)
        {
            m_pos.push_back((int)in.pos());//获取当前Lesson位置,压入m_pos对象
            ++m_nlesson;//记录多少章节，每次获取"Lesson"自增
            m_lin.push_back(m_linecount);//压入当前Lesson所在行号
            m_str.push_back(m_ReadLine);//章节名
            m_ReadLine=m_ReadLine.trimmed();
            ui->listWidget->addItem(m_ReadLine);
        }
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QFile file("nce4.txt");
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,"Information",tr("anything you want tell user"));
        return ;
    }
    QTextStream in(&file);
    QString tmp;
    in.seek(m_pos.at(4));//m_pos.at(i)为某一章节的开始,Lesson所在行
    tmp+=m_str.at(4);//获取章节名
    tmp+="\r\n";
    for(int i=m_lin.at(4);i<m_lin.at(5)-1;i++)//m_pos.at(i+1)-1为某一章节的结束，循环标示一个章节的开始行和结束行
    {
        tmp+=in.readLine();//读一行
        tmp+="\r\n";
        ui->textEdit->setText(tmp);
    }
    //    in.seek(m_pos.at(4));
    //    while(in.pos()!=m_pos.at(5))
    //    {
    //        m_ReadLine=in.readLine();
    //        ui->textEdit->setText(m_ReadLine);
    //    }
    //    QString qstr = QString::number(m_nlesson);
    //    QMessageBox::information(this,"Information",qstr);
    //    ui->textEdit->setText(qstr);
}
