#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sjf.h"
#include"roundrobin.h"
#include "QStringList"
#include "QTableWidget"
#include "QMessageBox"
#include "QMap"
#include "fcfs_algo.h"
#include "priority_non_algo.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->mylabel->hide();
    ui->quantum->hide();

}

MainWindow::~MainWindow()
{

    delete ui;
}






void MainWindow::on_fcfs_but_clicked()
{
    ui->mylabel->hide();
    ui->quantum->hide();
    schedulerAlgo = "fcfs";
    num_rows =ui->process_num->toPlainText().toInt();

    if(num_rows == 0 || num_rows< 0){ //error check for the user input
        QMessageBox Msgbox;
        Msgbox.setText("Please enter a valid number! ");
        Msgbox.exec();
    }

    ui->inputTable->setRowCount(num_rows);
    ui->inputTable->setColumnCount(3);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Process"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Arrival Time"));
    ui->inputTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Burst Time"));
}

void MainWindow::on_sjf_preemitive_but_clicked()
{
    ui->mylabel->hide();
    ui->quantum->hide();

    schedulerAlgo = "sjf_pre";

    num_rows =ui->process_num->toPlainText().toInt();

    if(num_rows == 0 || num_rows< 0){ //error check for the user input
        QMessageBox Msgbox;
        Msgbox.setText("Please enter a valid number! ");
        Msgbox.exec();
    }

    ui->inputTable->setRowCount(num_rows);
    ui->inputTable->setColumnCount(3);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Process"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Arrival Time"));
    ui->inputTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Burst Time"));

}

void MainWindow::on_sjf_non_but_clicked()
{
    ui->mylabel->hide();
    ui->quantum->hide();

    schedulerAlgo = "sjf_nonpre";

    num_rows =ui->process_num->toPlainText().toInt();

    if(num_rows == 0 || num_rows< 0){ //error check for the user input
        QMessageBox Msgbox;
        Msgbox.setText("Please enter a valid number! ");
        Msgbox.exec();
    }

    ui->inputTable->setRowCount(num_rows);
    ui->inputTable->setColumnCount(3);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Process"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Arrival Time"));
    ui->inputTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Burst Time"));
}

void MainWindow::on_priority_pre_but_clicked()
{
    ui->mylabel->hide();
    ui->quantum->hide();
    schedulerAlgo = "priority_pre";

    num_rows =ui->process_num->toPlainText().toInt();

    if(num_rows == 0 || num_rows< 0){ //error check for the user input
        QMessageBox Msgbox;
        Msgbox.setText("Please enter a valid number! ");
        Msgbox.exec();
    }

    ui->inputTable->setRowCount(num_rows);
    ui->inputTable->setColumnCount(4);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Process"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Arrival Time"));
    ui->inputTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Burst Time"));
    ui->inputTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Priority"));
}


//priority non preemitive algo
void MainWindow::on_priority_non_but_clicked()
{

    ui->mylabel->hide();
    ui->quantum->hide();
    schedulerAlgo = "priority_non";
    num_rows =ui->process_num->toPlainText().toInt();

    if(num_rows == 0 || num_rows< 0){ //error check for the user input
        QMessageBox Msgbox;
        Msgbox.setText("Please enter a valid number! ");
        Msgbox.exec();
    }

    ui->inputTable->setRowCount(num_rows);
    ui->inputTable->setColumnCount(4);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Process"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Arrival Time"));
    ui->inputTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Burst Time"));
    ui->inputTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Priority"));


}

void MainWindow::on_roundrobin_but_clicked()
{

    ui->mylabel->show();
    ui->quantum->show();
    schedulerAlgo = "roundrobin";
    num_rows =ui->process_num->toPlainText().toInt();

    if(num_rows == 0 || num_rows < 0){ //error check for the user input
        QMessageBox Msgbox;
        Msgbox.setText("Please enter a valid number! ");
        Msgbox.exec();
    }

    ui->inputTable->setRowCount(num_rows);
    ui->inputTable->setColumnCount(3);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Process"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Arrival Time"));
    ui->inputTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Burst Time"));

}

