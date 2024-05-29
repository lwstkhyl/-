#pragma once
#include"linklist.h"
//初始化一个头节点
struct link_nods* create_empty_list(int head_val = -1)
{
	struct link_nods* head = (struct link_nods*)malloc(sizeof(struct link_nods));
	head->data = head_val;
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
struct link_nods* create_linklist(int a[], int n, int head_val = -1)
{
	struct link_nods* head = create_empty_list(head_val);
	return insert_list_in_tail(head, a, n);
}
//找值为value的节点
struct link_nods* find_byValue(struct link_nods* head, int n)
{
	struct link_nods* p = head->next;
	while (p != NULL)
	{
		if (p->data == n) break;
		p = p->next;
	}
	return p;
}
//找索引为index的节点（索引从0开始表示首元结点），默认为最后一个
struct link_nods* find_byIndex(struct link_nods* head,int index=-2)
{
	struct link_nods* p = head->next;
	if (index == -1) return head;
	if (index != -2)
	{
		int current = 0;
		while (current != index)
		{
			if (p == NULL || p->next == NULL)
			{
				printf("不存在第%d个元素", index);
				return NULL;
			} 
			p = p->next;
			current++;
		}
	}
	else
	{
		while (p != NULL && p->next != NULL)
		{
			p = p->next;
		}
	}
	return p;
}
//删除指定位置的节点（默认为最后一个，索引从0开始表示首元结点）
struct link_nods* del_byIndex(struct link_nods* head, int index=-1)
{
	if (index != -1)
	{
		struct link_nods* del_prev = find_byIndex(head, index - 1); //要删除节点之前的那个节点
		if (del_prev == NULL)
		{
			printf("要删除的节点不存在");
			return head;
		}
		struct link_nods* del = del_prev->next; //要删除的那个节点
		if (del == NULL)
		{
			printf("要删除的节点不存在");
			return head;

		}
		del_prev->next = del->next; //将前节点与后节点相连
		free(del); //释放要删除的节点
	}
	else
	{
		struct link_nods* last = head;
		if (last->next == NULL)
		{
			printf("要删除的节点不存在");
			return head;
		}
		while (last->next->next != NULL)
		{
			last = last->next;
		} //找到倒数第二个节点
		free(last->next);
		last->next = NULL;
	}
	return head;
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
//递归法逆置无头节点的链表
struct link_nods* _reverse_byRecursion(struct link_nods* head)
{
	if (head->next == NULL)
		return head;
	struct link_nods* new_head = _reverse_byRecursion(head->next);
	head->next->next = head;
	head->next = NULL;
	return new_head;
}
//使用递归逆置链表
struct link_nods* reverse_byRecursion(struct link_nods* head)
{
	struct link_nods* new_head = _reverse_byRecursion(head->next);
	head->next = new_head; //因为这个递归方法是无头结点的，所以要把头节点连上
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
//按递增顺序合并两个递增有序排列的链表（保留重复点）
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
//按递减顺序合并两个递增有序排列的链表（保留重复点）
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
//找单链表中点
//链表长度为奇数时，返回链表中间结点；为偶数时，返回中间两个节点中靠前的那一个，即返回节点和它的next都是中间节点
struct link_nods* find_mid(struct link_nods* head)
{
	//设立两个指针fast和slow，它们分别从head开始，fast走两步slow走一步，当fast走到最后一个结点的时候slow正好走到中点
	struct link_nods* fast = head, * slow = head;
	while (fast != NULL && fast->next != NULL) 
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}
//找单链表倒数第k个点（k=1为最后一个节点，依此类推）
struct link_nods* find_byIndex_toLast(struct link_nods* head, int k)
{
	//设置两个指针，让其中一个指针比另一个指针先前移k-1步，然后两个指针同时往前移动。循环直到先行的指针指为NULL时，另一个指针所指的位置就是所要找的位置
	struct link_nods* fast = head, * slow = head;
	for (int i = 0; i < k; i++)
	{
		if (fast == NULL)
		{
			printf("不存在倒数第%d个点\n", k);
			return NULL;
		}
		fast = fast->next;
	}
	while (fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}
//删除单链表倒数第k个点（k=1为最后一个节点，依此类推）
struct link_nods* del_byIndex_toLast(struct link_nods* head, int k)
{
	struct link_nods* del_prev = find_byIndex_toLast(head, k + 1); //要删除节点之前的那个节点
	if (del_prev == NULL)
	{
		printf("无法删除倒数第%d个点\n", k);
		return head;
	}
	struct link_nods* del = del_prev->next; //要删除的那个节点
	del_prev->next = del->next; //将前节点与后节点相连
	free(del); //释放要删除的节点
	return head;
}
//去重，使每个元素只出现一次
struct link_nods* unique_linklist(struct link_nods* head)
{
	//只需要判断当前节点和下一个节点值是否相同，如果相同那么当前节点的next就改为下一个节点的next
	struct link_nods* p = head->next; //探测指针
	struct link_nods* del = NULL; //记录要删除的节点
	while (p != NULL && p->next != NULL)
	{
		if (p->data == p->next->data) //p节点与它的下一个节点值相等
		{
			del = p->next; //删除p的下一个节点
			p->next = p->next->next; //p的next指向要删除节点的下一个节点
			free(del);
		} //注意这里不能让p往后移，因为要删除节点的下一个节点的值还可能与p值相同，还要继续删
		else
		{
			p = p->next; //不相等就后移
		}
	}
	return head;
}
//删除链表中重复的结点，重复的结点不保留
struct link_nods* unique_linklist_thoroughly(struct link_nods* head)
{
	if (head == NULL || head->next == NULL) return head;
	struct link_nods* slow = head, * fast = slow->next; //使用指针slow和fast遍历链表，初始时slow指向头结点，fast指向头结点的下一个结点
	struct link_nods* del = NULL; //记录要删除的节点
	//当fast指向的结点值与其后一个结点的结点值相同时，fast独自后移，直到它指向结点的结点值与其下一个结点的结点值不同为止
	//此时让slow指向结点的next指向last的后一个结点，让fast后移
	while (fast != NULL && fast->next != NULL)
	{
		while (fast->next != NULL && fast->data != fast->next->data) //未发现重复的节点，两个指针一起后移
		{
			fast = fast->next;
			slow = slow->next;
		}
		while (fast->next != NULL && fast->data == fast->next->data) //发现重复的节点，fast独自后移
		{
			del = fast; //删除该节点
			fast = fast->next;
			free(del);
		}
		//到达此处有三种情况：
		//1、没有需要删除的重复结点，同时fast指向尾节点，此时slow->next==fast
		//2、有需要删除的重复结点，同时fast指向尾节点，此时链表后半段都需要删除，slow->nex!=fast
		//3、有需要删除的重复结点，fast未指向尾节点，此时链表中间某段需要删除，slow->nex!=fast
		if (slow->next != fast) //有需要删除的重复结点
		{
			slow->next = fast->next;
			free(fast); //删除重复节点
			if (slow == NULL) break; //是上面的情况2，直接退出即可
			fast = slow->next; //是上面的情况3，接着探测下一个节点
		}
	}
	return head;
}
//在链表值为n的节点处创建一个环（将这个节点置为交点），返回这个交点
struct link_nods* create_circle(struct link_nods* head, int n)
{
	struct link_nods* jd = find_byValue(head, n); //交点
	if (jd == NULL) printf("没有%d这个值", n);
	struct link_nods* last = find_byIndex(head); //最后一个节点
	last->next = jd;
	return jd;
}
//判断链表是否有环，若有则返回交点，没有则返回NULL
struct link_nods* find_circle(struct link_nods* head)
{
	//思路详见https://blog.csdn.net/weixin_36795183/article/details/93890489
	struct link_nods* fast = head, * slow = head;
	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) //链表中有环
		{
			fast = head;
			while (fast != slow)
			{
				fast = fast->next;
				slow = slow->next;
			}
			return fast;
		}
	}
	return NULL; //fast为空，无环
}
//展开环
struct link_nods* del_circle(struct link_nods* head)
{
	//遍历找节点的前一个节点，next置为空
	struct link_nods* jd = find_circle(head);
	if (jd == NULL) return head;
	struct link_nods* p = head;
	int count = 0;
	while (1)
	{
		if (p->next == jd)
		{
			count++;
			if (count == 2)
			{
				p->next = NULL;
				break;
			}
		}
		p = p->next;
	}
	return head;
}
//将head2从索引为index2的节点并入head1的索引为index1的节点。使它们相交于head1中索引为index1的节点，函数返回该节点
struct link_nods* create_intersection(struct link_nods* head1, int index1, struct link_nods* head2, int index2)
{
	struct link_nods* p2 = find_byIndex(head2, index2);
	struct link_nods* p1 = find_byIndex(head1, index1);
	if (p2 == NULL) return head1;
	destroy_linklist(p2->next);
	p2->next = p1;
	return p1;
}
//判断h1和h2有无交点，若有则返回交点，没有则返回NULL
struct link_nods* find_intersection(struct link_nods* h1, struct link_nods* h2)
{
	//遍历两个链表，获取它们的长度；之后让较长的链表的指针先移动两个链表长度之差的步数
	//然后让两个链表的指针同时向前移动，当它们相遇时，相遇的位置就是交点。
	//如果直到指针移动到了尾节点（为NULL时），就是没交点
	int len1 = get_linklist_length(h1), len2 = get_linklist_length(h2);
	struct link_nods* p1 = h1->next, *p2 = h2->next;
	if (len1 > len2)
	{
		for (int i = 0; i < len1 - len2; i++)
			p1 = p1->next;
	}
	else
	{
		for (int i = 0; i < len2 - len1; i++)
			p2 = p2->next;
	}
	while (p1 != NULL && p2 != NULL && p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}
//判断一个链表是否对称
bool is_palindrome(struct link_nods* head)
{
	//找到链表中点，将链表的后半部分反转；之后从头部和中点处同时开始遍历，若所有节点值都相等则对称
	if (head == NULL || head->next == NULL || head->next->next == NULL) return true; //一个节点直接返回true
	if (head->next->next->next == NULL) return head->next->data == head->next->next->data; //2个节点直接比较
	if (head->next->next->next->next == NULL) return head->next->data == head->next->next->next->data; //3个节点直接比较
	struct link_nods* mid = find_mid(head); //找到链表中点
	reverse_byPoint(mid); //反转后半部分
	struct link_nods* p1 = head->next, *p2 = mid->next;
	while (p1 != mid->next && p2 != NULL)
	{
		if (p1->data != p2->data)
		{
			reverse_byPoint(mid); //复原链表
			return false;
		}
		p1 = p1->next;
		p2 = p2->next;
	}
	reverse_byPoint(mid); //复原链表
	return true;
}
//约瑟夫问题（无损）--n个人围成一圈，从第一个开始报数，报到m的人out，下一个人继续开始从1报数，直到剩下最后一个人
//函数返回一个记录out顺序的链表
struct link_nods* josephus_noLoss(int n, int m)
{
	//先创建一个循环链表
	struct link_nods* head = create_empty_list(1); //循环链表的第一个节点，表示第一个人，值为1
	struct link_nods* p = head;
	for (int i = 2; i <= n; i++)
	{
		p->next = create_empty_list(i); //依次向循环链表中写入数据
		p = p->next;
	}
	p->next = head; //连接首尾节点，使成为循环链表

