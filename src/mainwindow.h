#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include <iostream>
#include <QListWidgetItem>
#include <cctype>
#include <QDebug>
#include <string>
#include "highlighter.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

//    void slotFind();

    Highlighter *highlighter;

    QString m_ReadLine;
    int m_nlesson;//记录多少章节
    int m_linecount;
    QVector<int> m_pos;//记录章节开始的位置
    QVector<int> m_lin;//记录行号
    QVector<QString> m_str;//行内容,Lesson<1、2、3.....100>
    QMap<int,QStringList> m_words;
};

#endif // MAINWINDOW_H
