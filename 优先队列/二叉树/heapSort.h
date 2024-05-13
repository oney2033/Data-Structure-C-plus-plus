#pragma once
#include"maxHeap.h"
template<class T>
void heapSort(T a[], int n)
{
	maxHeap<T>heap;
	heap.initialize(a, n);
	for (int i = n; i > 0; i--)
	{
		T x = heap.top();
		heap.pop();
		a[i] = x;
	}
	heap.deactivateArray();
}