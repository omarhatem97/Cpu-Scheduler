#ifndef PRIORITY_NON_ALGO_H
#define PRIORITY_NON_ALGO_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringList"
#include "QTableWidget"
#include "QMessageBox"
#include "QMap"
#include <iostream>
#include "QVector"
using namespace std;


float average_time = 0;


struct priority {
    QString processName;
    int arrivalTime , burstTime ,Priority;
};

bool compareArrival(priority a, priority b)
{
    // If total marks are not same then
    // returns true for higher total
    if (a.arrivalTime != b.arrivalTime )
        return a.arrivalTime > b.arrivalTime;
    return (a.arrivalTime > b.arrivalTime);
}

bool comparePriority(priority a, priority b)
{
    // If total marks are not same then
    // returns true for higher total
    if (a.Priority != b.Priority )
        return a.Priority < b.Priority;
    return (a.Priority < b.Priority);
}




QVector<QPair<QString ,QPair<int,int>>> priority_non_Algo(QVector<priority> &v)
{
    QVector<QPair<QString ,QPair<int,int>>> res;

    sort(v.rbegin(), v.rend(), compareArrival); // sort elements according to arrival time

    // at first check if some elements have the same arrival time , sort them according to priority
    int element = v[0].arrivalTime;
    int idx = 0;
    for (int i=1; i<v.size(); i++)
    {
        if(v[i].arrivalTime != element){
            idx = i;
            break;
        }
    }

    sort(v.begin(),v.begin()+idx , comparePriority);
    //------------------

    int finishTime = v[0].arrivalTime + v[0].burstTime;
    QPair<int,int> time = {v[0].arrivalTime,finishTime};
    QPair<QString ,QPair<int,int>> p = {v[0].processName ,time};
    res.append(p);
    int index =0;

    //to calculate the total waiting time = departure -arrival - burst
    int sum = finishTime - v[0].arrivalTime -v[0].burstTime;

    for (int i=1; i<v.size()-1; i++)
    {

        int j = i+1 , flag = 0;
        for (j= i+1; j<v.size(); j++) {

            if(finishTime <= v[i].arrivalTime)
            {
                flag =1;
                index = j-1;
                break;
            }
        }
        if(flag)sort(v.begin()+ i , v.begin()+idx , comparePriority);
        else sort(v.begin()+ i , v.end() , comparePriority);

        QPair<int,int> time = {finishTime,finishTime+v[i].burstTime};
        finishTime += v[i].burstTime;
        QPair<QString ,QPair<int,int>> p = {v[i].processName ,time};
        res.append(p);
        sum += finishTime - v[i].arrivalTime -v[i].burstTime;

    }

    //adding the last element bec itsnot coverdd
    int pos = v.size()-1;
    time = {finishTime,finishTime+v[pos].burstTime};
    finishTime += v[pos].burstTime;
    p = {v[pos].processName ,time};
    res.append(p);

    sum += finishTime - v[pos].arrivalTime -v[pos].burstTime;
    average_time = float(sum)/float(v.size());

    return res;
}








#endif // PRIORITY_NON_ALGO_H
