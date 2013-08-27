#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_nlesson=0;
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(6);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setPageStep(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    //QFile file("nce4.txt");
    QFile file("/sdcard/nce4.txt");
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
        m_ReadLine=in.readLine();//从in中读一行
        ++m_linecount;//行号计数，由于QTextStream类没有提供查询行号的函数，人工计数
        if(m_ReadLine.indexOf(LessonString)!=-1)
        {
            m_pos.push_back((int)in.pos());//获取当前Lesson位置in.pos(),压入m_pos对象
            ++m_nlesson;//记录多少章节，每次获取"Lesson"自增
            m_lin.push_back(m_linecount);//压入当前Lesson所在行号
            m_str.push_back(m_ReadLine);//章节名，当前行内容
            m_ReadLine=m_ReadLine.trimmed();
            ui->listWidget->addItem(m_ReadLine);//below,both works.
//            ui->listWidget->insertItem(m_nlesson,m_ReadLine);//above,both works.
        }
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //QFile file("nce4.txt");
    QFile file("/sdcard/nce4.txt");
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,"Information",tr("anything you want tell user"));
        return ;
    }
    QTextStream in(&file);
    QString tmp;
    int nrow=ui->listWidget->row(item);//获取listWidget行号
    in.seek(m_pos.at(nrow));//m_pos.at(nrow)为某一章节的开始,即Lesson所在行,定位作用
    tmp+=m_str.at(nrow);//获取章节名
    tmp+="\r\n";
    if(nrow!=m_lin.count()-1)//如果不是最后一章节,m_lin.count()-1为倒数第二章节
        for(int i=m_lin.at(nrow);i<m_lin.at(nrow+1)-1;i++)//m_pos.at(nrow+1)-1为某一章节的结束，"-1"把下个章节的标题行减掉，循环表示一个章节的开始行和结束行
        {
            tmp+=in.readLine();//读一行
            tmp+="\r\n";
        }
    else//如果是最后一个章节，循环方式有区别
        while(!in.atEnd())
        {
            tmp=in.readAll();//读最后一章的全部
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
    //QFile file("nce4_words");
    QFile file("/sdcard/nce4_words");
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,"Information",tr("anything you want tell user"));
        return ;
    }
    QTextStream in(&file);
    QString tmp;//单词、等级
    QString tmp1;//单词
    int tmp2;//等级
    QStringList lst0;//单词List
    QStringList lst1;//单词List
    QStringList lst2;//单词List
    QStringList lst3;//单词List
    QStringList lst4;//单词List
    QStringList lst5;//单词List

    tmp=in.readLine();//读第一行，但是丢弃不使用
    while(!in.atEnd())
    {
        tmp=in.readLine();
        tmp1=tmp.split('\t').first();//通过/t分解每一行内容
        tmp2=tmp.split('\t').last().toInt();//first部分为单词,last部分为等级
        switch(tmp2)
        {
            case 0:lst0.push_back(tmp1);
                break;
            case 1:lst1.push_back(tmp1);
                break;
            case 2:lst2.push_back(tmp1);
                break;
            case 3:lst3.push_back(tmp1);
                break;
            case 4:lst4.push_back(tmp1);
                break;
            case 5:lst5.push_back(tmp1);
                break;
        }
    }
//    qDebug()<<tmp1<<"\t"<<tmp2;
    m_words.insert(0,lst0);//add to QMap<int,QStringList>
    m_words.insert(1,lst1);//add to QMap<int,QStringList>
    m_words.insert(2,lst2);//add to QMap<int,QStringList>
    m_words.insert(3,lst3);//add to QMap<int,QStringList>
    m_words.insert(4,lst4);//add to QMap<int,QStringList>
    m_words.insert(5,lst5);//add to QMap<int,QStringList>
    switch(value)
    {
        case 0:
            break;
        case 1:
            {
                //查找等级为0的单词，并保存在wordlist列表中
                QStringList wordlist;
                QMap<int,QStringList>::iterator it=m_words.find(0);
                if(it!=m_words.end())
                    wordlist=it.value();
                highlighter->setTextQueue(wordlist);
            }
        break;
        case 2:
            {
                QStringList wordlist;
                QMap<int,QStringList>::iterator it=m_words.find(0);
                if(it!=m_words.end())
                    wordlist=it.value();
                //查找等级为1的单词，并添加到等级为0的列表后面，下同
                it=m_words.find(1);
                if(it!=m_words.end())
                    wordlist+=it.value();
                highlighter->setTextQueue(wordlist);
            }
        break;
        case 3:
            {
                QStringList wordlist;
                QMap<int,QStringList>::iterator it=m_words.find(0);
                if(it!=m_words.end())
                    wordlist=it.value();
                it=m_words.find(1);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(2);
                if(it!=m_words.end())
                    wordlist+=it.value();
                highlighter->setTextQueue(wordlist);
            }
        break;
        case 4:
            {
                QStringList wordlist;
                QMap<int,QStringList>::iterator it=m_words.find(0);
                if(it!=m_words.end())
                    wordlist=it.value();
                it=m_words.find(1);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(2);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(3);
                if(it!=m_words.end())
                    wordlist+=it.value();
                highlighter->setTextQueue(wordlist);
            }
        break;
        case 5:
            {
                QStringList wordlist;
                QMap<int,QStringList>::iterator it=m_words.find(0);
                if(it!=m_words.end())
                    wordlist=it.value();
                it=m_words.find(1);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(2);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(3);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(4);
                if(it!=m_words.end())
                    wordlist+=it.value();
                highlighter->setTextQueue(wordlist);
            }
        break;
        case 6:
            {
                QStringList wordlist;
                QMap<int,QStringList>::iterator it=m_words.find(0);
                if(it!=m_words.end())
                    wordlist=it.value();
                it=m_words.find(1);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(2);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(3);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(4);
                if(it!=m_words.end())
                    wordlist+=it.value();
                it=m_words.find(5);
                if(it!=m_words.end())
                    wordlist+=it.value();
                highlighter->setTextQueue(wordlist);
            }
        break;
    }
//    QPalette palette = ui->textEdit->palette();
//    palette.setColor(QPalette::Highlight, QColor::fromRgb(51, 153, 255)); //天蓝色
//    palette.setColor(QPalette::HighlightedText, QColor::fromRgb(255, 255, 255)); //白色
//    palette.setColor(QPalette::Text,QColor::fromRgb(139,139,0));
//    ui->textEdit->setPalette(palette);
//    slotFind();
}

/**slotFind()查找
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
