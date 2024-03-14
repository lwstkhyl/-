#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
struct link_nods
{
	int data;
	struct link_nods* next;
};
//通过输入数据创建新链表，新数据增加到链表尾部，返回链表头节点
struct link_nods* init_linklist();
//在值为old_val的位置前插入新值new_val
struct link_nods* insert_by_value(struct link_nods* header, int old_val, int new_val);
//删除值为del_value的结点
struct link_nods* remove_by_value(struct link_nods* header, int del_value);
//从头到尾输出链表存储的数据
struct link_nods* foreach_linklist(struct link_nods* header, char seq);
//输出node节点的数据
struct link_nods* print_linknode(struct link_nods* node);
//与清空不同，销毁要把头节点也释放
struct link_nods* destroy_linklist(struct link_nods* header);
//清空：恢复到只有头节点的状态，把除头结点之外的结点全都释放
struct link_nods* clear_linklist(struct link_nods* header);
struct link_nods* init_linklist()
{
	struct link_nods* header = (struct link_nods*)malloc(sizeof(struct link_nods));
	header->data = -1;
	header->next = NULL;
	struct link_nods* rear = header;
	int val = -1;
	printf("输入-1则结束输入\n");
	while (true)
	{
		printf("输入插入的数据：\n");
		scanf_s("%d", &val);
		if (val == -1)
			break;
		struct link_nods* new_nods = (struct link_nods*)malloc(sizeof(struct link_nods));
		new_nods->data = val;
		new_nods->next = NULL;
		rear->next = new_nods;
		rear = new_nods;
	}
	return header;
}
struct link_nods* foreach_linklist(struct link_nods* header, char seq = ' ')
{
	if (header == NULL||header->next==NULL)
	{
		printf("链表为空\n");
		return header;
	}
	struct link_nods* p_current = header->next;
	while (p_current != NULL)
	{
		printf("%d", p_current->data);
		printf("%c",seq);
		p_current = p_current->next;
	}
	printf("\n");
	return header;
}
struct link_nods* print_linknode(link_nods* node)
{
	if (node == NULL)
	{
		printf("节点为空\n");
		return node;
	}
	printf("%d", node->data);
	return node;
}
struct link_nods* insert_by_value(struct link_nods* header, int old_val, int new_val)
{
	if (header == NULL)
		return header;
	struct link_nods* p_prev = header;
	struct link_nods* p_current = p_prev->next;
	while (p_current != NULL)
	{
		if (p_current->data == old_val)
			break;
		p_prev = p_current;
		p_current = p_current->next;
	}
	if (p_current == NULL)
		return header;
	struct link_nods* newnods = (struct link_nods*)malloc(sizeof(struct link_nods));
	newnods->data = new_val;
	newnods->next = NULL;
	p_prev->next = newnods;
	newnods->next = p_current;
	return header;
}
struct link_nods* remove_by_value(struct link_nods* header, int del_value)
{
	if (header == NULL)
		return header;
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
	{
		return header;
		printf("不存在值为%d的元素", del_value);
	}
	p_prev->next = p_current->next;
	free(p_current);
	p_current = NULL;
	return header;
}
struct link_nods* clear_linklist(struct link_nods* header)
{
	if (header == NULL)
		return header;
	struct link_nods* p_current = header->next;
	while (p_current != NULL)
	{
		struct link_nods* p_next = p_current->next;
		free(p_current);
		p_current = p_next;
	}
	header->next = NULL;
	return header;
}
struct link_nods* destroy_linklist(struct link_nods* header)
{
	if (header == NULL)
		return header;
	struct link_nods* p_current = header;
	while (p_current != NULL)
	{
		struct link_nods* p_next = p_current->next;
		printf("%d结点被销毁\n", p_current->data);
		free(p_current);
		p_current = p_next;
	}
	return header;
}