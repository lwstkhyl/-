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
struct hstring {
	char* ch; //储存字符串信息：若非空串，按串长分配空间，否则ch=NULL
	int length; //串长度
};
hstring& init_hstring()
{
	hstring* h = new hstring;
	h->ch = NULL;
	h->length = 0;
	return *h;
}
hstring& create_hstring(const char* chars)
{
	hstring T = init_hstring();
	if (T.ch) free(T.ch); //释放T原有空间
	int i; //chars长度
	const char* c = chars;
	for (i = 0; (*c) != '\0'; ++i, ++c); //求chars的串长度i
	if (!i) //如果chars为空串
	{
		T.ch = NULL;
		T.length = 0;
	} //就把T也设为空串
	else
	{
		T.ch = (char*)malloc(i * sizeof(char)); //给T.ch分配内存（内存大小同chars串）
		for (int j = 0; j < i; j++)
			T.ch[j] = chars[j]; //for循环把T.ch进行赋值
		T.length = i; //更改T的长度
	}
	return T;
}
void show_hstring(hstring& h)
{
	if (h.length == 0)
	{
		printf("串为空\n");
		return;
	}
	for(int i=0;i<h.length;i++)
		printf("%c", h.ch[i]);
	printf("\n");
}