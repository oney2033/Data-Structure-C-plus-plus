#pragma once
#include"maxHeapSort.h"
#include"minHeap.h"
#include"lptNodes.h"
#include<iostream>

void makeSchedule(jobNode a[], int n, int m)
{//���һ������ n ����ҵa[1:n]�� m ̨������ LPT ����
    if (n <= m)
    {
        std::cout << "Schedule each job on a different machine." << std::endl;
        return;
    }
    heapSort(a, n);//����ҵʱ�䰴����˳������

    //��ʼ��m̨����������С����
    minHeap<machineNode>machineHeap(m);
    for (int i = 1; i <= m; i++)
    {
        machineHeap.push(machineNode(i, 0));
    }

    //���ɵ��ȼƻ�
    for (int i = n; i >= 1; i--)
    {//����ҵi�����ڵ�һ̨���еĻ���
        machineNode x = machineHeap.top();
        machineHeap.pop();
        std::cout << "Schedule job " << a[i].id
            << " on machine " << x.id << " from " << x.avail
            << " to " << (x.avail + a[i].time) << std::endl;
        x.avail += a[i].time;  //��̨�����µĿ���ʱ��
        machineHeap.push(x);
    }
}