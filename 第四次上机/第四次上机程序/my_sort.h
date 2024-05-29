#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//输出有num个数的一维数组，间隔符为seq
void show_array(const int* a, int num, char seq = ' ')
{
	for (int i = 0; i < num; i++)
	{
		printf("%d%c", a[i], seq);
	}
}
//交换2个整数
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
//在递归中使用的快速排序函数（从小到大）
void _quick_sort(int a[], int low, int high)
{
	if (low >= high)//递归终止条件：尾索引>=头索引
	{
		return;
	}
	int first = low, last = high;
	int key = a[first];//将first处的值放到key中
	int temp = first;//first即为坑位，之后last开始行动找值补坑
	while (first < last)
	{
		while (first < last && a[last] >= key)
		{
			--last;
		}//从右往左找一个比key小的值
		a[temp] = a[last];//将这个值放入坑位
		temp = last;//并将此处置为新坑
		while (first < last && a[first] <= key)//first开始行动找值补坑
		{
			++first;
		}//从左往右找一个比key要大的值
		a[temp] = a[first];//将这个值放入坑位
		temp = first;//并将此处置为新坑
	}
	a[temp] = key;//当first与last相遇的时候，将key放入到坑位中
	_quick_sort(a, low, temp - 1); //进行[low, temp - 1], temp, [temp + 1, high] 的递归分治
	_quick_sort(a, temp + 1, high);
}
//快速排序（从小到大）
void quick_sort(int arr[], int n)
{
	_quick_sort(arr, 0, n - 1);
}
//希尔排序
void shell_sort(int a[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2) //从一个大的间隔开始，然后缩小间隔
	{
		//第一个间隔a[0..gap-1]已经顺序排列
		//继续添加一个元素，直到对整个数组进行顺序排序
		for (int i = gap; i < n; i++) //将a[i]添加到已进行排序的元素中
		{ 
			int temp = a[i]; //用temp中保存a[i]，并在i处挖坑
			int j;
			for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
				a[j] = a[j - gap]; //向上移动先前排序的元素，直到找到[i]的正确位置
			a[j] = temp; //将temp（原始a[i]）放在正确的位置
		} 
	}
}
//堆排序中建堆
void _heapify(int a[], int n, int i)
{
	int max = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left<n && a[left]>a[max]) max = left;
	if (right<n && a[right]>a[max]) max = right;
	if (max != i) {
		swap(a[i], a[max]);
		_heapify(a, n, max);
	}
}
//堆排序
void heap_sort(int a[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		_heapify(a, n, i);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(a[0], a[i]);
		_heapify(a, i, 0);
	}
}
//二分查找（不使用递归），在长度为length的有序（从小到大）数组a中找值val
int binary_search(int val, int* a, int length)
{
	int low = 0, high = length - 1, mid; //最小值、最大值和中间值的下标
	while (low <= high) //循环终止条件
	{
		mid = (low + high) / 2; //每次递归重新给mid赋值，改变中间值的下标
		if (a[mid] == val) //如果中间值等于目标值，说明查找成功，返回下标
		{
			return mid;
		}
		else if (a[mid] > val) //如果中间值大于目标值，说明目标值在左半边
		{
			high = mid - 1; //下一次循环的终点就是中间值前的位置
		}
		else //如果中间值小于目标值，说明目标值在右半边
		{
			low = mid + 1; //下一次循环的起点
		}
	}
	return -1; //循环结束后仍未找到
}