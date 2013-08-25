#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_nlesson=0;
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(7);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setPageStep(1);

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
            ui->listWidget->addItem(m_ReadLine);//below,both works.
//            ui->listWidget->insertItem(m_nlesson,m_ReadLine);//above,both works.
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
    int nrow=ui->listWidget->row(item);//获取行号
    in.seek(m_pos.at(nrow));//m_pos.at(nrow)为某一章节的开始,Lesson所在行，定位作用
    tmp+=m_str.at(nrow);//获取章节名
    tmp+="\r\n";
    for(int i=m_lin.at(nrow);i<m_lin.at(nrow+1)-1;i++)//m_pos.at(nrow+1)-1为某一章节的结束，循环表示一个章节的开始行和结束行
    {
        tmp+=in.readLine();//读一行
        tmp+="\r\n";
    }
    ui->textEdit->setText(tmp);//显示OK的文本
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

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    highlighter = new Highlighter(ui->textEdit->document());
    switch(value)
    {
        case 0:
            break;
        case 1:
            {
                QStringList wordlist;
                wordlist << "Arial" << "on" << "in" << "to";
                highlighter->setTextQueue(wordlist);
            }
        case 2:
            {
                QStringList wordlist;
                wordlist << "Arial" << "on" << "in" << "to";
                highlighter->setTextQueue(wordlist);
            }
        case 3:
            {
                QStringList wordlist;
                wordlist << "Arial" << "on" << "in" << "to";
                highlighter->setTextQueue(wordlist);
            }
        case 4:
            {
                QStringList wordlist;
                wordlist << "Arial" << "on" << "in" << "to";
                highlighter->setTextQueue(wordlist);
            }
        case 5:
            {
                QStringList wordlist;
                wordlist << "Arial" << "on" << "in" << "to";
                highlighter->setTextQueue(wordlist);
            }
        case 6:
            {
                QStringList wordlist;
                wordlist << "Arial" << "on" << "in" << "to";
                highlighter->setTextQueue(wordlist);
            }
    }
//    if(value==3)
//    {
//    QStringList wordlist;
//         wordlist << "Arial" << "on" << "in" << "to";
//    highlighter->setTextQueue(wordlist);
//    }
//    if(value==0)
//        ;
//    QPalette palette = ui->textEdit->palette();
//    palette.setColor(QPalette::Highlight, QColor::fromRgb(51, 153, 255)); //天蓝色
//    palette.setColor(QPalette::HighlightedText, QColor::fromRgb(255, 255, 255)); //白色
//    palette.setColor(QPalette::Text,QColor::fromRgb(139,139,0));
//    ui->textEdit->setPalette(palette);
//    slotFind();
}

/*slotFind()查找
void MainWindow::slotFind()
{
    QString findtxt("commitment");
    if(findtxt.isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("No input"));
    }
    else
    {
        ui->textEdit->moveCursor(QTextCursor::Start);
        if(!ui->textEdit->find(findtxt))
        {
            QMessageBox::StandardButton btn;
            btn = QMessageBox::information(this,tr("Find"),"cannot find,"+findtxt+"\ntry again?",QMessageBox::Ok,QMessageBox::Abort);
            if(btn == QMessageBox::Ok)
            {
                ui->textEdit->moveCursor(QTextCursor::Start);
                slotFind();
            }
        }
    }
}
****************************/