	//再创建一个单向链表用于记录out的顺序
	struct link_nods* order = create_empty_list();
	struct link_nods* order_p = order; //用于向order链表中添加元素

	//开始报数过程
	struct link_nods* prev = head;
	p = head; //p从第一个人开始移动
	while (p->next != p) //当圈中只有一个节点（一个人）时，p->next==p
	{
		for (int count = 1; count < m; count++)
		{
			prev = p;
			p = p->next;
		} //将p和prev移动m个节点，此时p指向的人out，prev指向out的人前面的节点
		order_p->next = p; //记录是第几个人出局，把出局的人（节点）移入记录链表中
		order_p = order_p->next; //移动记录链表的写入指针
		prev->next = p->next; //将out人前面的人与out人后面的人连接（跳过out的那个人）
		p = prev->next; //p指向out人后面的人，开始下一轮报数
	}
	order_p->next = p; //将最后剩的那个人写入order
	order_p->next->next = NULL; //将尾节点的next置空
	printf("剩下的是第%d个人\n", p->data);
	return order;
}
//约瑟夫问题（有损）--n个人围成一圈，从第一个开始报数，报到m的人out，下一个人继续开始从1报数，直到剩下最后一个人
//函数返回最后那个人的序号，不保存out的人的顺序链表
int josephus(int n, int m)
{
	//先创建一个循环链表
	struct link_nods* head = create_empty_list(1); //循环链表的第一个节点，表示第一个人，值为1
	struct link_nods* p = head;
	for (int i = 2; i <= n; i++)
	{
		p->next = create_empty_list(i); //依次向循环链表中写入数据
		p = p->next;
	}
	p->next = head; //连接首尾节点，使成为循环链表

	//开始报数过程
	struct link_nods* prev = head;
	p = head; //p从第一个人开始移动
	while (p->next != p) //当圈中只有一个节点（一个人）时，p->next==p
	{
		for (int count = 1; count < m; count++)
		{
			prev = p;
			p = p->next;
		} //将p和prev移动m个节点，此时p指向的人out，prev指向out的人前面的节点
		prev->next = p->next; //将out人前面的人与out人后面的人连接（跳过out的那个人）
		free(p); //删除out的节点
		p = prev->next; //p指向out人后面的人，开始下一轮报数
	}
	int res = p->data;
	free(p);
	printf("剩下的是第%d个人\n", res);
	return res;
}