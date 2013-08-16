#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include <iostream>

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
    void on_action_N_triggered();

private:
    Ui::MainWindow *ui;
    QString m_ReadLine;
    int m_nlesson;//记录多少章节
//    qint64 position;
    int m_linecount;
    QVector<int> m_pos;//记录行号
    QVector<int> m_lin;//记录行号
    QVector<QString> m_str;//行内容,Lesson<1、2、3.....100>
};

#endif // MAINWINDOW_H