void MainWindow::on_ok_but_clicked()
{
    if(schedulerAlgo == "fcfs") //fcfs algo
    {

        QVector<fcfs_process>v;
        fcfs_process p;

        for (int i=0; i<num_rows; i++)
        {
            for (int j=0; j<3; j++)
            {
                 if(j==0) p.name = ui->inputTable->item(i,j)->text();
                 else if (j==1) p.arrival = ui->inputTable->item(i,j)->text().toInt();
                 else p.burst = ui->inputTable->item(i,j)->text().toInt();
            }
            v.append(p);
        }

        //5ra wa araf !!
        QVector<QPair<QString ,QPair<int,int>>>res =fcfs(v); // hena 5at nateget el algo
        ui->out_table->setColumnCount(res.size());
        ui->out_table->setRowCount(2);

        //displaying the result
        for (int i=0; i<res.size(); i++)
        {
           ui->out_table->setItem(0, i, new QTableWidgetItem(res[i].first));
           ui->out_table->setItem(1, i, new QTableWidgetItem(QString::number(res[i].second.first)+"->"+
                                                             QString::number(res[i].second.second)));
        }


        QString t;
        t.setNum(avrg);
        ui->waiting_time->setText("   "+t);


    }

/****************************************************************************/
    //priority non algorithim logic
    else if (schedulerAlgo == "priority_non")
    {
        //loop over the table and store the data in a vector of struct priority
        QVector<priority>v;
        for (int i=0; i<num_rows; i++)
        {
            priority p;
            for (int j=0; j<4; j++)
            {
                 if(j==0) p.processName = ui->inputTable->item(i,j)->text();
                 else if (j==1) p.arrivalTime = ui->inputTable->item(i,j)->text().toInt();
                 else if(j==2) p.burstTime= ui->inputTable->item(i,j)->text().toInt();
                 else p.Priority = ui->inputTable->item(i,j)->text().toInt();
            }
            v.append(p);

        }//forloop

        //logic
        QVector<QPair<QString ,QPair<int,int>>>res = priority_non_Algo(v); //hena 5at nateget el algo

        ui->out_table->setColumnCount(res.size());
        ui->out_table->setRowCount(2);

        //displaying the result
        for (int i=0; i<res.size(); i++)
        {
           ui->out_table->setItem(0, i, new QTableWidgetItem(res[i].first));
           ui->out_table->setItem(1, i, new QTableWidgetItem(QString::number(res[i].second.first)+"->"+
                                                             QString::number(res[i].second.second)));
        }


        QString t;
        t.setNum(average_time);
        ui->waiting_time->setText("   "+t);

    } // end of algo
/***************************************************************************/

    //priority preemitive algo
    else if (schedulerAlgo == "priority_pre")
    {
        //loop over the table and store the data in a vector of struct priority
        QVector<Priority>v;

       // QString name;
        //int burst_time, arrival_time, priority;
        for (int i=0; i<num_rows; i++)
        {
            Priority p;
            for (int j=0; j<4; j++)
            {
                 if(j==0) p.name = ui->inputTable->item(i,j)->text();
                 else if (j==1) p.arrival_time = ui->inputTable->item(i,j)->text().toInt();
                 else if(j==2) p.burst_time= ui->inputTable->item(i,j)->text().toInt();
                 else p.priority = ui->inputTable->item(i,j)->text().toInt();
            }
            v.append(p);

        }//forloop

        //logic
        QVector<QPair<QString ,QPair<int,int>>>res = priority_preemptive(v); //hena 5at nateget el algo

        ui->out_table->setColumnCount(res.size());
        ui->out_table->setRowCount(2);

        //displaying the result
        for (int i=0; i<res.size(); i++)
        {
           ui->out_table->setItem(0, i, new QTableWidgetItem(res[i].first));
           ui->out_table->setItem(1, i, new QTableWidgetItem(QString::number(res[i].second.first)+"->"+
                                                             QString::number(res[i].second.second)));
        }

        ui->waiting_time->setTextColor(Qt::blue);
        QString t;
        t.setNum(avg_time);
        ui->waiting_time->setText("   "+t);
    }








/***************************************************************************/

    //round robin algo//////////
    else if (schedulerAlgo == "roundrobin")
    {
        int quantum  = ui->quantum->toPlainText().toInt();
        QVector<round_process>v;
        for (int i=0; i<num_rows; i++)
        {
            round_process p;
            for (int j=0; j<3; j++)
            {
                 if(j==0) p.name = ui->inputTable->item(i,j)->text();
                 else if (j==1) p.arrival = ui->inputTable->item(i,j)->text().toInt();
                 else if(j==2) p.burst= ui->inputTable->item(i,j)->text().toInt();

            }
            v.append(p);

        }//forloop

        //logic
         QPair < QVector<round_process>, int> p;
         p = {v,quantum};

        QVector<QPair<QString ,QPair<int,int>>>res = roundRobin_algo(p); //hena 5at nateget el algo

        //the output
        ui->out_table->setColumnCount(res.size());
        ui->out_table->setRowCount(2);

        //displaying the result
        for (int i=0; i<res.size(); i++)
        {
           ui->out_table->setItem(0, i, new QTableWidgetItem(res[i].first));
           ui->out_table->setItem(1, i, new QTableWidgetItem(QString::number(res[i].second.first)+"->"+
                                                             QString::number(res[i].second.second)));
        }

        ui->waiting_time->setTextColor(Qt::blue);
        QString t;
        t.setNum(average);
        ui->waiting_time->setText("   "+t);
    } //end roubin

   /*************************************************************/

    else if (schedulerAlgo == "sjf_pre")
    {

       // QString name;
       //int burst_time, arrival_time;
        //loop over the table and store the data in a vector of struct priority
        QVector<SJF>v;

       // QString name;
        //int burst_time, arrival_time, priority;
        for (int i=0; i<num_rows; i++)
        {
            SJF p;
            for (int j=0; j<4; j++)
            {
                 if(j==0) p.name = ui->inputTable->item(i,j)->text();
                 else if (j==1) p.arrival_time = ui->inputTable->item(i,j)->text().toInt();
                 else if(j==2) p.burst_time= ui->inputTable->item(i,j)->text().toInt();

            }
            v.append(p);

        }//forloop

        //logic
        QVector<QPair<QString ,QPair<int,int>>>res = sjf_preemptive(v); //hena 5at nateget el algo

        ui->out_table->setColumnCount(res.size());
        ui->out_table->setRowCount(2);

        //displaying the result
        for (int i=0; i<res.size(); i++)
        {
           ui->out_table->setItem(0, i, new QTableWidgetItem(res[i].first));
           ui->out_table->setItem(1, i, new QTableWidgetItem(QString::number(res[i].second.first)+"->"+
                                                             QString::number(res[i].second.second)));
        }

        ui->waiting_time->setTextColor(Qt::blue);
        QString t;
        t.setNum(avg_time);
        ui->waiting_time->setText("   " + t);

    }


    /*************************************************************/

    else if (schedulerAlgo == "sjf_nonpre")
    {
        // QString name;
        //int burst_time, arrival_time;
         //loop over the table and store the data in a vector of struct priority
         QVector<SJF>v;

        // QString name;
         //int burst_time, arrival_time, priority;
         for (int i=0; i<num_rows; i++)
         {
             SJF p;
             for (int j=0; j<4; j++)
             {
                  if(j==0) p.name = ui->inputTable->item(i,j)->text();
                  else if (j==1) p.arrival_time = ui->inputTable->item(i,j)->text().toInt();
                  else if(j==2) p.burst_time= ui->inputTable->item(i,j)->text().toInt();

             }
             v.append(p);

         }//forloop

         //logic
         QVector<QPair<QString ,QPair<int,int>>>res = sjf_non_preemptive(v); //hena 5at nateget el algo

         ui->out_table->setColumnCount(res.size());
         ui->out_table->setRowCount(2);

         //displaying the result
         for (int i=0; i<res.size(); i++)
         {
            ui->out_table->setItem(0, i, new QTableWidgetItem(res[i].first));
            ui->out_table->setItem(1, i, new QTableWidgetItem(QString::number(res[i].second.first)+"->"+
                                                              QString::number(res[i].second.second)));
         }

         ui->waiting_time->setTextColor(Qt::blue);
         QString t;
         t.setNum(avg_time);
         ui->waiting_time->setText("   " + t);
    }

    /* to acess table elements
    int s = ui->inputTable->item(0,1)->text().toInt();
    cout << s <<endl;*/
}
