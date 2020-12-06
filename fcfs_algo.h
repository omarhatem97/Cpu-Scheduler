#ifndef FCFS_ALGO_H
#define FCFS_ALGO_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringList"
#include "QTableWidget"
#include "QMessageBox"
#include "QMap"
#include <iostream>
#include "QVector"
#include "QtAlgorithms"
using namespace std;


float avrg = 0;


struct fcfs_process{
    QString name;
    int arrival,burst;
};


bool compare(fcfs_process p1 , fcfs_process p2)
{
    return p1.arrival < p2.arrival;
}

QVector<QPair<QString ,QPair<int,int>>> fcfs ( QVector<fcfs_process>& v)
{

    QVector<QPair<QString ,QPair<int,int>>> res;

    QVector<fcfs_process> vp = v;

    stable_sort(vp.begin(),vp.end() ,compare);



    int sum =0 ,start = 0;
    //printing the final result
    for (int i=0; i<vp.size(); i++)
    {

       //handling if the next process has arrival time after the process before it has finished
       if(vp[i].arrival > start)
       {
           start = vp[i].arrival;
       }
       int finish = start + vp[i].burst;

       res.append({vp[i].name , {start,finish}});

       //to calculate the total waiting time = departure -arrival - burst
       sum += finish -vp[i].arrival - vp[i].burst;


       start = finish;
    }


    avrg = float(sum) / float (vp.size());

    return res;

}




/*QVector<QPair <int ,QString>> fcfs ( QMap<QString, QPair<int , int>> &m)
{
    QVector<QPair <int ,QString>> vp;
    auto i = m.cbegin();
    while (i != m.cend())
    {

        QPair<int ,QString> p = {i.value().first,i.key()};
        vp.append(p);
        i++;
    } // i now is : key:"p1" , value : (2 ,3)

    sort(vp.begin(),vp.end());


    return vp;

}*/






#endif // FCFS_ALGO_H
