#ifndef SJF_BODA_H
#define SJF_BODA_H
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


//global vars
double avg_time = 0;
//


struct SJF{

    QString name;
    int burst_time, arrival_time;

    bool  operator < ( const SJF &b){

        return this->burst_time < b.burst_time;
    }

};

struct Priority{

    QString name;
    int burst_time, arrival_time, priority;

    bool  operator < ( const Priority &b){

        return this->priority < b.priority;
    }

};




/****************/

QVector<QPair<QString,QPair<int,int>>> sjf_non_preemptive(QVector<SJF> processes)
{

    QVector<QPair<QString,QPair<int,int>>>timeline;


    int num_of_processes = processes.size();
    avg_time =0;
    QSet<QString> done;
    QVector<QPair<int,QString>> time;
    sort(processes.begin(),processes.end());
    int total_burst_time = 0;
    int last_arrive = 0;
        for(int i=0;i<num_of_processes;i++)
        {
            last_arrive = max(last_arrive, processes[i].arrival_time);
            total_burst_time+= processes[i].burst_time;
        }
    total_burst_time += last_arrive;

    for(int i=0;i<total_burst_time;i++)
    {

        for(int j=0;j<num_of_processes;j++){

            if(processes[j].arrival_time<= i && done.find(processes[j].name) == done.end())
            {
                done.insert(processes[j].name);
                avg_time+=  -processes[j].burst_time - processes[j].arrival_time;

                for(int k = i;k<=processes[j].burst_time+i;k++)
                    time.append({k,processes[j].name});
                i += processes[j].burst_time - 1;

                break;
            }
        }
    }

        time.append({-1,"dummy"});
        QString cur = time[0].second;
        int started = time[0].first;
        for(int i=1;i<time.size();i++){
            if(time[i].second != cur){

                timeline.append({cur,{started,time[i-1].first}});
                avg_time += time[i-1].first;
                cur = time[i].second;
                started = time[i].first;
            }

        }


    avg_time /= (double)num_of_processes;
    return timeline;
}

/*********************************************************************/

QVector<QPair<QString,QPair<int,int>>> sjf_preemptive(QVector<SJF> processes)
{

    QVector<QPair<QString,QPair<int,int>>>timeline;
    int num_of_processes = processes.size();
    avg_time =0;
    QSet<QString> done;
    QVector<pair<int,QString>> time;
    sort(processes.begin(),processes.end());
    int total_burst_time = 0;
    int last_arrive = 0;
        for(int i=0;i<num_of_processes;i++)
        {   avg_time+=  -processes[i].burst_time - processes[i].arrival_time;
            last_arrive = max(last_arrive, processes[i].arrival_time);
            total_burst_time+= processes[i].burst_time;
        }
    total_burst_time += last_arrive;

    for(int i=0;i<total_burst_time;i++)
    {

        for(int j=0;j<num_of_processes;j++){

            if(processes[j].arrival_time<= i && done.find(processes[j].name) == done.end())
            {
                processes[j].burst_time--;
              //  sort(processes.begin(),processes.end());
                if(processes[j].burst_time == 0 )
                {
                done.insert(processes[j].name);
                avg_time += i+1;
                }

                time.append({i,processes[j].name});
                sort(processes.begin(),processes.end());
                break;





            }
        }
    }


        time.append({-1,"dummy"});
        QString cur = time[0].second;
        int started = time[0].first;
        for(int i=1;i<time.size();i++){
            if(time[i].second != cur){

                timeline.append({cur,{started,time[i-1].first+1}});

                cur = time[i].second;
                started = time[i].first;
            }

        }

    avg_time /= (double)num_of_processes;

    return timeline;
}


/*****************************************************************************/

QVector<QPair<QString,QPair<int,int>>> priority_preemptive(QVector<Priority> processes )
{

    QVector<QPair<QString,QPair<int,int>>> timeline;
    int num_of_processes = processes.size();
    avg_time =0;
    QSet<QString> done;
    QVector<QPair<int,QString>> time;
    sort(processes.begin(),processes.end());
    int total_burst_time = 0;
    int last_arrive = 0;
        for(int i=0;i<num_of_processes;i++)
        {   avg_time+=  -processes[i].burst_time - processes[i].arrival_time;
            last_arrive = max(last_arrive, processes[i].arrival_time);
            total_burst_time+= processes[i].burst_time;
        }
    total_burst_time += last_arrive;

    for(int i=0;i<total_burst_time;i++)
    {

        for(int j=0;j<num_of_processes;j++){

            if(processes[j].arrival_time<= i && done.find(processes[j].name) == done.end())
            {
                processes[j].burst_time--;
              //  sort(processes.begin(),processes.end());
                if(processes[j].burst_time == 0 )
                {
                done.insert(processes[j].name);
                avg_time += i+1;
                }

                time.append({i,processes[j].name});
                 sort(processes.begin(),processes.end());
                break;





            }
        }
    }

   // for(int i=0;i<time.size();i++)
        //cout<< time[i].first << "  " << time[i].second << endl ;

        time.append({-1,"dummy"});
        QString cur = time[0].second;
        int started = time[0].first;
        for(int i=1;i<time.size();i++){
            if(time[i].second != cur){

                timeline.append({cur,{started,time[i-1].first+1}});

                cur = time[i].second;
                started = time[i].first;
            }

        }

        avg_time /= (double)num_of_processes;
        return timeline;
}







#endif // SJF_BODA_H
