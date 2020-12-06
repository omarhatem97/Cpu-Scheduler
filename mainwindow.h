#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_fcfs_but_clicked();

    void on_sjf_preemitive_but_clicked();

    void on_sjf_non_but_clicked();

    void on_priority_pre_but_clicked();

    void on_priority_non_but_clicked();

    void on_roundrobin_but_clicked();

    void on_ok_but_clicked();

private:
    Ui::MainWindow *ui;
    QString schedulerAlgo;
    int num_rows;

};

#endif // MAINWINDOW_H
