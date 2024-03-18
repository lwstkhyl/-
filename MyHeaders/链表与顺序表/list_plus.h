#pragma once
#include"list.h"
//将a数组中索引为n和m的两个数交换位置
void swap(int a[], int n, int m)
{
	int temp = a[n];
	a[n] = a[m];
	a[m] = temp;
}
//将l倒序
void reverse_list(list& l)
{
	for (int i = 0; i < (l.last_index + 1) / 2; i++)
	{
		swap(l.data, i, l.last_index - i);
	}
}
//删除data表中既在del1又在del2中出现的元素
void del_intersection_list(list& data, list del1, list del2)
{
	if (data.last_index == -1 || del1.last_index == -1 || del2.last_index == -1)
	{
		printf("表不能为空");
		return;
	}
	int p = 0, p1 = 0, p2 = 0; //这三个指针分别指向data del1 del2的元素
	while (p <= data.last_index && p1 <= del1.last_index && p2 <= del2.last_index) //当三个指针都没有遍历完时
	{
		//先找一个bc中都有的元素
		while (p1 <= del1.last_index && p2 <= del2.last_index && del1.data[p1] != del2.data[p2]) //当p1p2没越界，且它们指的值不等时
		{
			if (del1.data[p1] < del2.data[p2]) //如果p1指的值比p2小，就把p1往后移，尝试找一个较大的数
				p1++;
			else //反之就把p2往后移
				p2++; 
		}
		if (p1 <= del1.last_index && p2 <= del2.last_index) //如果满足这个条件，说明上面循环是因为找到了共有元素才退出的
		{
			//一个特殊情况处理：当del1和del2中有重复的元素，这时需让p1p2跳过重复，指向重复的最后一个元素（[2,2,3]让p=1而不是0）
			while ((p1 <= del1.last_index - 1 && del1.data[p1] == del1.data[p1 + 1]) || (p2 <= del2.last_index - 1 && del2.data[p2] == del2.data[p2 + 1]))
			{
				if (del1.data[p1] == del1.data[p1 + 1]) //如果p1与p1的下一个元素相等，就把p1移到下一个元素上
					p1++;
				if (del2.data[p2] == del2.data[p2 + 1])
					p2++;
			} //为了避免两次找到的bc中共有元素是重复的
			//现在p1和p2指向的元素是相等的
			while (p <= data.last_index && data.data[p] < del1.data[p1])
				p++; //将p移动到>=p1的位置，便于后续的判断
			if (p <= data.last_index && data.data[p] == del1.data[p1]) //如果p==p1且p未越界，说明在data中找到了共有元素
			{
				for (int i = p; i <= data.last_index - 1; i++)
					data.data[i] = data.data[i + 1]; //使用"后一个元素给前一个元素赋值的方式"删除p指向的元素
				data.last_index--; //data表长-1
			}
			else //如果不存在这个元素（或删除已完成），p1p2都往后移
			{
				p1++;
				p2++;
			}
			//另一个特殊情况：要删除的元素在data中多次出现，在删除第一个后，又进入循环且p1p2不变，仍会删除下一个要删除的元素，所以不需作特殊处理。这也是为什么在上面删除操作的if中不让p++的原因
		}
	}
}
//冒泡排序（从小到大）
void bubble_sort(list& data)
{
	int n = data.last_index + 1; //要排序的数组长度
	for (int i = 0; i < n - 1; i++) //n-1是因为数组下标最大为n-1 要进行10轮比较
	{
		for (int j = 0; j < n-1-i; j++) //n-1是因为数组下标最大为n-1 要进行10次比较，再减i是因为每最后的i个元素已经有序不需要继续排序
		{
			if (data.data[j] > data.data[j+1]) //两两比较，将小的数据放前面
			{
				swap(data.data, j+1, j); //交换arr数组arr[j+1]和arr[j]的值
			}
		}
	}
}
//选择排序（从小到大）
void select_sort(list& data)
{
	int n = data.last_index + 1; //要排序的数组长度
	int min; //用于存放最小值的下标
	for (int i = 0; i < n; i++)
	{
		min = i;//初始化选取假设的最小值,选取的是未排序序列的第一个数
		for (int j = i; j < n; j++)
		{
			if (data.data[j] < data.data[min])
				min = j;
		} //内循环退出，确定了最小值
		swap(data.data, i, min); //将最小值移动到已排序序列末尾
	}
}
//插入排序（从小到大）
void insert_sort(list& data)
{
	int n = data.last_index + 1; //要排序的数组长度
	int temp; //用于记录要插入的值
	for (int i = 1, j; i < n; i++)
	{
		temp = data.data[i]; //保存要插入的值
		for (j = i - 1; temp < data.data[j] && j >= 0; --j)  //数据往后移动，给要插入的值腾位
		{
			data.data[j + 1] = data.data[j];
		}
		data.data[j + 1] = temp;
	}
}
//对有序表去重，返回去重后的顺序表长度
int unique_list(list& data) 
{
	int n = data.last_index + 1; //要去重的数组长度
	int slow = 0, fast = 0;//慢指针slow走在后面，快指针fast走在前面探路，找到一个不重复的元素就告诉slow并让slow前进一步。当fast指针遍历完整个数组nums后nums[0--slow]就是不重复元素
	while (fast < n)
	{
		if (data.data[fast] != data.data[slow])
		{
			slow++;
			data.data[slow] = data.data[fast];
		}
		fast++;
	}
	data.last_index = slow;
	return slow + 1;
}
//删除表中所有值为0的元素，返回新顺序表长度
int del_all_zero(list& data)
{
	int n = data.last_index + 1; //要处理的数组长度
	int slow = 0, fast = 0;//慢指针slow走在后面，快指针fast走在前面探路，找到一个不为0的元素就告诉slow并让slow前进一步。当fast指针遍历完整个数组nums后nums[0--slow]就是不为0的元素
	while (fast < n)
	{
		if (data.data[fast] != 0)
		{
			data.data[slow] = data.data[fast];
			slow++;
		}
		fast++;
	}
	data.last_index = slow-1;
	return slow;
}