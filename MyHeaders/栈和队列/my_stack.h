#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX_SIZE 100
struct stack
{
	int data[MAX_SIZE];
	int top; //栈顶指针，指向栈顶元素data[top]
};
//初始化栈，将栈顶指针赋值为-1
stack& init_stack()
{
	stack new_stack;
	new_stack.top = -1;
	return new_stack;
}
//向栈中添加new_val
stack& push(stack& a, int new_val)
{
	if (a.top >= MAX_SIZE - 1) return a;
	a.top++;
	a.data[a.top] = new_val;
	return a;
}
//弹出栈顶元素，其值保存在val中
stack& pop(stack& a, int& val)
{
	if (a.top <= -1) return a;
	val = a.data[a.top];
	a.top--;
	return a;
}
//弹出栈顶元素
void pop(stack& a)
{
	if (a.top <= -1) return;
	a.top--;
}
//得到栈顶元素
int get_top(stack& a)
{
	return a.data[a.top];
}
//判断栈是否为空
bool is_empty(stack& a)
{
	return a.top <= -1;
}
//遍历输出栈中元素（不弹出元素），从栈顶开始
stack& foreach_stack(stack& a, char seq = ' ')
{
	for (int i = a.top; i >= 0; i--)
	{
		printf("%d%c", a.data[i], seq);
	}
	return a;
}
//遍历输出栈中元素（不弹出元素），从栈顶开始
stack& foreach_char_stack(stack& a, char seq = ' ')
{
	for (int i = a.top; i >= 0; i--)
	{
		printf("%c%c", a.data[i], seq);
	}
	return a;
}
//遍历输出栈中元素（同时弹出元素），从栈顶开始
stack& foreach_pop_stack(stack& a, char seq = ' ')
{
	while (a.top >= -1)
	{
		printf("%d%c", a.data[a.top], seq);
		a.top--;
	}
	return a;
}
//使用长度为n的a数组创建一个栈
stack& init_stack_byArray(int a[], int n)
{
	stack new_stack = init_stack();
	for (int i = 0; i < n; i++)
	{
		push(new_stack, a[i]);
	}
	return new_stack;
}