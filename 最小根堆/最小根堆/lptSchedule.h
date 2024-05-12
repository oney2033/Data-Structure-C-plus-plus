#pragma once
#include"maxHeapSort.h"
#include"minHeap.h"
#include"lptNodes.h"
#include<iostream>

void makeSchedule(jobNode a[], int n, int m)
{//输出一个基于 n 个作业a[1:n]的 m 台机器的 LPT 调度
    if (n <= m)
    {
        std::cout << "Schedule each job on a different machine." << std::endl;
        return;
    }
    heapSort(a, n);//将作业时间按递增顺序排序

    //初始化m台机器，建立小根堆
    minHeap<machineNode>machineHeap(m);
    for (int i = 1; i <= m; i++)
    {
        machineHeap.push(machineNode(i, 0));
    }

    //生成调度计划
    for (int i = n; i >= 1; i--)
    {//把作业i安排在第一台空闲的机器
        machineNode x = machineHeap.top();
        machineHeap.pop();
        std::cout << "Schedule job " << a[i].id
            << " on machine " << x.id << " from " << x.avail
            << " to " << (x.avail + a[i].time) << std::endl;
        x.avail += a[i].time;  //这台机器新的空闲时间
        machineHeap.push(x);
    }
}