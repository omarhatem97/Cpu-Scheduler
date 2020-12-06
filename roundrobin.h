#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringList"
#include "QTableWidget"
#include "QMessageBox"
#include<algorithm>
#include "QMap"
#include"queue"
#include <iostream>
using namespace std;



float average  = 0;


struct round_process{
    QString name;
    int burst ,arrival;
};


bool compareArival ( round_process x , round_process y)
{
    if(x.arrival != y.arrival) return x.arrival < y.arrival;
    return (x.arrival<y.arrival);
}


bool check(queue<round_process> q , int end) //check if all arrival times are greater than end
{
    while (q.size()!= 0)
    {
        round_process process = q.front();
        if(process.arrival <= end)
        {
            return 0;
        }
        q.pop();
    }
    return 1;
}



QVector<QPair<QString ,QPair<int,int>>> roundRobin_algo(QPair < QVector<round_process>, int>& p)
{
    int quantum = p.second;
    QVector<round_process> v = p.first;

    QVector<QPair<QString ,QPair<int,int>>>res;

    //bsahel 3ala nafsy abl ma append fel vector

    QPair<QString ,QPair<int,int>> big;
    QPair<int,int>small;

    //endtashel

    sort(v.begin(),v.end() ,compareArival); // sort elements according to arrival time

    int start = 0 , end =0; // start and end time
    QMap<QString,int> remainingTime; // remaining time for each process

    queue<round_process> q; // queue of processes in order to be executed

    //initialize queue and reaminig times
    for (int i = 0; i<v.size(); i++) {
        q.push(v[i]);
        remainingTime[v[i].name] = v[i].burst;
    }
    //end initialize

    start =v[0].arrival; end = start;

    //waiting time = departure - arrival - burst
    int waiting = 0;


    while(q.size()!= 0)
    {
        round_process process = q.front();

        if(check(q,end))
        {
            start  = process.arrival;
            end = start;
        }
        else
        {
            start = end;
            while (process.arrival > end)
            {
                round_process temp = process;
                q.pop();
                q.push(temp);
                process =q.front();
            }
        }



        if(remainingTime[process.name] <= quantum)
        {
            end += remainingTime[process.name]; //endtime
            remainingTime[process.name] = 0;
            //ba append el result
            small= {start,end};
            big = {process.name ,small};
            res.append(big);

            waiting+= end - process.arrival - process.burst;

            q.pop();
        }
        else { // law el process takes more time than the quantum available
            end += quantum;
            remainingTime[process.name] -= quantum;

            //ba append el result
            small= {start,end};
            big = {process.name ,small};
            res.append(big);

            q.push(process);
            q.pop();
        }

    }

    average = float(waiting)/float(v.size());
    return res;
}





#endif // ROUNDROBIN_H
