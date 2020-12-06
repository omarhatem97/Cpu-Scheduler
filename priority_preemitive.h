#ifndef PRIORITY_PREEMITIVE_H
#define PRIORITY_PREEMITIVE_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringList"
#include "QTableWidget"
#include "QMessageBox"
#include "QMap"
#include <iostream>
#include "QVector"
#include "queue"
using namespace std;


float average_time = 0;




struct priority_process
{
    QString name;
    int arrival , burst, priority;
};


struct CustomCompare
{
    bool operator()(const priority_process& lhs, const priority_process& rhs)
    {
        return lhs.priority < rhs.priority;
    }
};



bool compareArrival(priority_process a, priority_process b)
{
    if (a.arrival != b.arrival )
        return a.arrival > b.arrival;
    return (a.arrival > b.arrival);
 }


QVector<QPair<QString ,QPair<int,int> > > priority_pre_Algo(QVector<priority_process>v)
{
    QVector<QPair<QString ,QPair<int,int>>> res;
    sort(v.rbegin(), v.rend(), compareArrival); // sort elements according to arrival time

    //bsahel 3ala nafsy abl ma append fel vector

    QPair<QString ,QPair<int,int>> big;
    QPair<int,int> small;

    //endtashel


    QMap<QString,int> remainingTime; // remaining time for each process

    priority_queue<priority_process,vector<priority_process>, CustomCompare > pq; // queue of processes in order to be executed

    //initializing priority queue and remaining time
    for (int i =0; i<v.size(); i++)
    {
        remainingTime[v[i].name] = v[i].burst;
    }


    //some tafaha
    int start = 0 , end =0; // start and end time

    int idx=0;
    pq.push(v[0]);

    while (pq.size()!=0)
    {
        priority_process process = pq.top();
        for ( int i= idx+1; i<v.size(); i++) //collecting the processes that has arrived during the running time of the
        {                                    //current process
            if(remainingTime[v[i].name] > v[i].arrival)
            {
                pq.push(v[i]);
            }
            else{ idx =i; break;}
        }

        while (pq.size() != 0)
        {

        }


    }//END WHILE


    return res;
}






#endif // PRIORITY_PREEMITIVE_H
