#include"linklist.h"
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
struct link_nods* init_linklist()
{
	//创建头节点
	struct link_nods* header = malloc(sizeof(struct link_nods));//指向一块新内存
	header->data = -1;//头节点不存储数据
	header->next = NULL;
	//创建一个指针，始终指向链表尾部
	struct link_nods* rear = header;
	int val = -1;
	printf("输入-1则结束输入\n");
	while (true)
	{
		printf("输入插入的数据：\n");
		scanf_s("%d", &val);
		if (val == -1)
			break;
		//先创建新结点
		struct link_nods* new_nods = malloc(sizeof(struct link_nods));
		new_nods->data = val;
		new_nods->next = NULL;
		//新节点插入到链表中，即让新节点的前一个结点的next指向它，“前一个结点”就是原来的最后一个结点，此时被rear指向（最开始时头节点就是最后一个结点）
		rear->next = new_nods;  //
		//更新尾部指针指向
		rear = new_nods;
	}
	return header;
}
void foreach_linklist(struct link_nods* header)
{
	if (header == NULL)
	{
		return;
	}
	//头节点不保存数据，从头节点的下一个开始判断
	struct link_nods* p_current = header->next;//辅助指针变量
	while (p_current!=NULL)
	{
		printf("%d", p_current->data);
		printf("\n");
		p_current = p_current->next;
	}
}
void insert_by_value(struct link_nods* header, int old_val, int new_val)
{
	//需要通过遍历找到old_val结点和它之前的那个结点，但因为是单向链表，无法通过old_val找到它之前的结点
	//所以设置两个相邻的指针，同时进行移动，一个指针p_current指向old_val时，另一个p_prev就指向它之前的那个结点
	//让old_val之前的那个结点p_prev指向new_val，而new_val指向old_val
	//先找到old_val
	if (header == NULL)
		return;
	struct link_nods* p_prev = header;
	struct link_nods* p_current = p_prev->next;
	while (p_current != NULL)
	{
		if (p_current->data == old_val)
			break;
		p_prev = p_current;
		p_current = p_current->next;
	}
	if (p_current == NULL)//循环结束，没找到old_val
		return; //如果想让没找到old_val时把new_val插入到链表尾部，只要把这段if删去即可
	//先创建新结点
	struct link_nods* newnods = malloc(sizeof(struct link_nods));
	newnods->data = new_val;
	newnods->next == NULL;
	//新结点插入到链表中,
	p_prev->next = newnods;
	newnods->next = p_current;
}
void remove_by_value(struct link_nods* header, int del_value)
{
	//删除del_value就是让该结点的前结点p_prev指向它的后结点p_current->next;，同时释放该结点，也需要两个指针
	if (header == NULL)
		return;
	struct link_nods* p_prev = header;
	struct link_nods* p_current = p_prev->next;
	while (p_current != NULL)
	{
		if (p_current->data == del_value)
			break;
		p_prev = p_current;
		p_current = p_current->next;
	}
	if (p_current == NULL)
		return;
	p_prev->next = p_current->next;
	free(p_current);//释放该结点内存
	p_current == NULL;
}
void clear_linklist(struct link_nods* header)
{
	if (header == NULL)
		return;
	//清空就是恢复到只有头节点的状态，把除头结点之外的结点全都释放
	struct link_nods* p_current = header->next;//用一个辅助指针从前往后进行释放
	while (p_current!=NULL)
	{
		//释放p_current指向结点前要先保存该结点的next，要不找不到下一个结点了
		struct lint_nods* p_next = p_current->next;
		free(p_current);
		p_current = p_next;//让p_current指向下一个结点
	}
	header->next = NULL;//把头结点的next也置空
}
void destroy_linklist(struct link_nods* header)
{
	if (header == NULL)
		return;
	struct link_nods* p_current = header;//与清空不同，销毁要把头节点也释放，所以辅助指针从header开始直接从
	while (p_current != NULL)
	{
		struct lint_nods* p_next = p_current->next;
		printf("%d结点被销毁\n", p_current->data);
		free(p_current);
		p_current = p_next;
	}
}
void test()
{
	//初始化链表 100 200 300 400 500
	struct link_nods* header = init_linklist();
	//打印链表
	foreach_linklist(header);
	//插入数据
	insert_by_value(header, 300, 600);
	printf("\n");
	foreach_linklist(header); //输出100 200 600 300 400 500
	//删除数据
	remove_by_value(header, 200);
	printf("\n");
	foreach_linklist(header);
	//清空链表
	clear_linklist(header);
	printf("\n");
	foreach_linklist(header);
	//销毁链表
	destroy_linklist(header);
}
int main()
{
	test();
	return 0;
}
