#include<stdio.h>
//链表结点类型定义
struct link_nods
{
	int data;
	struct link_nods* next; //指向下一个结点的指针
};
void test()
{ 
	//先创建6个结点
	struct link_nods node1 = { 1,NULL };
	struct link_nods node2 = { 2,NULL };
	struct link_nods node3 = { 3,NULL };
	struct link_nods node4 = { 4,NULL };
	struct link_nods node5 = { 5,NULL };
	struct link_nods node6 = { 6,NULL };
	//再把指针都指向下一个结点
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	//如何遍历链表？用一个指针p指向结点，将p=p->next就可以指向下一个结点，当p=NULL时结束
	struct link_nods* p = &node1;
	while (p!=NULL)
	{
		printf("%d",p->data);//输出指向的数据
		p = p->next;
	}
}
int main()
{
	test();
	return 0;
}
