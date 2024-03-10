#pragma once
#include"linklist.h"
//初始化一个头节点
struct link_nods* create_empty_list()
{
	struct link_nods* head = (struct link_nods*)malloc(sizeof(struct link_nods));
	head->data = -1;
	head->next = NULL;
	return head;
}
//接收头节点和要插入的值
struct link_nods* insert_in_head(struct link_nods* head, int a)
{
	struct link_nods* insert = (struct link_nods*)malloc(sizeof(struct link_nods));
	insert->data = a;
	struct link_nods* temp = head->next;
	head->next = insert;
	insert->next = temp;
	return head;
}
//接收要插入的数组和数组的元素个数，将数组中元素依次插入到头部
struct link_nods* insert_list_in_head(struct link_nods* head, int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		head = insert_in_head(head, a[i]);
	}
	return head;
}
//接收头节点和要插入的值
struct link_nods* insert_in_tail(struct link_nods* head, int a)
{
	struct link_nods* insert = (struct link_nods*)malloc(sizeof(struct link_nods));
	insert->data = a;
	insert->next = NULL;
	struct link_nods* tail = head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = insert;
	return head;
}
//接收要插入的数组和数组的元素个数，将数组中元素依次插入到尾部
struct link_nods* insert_list_in_tail(struct link_nods* head, int a[], int n)
{
	struct link_nods* tail = head;
	while (tail->next != NULL) {
		tail = tail->next;
	} //寻找尾指针
	for (int i = 0; i < n; i++)
	{
		struct link_nods* insert = (struct link_nods*)malloc(sizeof(struct link_nods));
		insert->data = a[i];
		insert->next = NULL;
		tail->next = insert; //将新结点加到尾指针后
		tail = insert; //将尾指针更新（后移）
	}
	tail->next = NULL; //没有这句也行
	return head;
}
//创建一个链表，链表元素值与长度为n的a数组相同，返回创建链表的头节点
struct link_nods* create_linklist(int a[], int n)
{
	struct link_nods* head = create_empty_list();
	return insert_list_in_tail(head, a, n);
}
//三指针法逆置链表
struct link_nods* reverse_byPoint(struct link_nods* head)
{
	if (head == NULL || head->next == NULL)
	{
		printf("no reverse needed");
		return head;
	}
	struct link_nods* p = head->next;
	struct link_nods* q = p->next;
	struct link_nods* r = q->next;
	p->next = NULL;
	while (r != NULL)
	{
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	q->next = p;
	head->next = q;
	return head;
}
//头插法逆置链表
struct link_nods* reverse_byInsert(struct link_nods* head)
{
	if (head == NULL || head->next == NULL)
	{
		printf("no reverse needed");
		return head;
	}
	struct link_nods* p = head->next;
	struct link_nods* q = p->next;
	head->next = NULL;
	while (p != NULL)
	{
		p->next = head->next;
		head->next = p;
		p = q;
		if (q != NULL)
			q = q->next;
	}
	return head;
}
//删除表中大于mink且小于maxk的元素，表中元素递增有序排列
struct link_nods* delete_val(struct link_nods* head, int mink, int maxk)
{
	if (mink > maxk)
	{
		printf("输入数据有误");
		return head;
	}
	struct link_nods* p = head->next;
	struct link_nods* prev = head; //prev始终指向p的直接前驱节点
	while (p != NULL && p->data < maxk) //如果p为空或者data>=maxk就不用删了
	{
		if (p->data <= mink) //如果p的数据比mink小，就不用删
		{
			prev = p;
			p = p->next; //将p和prev都向后移一位，继续判断
		}
		else //需要删去p节点，删去时让prev直接指向p的next（下一个要判断的节点）
		{
			prev->next = p->next;
			free(p); //释放该节点
			p = prev->next; //p重新指向下一个要判断的节点
		}
	}
	return head;
}
//按递增顺序合并两个递增有序排列的链表
struct link_nods* merge_linklist(struct link_nods* a, struct link_nods* b) //本质上与数组的双指针法相同，都是用两个指针去分布探测两个链表，用另外一个指针更新结果链表的索引
{
	struct link_nods* pa = a->next, * pb = b->next; //pa和pb分别指向a和b的第一个数据，用它们对data大小进行探测
	struct link_nods* res_index = a; //结果指针，用于记录添加到了哪（结果链表中已经添加了多少元素），它标注了节点添加的位置
	struct link_nods* temp = NULL; //用于待会添加结点时存储next
	while (pa && pb) //当pa和pb都不为空时
	{
		if (pa->data >= pb->data) //如果pb的数小，就先把pb加到结果中
		{
			temp = pb->next; //存储pb的下一个结点
			pb->next = NULL; //将pb从b链表中取出
			res_index->next = pb; //将pb添加为res_index的下一个节点
			res_index = res_index->next; //将结果指针后移，移到最新添加的节点pb上
			pb = temp; //将探测指针pb在b链上后移
		}
		else //如果pa的数小，就先把pa加到结果中
		{ //操作同上，只是把pb都换成pa
			temp = pa->next;
			pa->next = NULL;
			res_index->next = pa;
			res_index = res_index->next;
			pa = temp;
		} //虽然用a作为结果链表，但将a中节点添加到结果链表中的操作与b是相同的。因为合并实际上是改变每个节点的next指向，只要一直更新pa pb，节点就不会被覆盖
	}
	res_index->next = (pa ? pa : pb); //合并剩下的没遍历完的部分（若pa空了就接pb，若pa没空就是pb空了 接pb）
	return a;
}
//按递减顺序合并两个递增有序排列的链表
struct link_nods* merge_reverse_linklist(struct link_nods* a, struct link_nods* b)
{
	return reverse_byInsert(merge_linklist(a, b)); //将递增合并后的结果逆置
}
//删除data链表中既在del1又在del2中出现的元素
struct link_nods* del_intersection_linklist(struct link_nods* data, struct link_nods* del1, struct link_nods* del2)
{
	if (data->next == NULL || del1->next == NULL || del2->next == NULL)
	{
		printf("表不能为空");
		return data;
	}
	struct link_nods* p = data, * p1 = del1->next, * p2 = del2->next; //这三个指针分别指向data del1 del2链表
	struct link_nods* temp = NULL; //在删除节点过程中起存储作用
	while (p->next != NULL && p1 != NULL && p2 != NULL)
	{
		while (p1 != NULL && p2 != NULL && p1->data != p2->data) //先找一个bc中都有的元素
		{
			if (p1->data < p2->data) //如果p1指的值比p2小，就把p1往后移，尝试找一个较大的数
				p1 = p1->next;
			else
				p2 = p2->next; //反之就把p2往后移
		}
		if (p1 != NULL && p2 != NULL) //如果满足这个条件，说明上面循环是因为找到了共有元素才退出的
		{
			//一个特殊情况处理：当del1和del2中有重复的元素，这时需让p1p2跳过重复，指向重复的最后一个元素（[2,2,3]让p=1而不是0）
			while ((p1->next != NULL && p1->data == p1->next->data) || (p2->next != NULL && p2->data == p2->next->data))
			{
				if (p1->next != NULL && p1->data == p1->next->data) //如果p1与p1的下一个元素相等，就把p1移到下一个元素上
					p1 = p1->next;
				if (p2->next != NULL && p2->data == p2->next->data)
					p2 = p2->next;
			} //为了避免两次找到的bc中共有元素是重复的
			//现在p1和p2指向的元素是相等的
			while (p->next != NULL && p->next->data < p1->data) //为了后面方便删除，使用p表示要删除的那个元素的直接前驱节点，即要删除的实际上是p->next，所以判断条件是"p->next->data<p1->data"
				p = p->next; //将p->next移动到>=p1的位置，便于后续的判断
			if (p->next != NULL && p->next->data == p1->data) //在data中找到了共有元素
			{
				while (p->next != NULL && p->next->data == p1->data) //为了应对要删除的元素在data中多次出现的情况，使用循环。一直删到数不相等为止
				{
					temp = p->next; //temp是要删除的那个节点
					p->next = temp->next; //p是要删除节点的前驱，需要指向要删除节点的后继
					free(temp); //删除节点
				}
			}
			p1 = p1->next;
			p2 = p2->next; //删完了就把p1p2后移再找下一个共有元素
			//这里与数组有差别，因为数组没有用循环进行删除，需要应对多次出现的特殊情况，要额外判断是不是删完了。而这里肯定删完了，直接后移就行
		}
	}
	return data;
}