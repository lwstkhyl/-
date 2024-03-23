#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
struct queue_node //队列中的节点
{
	int data; //数据
	struct queue_node* next; //next指针
};
struct my_queue //队列
{
	struct queue_node* rear; //只设一个指针指向队尾元素节点
};
//初始化队列
my_queue* init_queue()
{
	my_queue* new_queue = new my_queue; //创建一个新队列
	new_queue->rear = new queue_node; //创建队列的尾节点（循环链表中的头节点）
	new_queue->rear->data = -1; //将尾节点的data置为-1
	new_queue->rear->next = new_queue->rear; //头节点的next指向它自己
	return new_queue;
}
//将值为val的节点加入队列
my_queue* add_queue(my_queue* q, int val)
{
	queue_node* new_node = new queue_node; //创建新节点
	new_node->data = val; //新节点的值为val
	new_node->next = q->rear->next; //新节点的next指向原尾节点的next（队列中的第一个元素）
	q->rear->next = new_node; //将新节点放在原尾节点后
	q->rear = new_node; //更新尾节点指针指向
	return q;
}
//判断队列是否为空
bool is_empty_queue(my_queue* q)
{
	return q->rear->next == q->rear;
	//当头节点（rear的next）与rear相同时
}
//出队列，返回出去元素的值
int del_queue(my_queue* q)
{
	if (is_empty_queue(q))
	{
		printf("队列为空\n");
		return -1;
	}
	queue_node* head = q->rear->next; //循环链表头节点--rear的next
	queue_node* del = head->next; //要删除的是头节点的下一个节点
	int del_data = del->data; //保存要删除节点的data
	if (del == q->rear) ///如果只有1个元素
	{
		head->next = head; //空循环链表
		q->rear = head; //更新尾指针
	}
	else //正常情况下
	{
		head->next = del->next; //头节点的next置为要删除节点的next
	}
	free(del); //释放要删除的节点
	return del_data;
}
//遍历队列
void foreach_queue(my_queue* q, char seq = ' ')
{
	if (is_empty_queue(q)) //空队列
	{
		printf("队列为空\n");
		return;
	}
	queue_node* head = q->rear->next; //循环链表头节点
	queue_node* print = head->next; //从队列中的第一个元素开始遍历
	while (1)
	{
		printf("%d%c", print->data, seq);
		if (print == q->rear) break; //当遍历到尾指针时退出
		print = print->next; //移动print
	}
	printf("\n");
}
//初始化队列，使用长度为n的a数组
my_queue* init_queue_byArray(int a[],int n)
{
	my_queue* new_queue = init_queue();
	for (int i = 0; i < n; i++)
	{
		add_queue(new_queue, a[i]);
	}
	return new_queue;
}