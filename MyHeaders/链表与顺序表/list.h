#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAXSIZE 100
struct list 
{
	int data[MAXSIZE];
	int last_index; //data数组中最后一个元素的索引（从0开始）
};
//创建空的顺序表
list make_empty()
{
	list l;
	l.last_index = -1;
	return l;
}
//根据长度为n的数组a初始化顺序表
list unit_byArray(int a[], int n)
{
	if (n > MAXSIZE)
	{
		printf("数组长度大于顺序表最大长度");
		return make_empty();
	}
	list l;
	for (int i = 0; i < n; i++)
	{
		l.data[i] = a[i];
	}
	l.last_index = n - 1;
	return l;
}
//在l表的index位置插入值为n的元素，index默认为表尾，注意index从0开始
void insert_byIndex(list& l, int n, int index = -1)
{
	if (l.last_index == MAXSIZE - 1)
	{
		printf("顺序表长度已达最大长度，无法插入");
		return;
	}
	if (index == -1) index = l.last_index + 1;
	if (index < 0 || index > l.last_index + 1)
	{
		printf("插入位置不合法");
		return;
	}
	for (int i = l.last_index; i >= index; i--)
	{
		l.data[i + 1] = l.data[i];
	}
	l.data[index] = n;
	l.last_index++;
	return;
}
//遍历输出顺序表
void foreach_list(list l, char seq = ' ')
{
	if (l.last_index == -1)
	{
		printf("顺序表为空\n");
		return;
	}
	for (int i = 0; i <= l.last_index; i++)
	{
		printf("%d%c", l.data[i], seq);
	}
	printf("\n");
}