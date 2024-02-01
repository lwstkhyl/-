#pragma once
#ifndef _wth_intArray_h_
#define _wth_intArray_h_
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//有num个数的一维数组，间隔符为seq
void show_array(const int* a ,int num ,char seq=' ')
{
	if (a == NULL)
	{
		printf("数组为NULL（来自show_array）\n");
		return;
	}
	for (int i = 0; i < num; i++)
	{
		printf("%d%c", a[i], seq);
	}
}
//m行n列的二维数组，即a[m][n]，间隔符为seq。传入方式：int a[n][m]; show_array_2(*a,...)
void show_array_2(const int* a, int m, int n, char seq = ' ')
{
	if (a == NULL)
	{
		printf("数组为NULL（来自show_array_2）\n");
		return;
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d%c", *(a + i * n + j), seq);
		}
		printf("\n");
	}
}
//a数组的第一个元素应标识数组长度，即除它之外还有几个元素，间隔符为seq
void show_array(const int* a, char seq = ' ')
{
	if (a == NULL)
	{
		printf("数组为NULL（来自show_array）\n");
		return;
	}
	for (int j = 1; j <= a[0]; j++)
	{
		printf("%d%c", *(a + j), seq);
	}
}
//二维数组a的a[0][0]应标识数组行数（除第一行之外），a[0][1]应标识数组总列数，间隔符为seq。传入方式：int a[n][m]; show_array_2(*a,...)
void show_array_2(const int* a, char seq = ' ')
{
	if (a == NULL)
	{
		printf("数组为NULL（来自show_array_2）\n");
		return;
	}
	for (int i = 1; i <= *(a); i++)
	{
		for (int j = 0; j < *(a+1); j++)
		{
			printf("%d%c", *(a + i * (*(a + 1)) + j), seq);
		}
		printf("\n");
	}
}

//获取const数组的可变副本
int* const_to_var(const int* arr, int num)
{
	int* data;
	if ((data = (int*)malloc(sizeof(int) * (num))) == NULL)
	{
		printf("分配内存空间失败!（来自const_to_var）\n");
		return NULL;
	}
	for (int i = 0; i < num; i++)
	{
		data[i] = arr[i];
	}
	return data;
}
//创建有num个数的一维数组
int* create_array(int num)
{
	if (num <= 0)
	{
		printf("输入数据有误（来自create_array）");
		return NULL;
	}
	int* data;
	if ((data = (int*)malloc(sizeof(int) * (num))) == NULL)
	{
		printf("分配内存空间失败!（来自create_array）\n");
		return NULL;
	}
	return data;
}
//创建二维数组（row行col列）
int* create_array(int row, int col)
{
	if (row <= 0 || col <= 0)
	{
		printf("输入数据有误（来自create_array）");
		return NULL;
	}
	int* data;
	if ((data = (int*)malloc(sizeof(int) * (row * col))) == NULL)
	{
		printf("分配内存空间失败!（来自create_array）\n");
		return NULL;
	}
	return data;
}
//选取[begin,end]索引内的数组，将新数组返回
int* index_select_array(const int* a, int begin, int end)
{
	if (a == NULL)
	{
		printf("数组为NULL（index_select_array）\n");
		return NULL;
	}
	if (end < begin || end < 0 || begin < 0)
	{
		printf("输入数据有误（index_select_array）");
	}
	int* data;
if ((data = (int*)malloc(sizeof(int) * (end - begin + 1))) == NULL)
{
	printf("分配内存空间失败!（来自index_select_array）\n");
	return NULL;
}
int data_index = 0;
for (int i = begin; i <= end; i++)
{
	data[data_index] = a[i];
	data_index++;
}
return data;
}

//交换2个整数
void swap_2_int(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
//交换数组中索引为x和y的整数
void swap_2_int(int arr[], int x, int y)
{
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

//判断n是否在a数组中
int is_contain(int n, int* a, int length)
{
	int flag = 0;
	for (int i = 0; i < length; i++)
	{
		if (a[i] == n)
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

//冒泡排序（从小到大）
void bubble_sort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)//n-1是因为数组下标最大为n-1 要进行10轮比较
	{
		for (int j = 0; j < n - 1 - i; j++)//n-1是因为数组下标最大为n-1 要进行10次比较，再减i是因为每最后的i个元素已经有序不需要继续排序
		{
			if (arr[j] > arr[j + 1])//两两比较，将小的数据放前面
			{
				swap_2_int(arr, j + 1, j);//交换arr数组arr[j+1]和arr[j]的值
			}
		}
	}
}
//交换排序（从小到大）
void swap_sort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)//前i个元素已确定，从第i+1个开始
		{
			if (arr[i] > arr[j])//将第i个元素与第j个元素比较，谁小谁就到第i个位置
			{
				swap_2_int(arr, i, j);  //交换arr数组arr[i]和arr[j]的值
			}
		}
	}
}
//选择排序（从小到大）
void select_sort(int arr[], int n)
{
	int min;//用于存放最小值的下标
	for (int i = 0; i < n; i++)
	{
		min = i;//初始化选取假设的最小值,选取的是未排序序列的第一个数，
		for (int j = i; j < n; j++)
		{
			if (arr[j] < arr[min])//如果遇见更小值，则记录最小值下标
			{
				min = j;
			}
		}//内循环退出，确定了最小值
		swap_2_int(arr, i, min);//将最小值移动到已排序序列末尾
	}
}
//二分法插入排序（从小到大）
void insert_sort(int a[], int n)//利用二分查找法查找出插入位置，并将有序数组中插入位置后的数据后移一位，空出插入位置插入数据
{
	for (int i = 1; i < n; i++)//从第2个数开始，依此将第a[i]放入前面已排好序的数组中
	{
		int left = 0;
		int right = i - 1;
		while (left <= right)//查找插入位置
		{
			int mid = (left + right) / 2;
			if (a[i] > a[mid])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}//循环的结果是left比right大1，left指向a[i]前已排序数组中刚好大于等于它的数，right指向刚好小于它的数
		int temp = a[i];//temp保存要插入的数
		for (int j = i; j > left; j--)//将已排序数组中left至i-1位置的数都往后移一位
		{//注意要从后往前移，否则会覆盖，导致数据丢失
			a[j] = a[j - 1];
		}
		a[left] = temp;//将a[i]放入a[left]
	} 
}
//在递归中的快速排序函数（从小到大）
void _quick_sort(int a[], int low, int high)
{
	//大体思路：先从数列中取出一个数作为基准数；将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边；再对左右区间重复第二步，直到各区间只有一个数
	if (low >= high)//递归终止条件：尾索引>=头索引
	{
		return;
	}
	int first = low, last = high;
	int key = a[first];//将first处的值放到key中
	int temp = first;//first即为坑位，之后last开始行动找值补坑
	while (first < last)
	{
		while (first < last && a[last] >= key)
		{
			--last;
		}//从右往左找一个比key小的值
		a[temp] = a[last];//将这个值放入坑位
		temp = last;//并将此处置为新坑
		while (first < last && a[first] <= key)//first开始行动找值补坑
		{
			++first;
		}//从左往右找一个比key要大的值
		a[temp] = a[first];//将这个值放入坑位
		temp = first;//并将此处置为新坑
	}
	a[temp] = key;//当first与last相遇的时候，将key放入到坑位中
	_quick_sort(a, low, temp - 1); //进行[low, temp - 1], temp, [temp + 1, high] 的递归分治
	_quick_sort(a, temp + 1, high);
}
//快速排序（从小到大）
void quick_sort(int arr[], int n)
{
	_quick_sort(arr, 0, n-1);
}
//冒泡排序（从大到小）
void bubble_sort_largeToSmall(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				swap_2_int(arr, j + 1, j);
			}
		}
	}
}
//交换排序（从大到小）
void swap_sort_largeToSmall(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (arr[i] < arr[j])
			{
				swap_2_int(arr, i, j); 
			}
		}
	}
}
//选择排序（从大到小）
void select_sort_largeToSmall(int arr[], int n)
{
	int max;
	for (int i = 0; i < n; i++)
	{
		max = i;
		for (int j = i; j < n; j++)
		{
			if (arr[j] > arr[max])
			{
				max = j;
			}
		}
		swap_2_int(arr, i, max);
	}
}
//二分法插入排序（从大到小）
void insert_sort_largeToSmall(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int left = 0;
		int right = i - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (a[i] < a[mid])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		int temp = a[i];
		for (int j = i; j > left; j--)
		{
			a[j] = a[j - 1];
		}
		a[left] = temp;
	}
}
void _quick_sort_largeToSmall(int a[], int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int first = low, last = high;
	int key = a[first];
	int temp = first;
	while (first < last)
	{
		while (first < last && a[last] <= key)
		{
			--last;
		}
		a[temp] = a[last];
		temp = last;
		while (first < last && a[first] >= key)
		{
			++first;
		}
		a[temp] = a[first];
		temp = first;
	}
	a[temp] = key;
	_quick_sort_largeToSmall(a, low, temp - 1);
	_quick_sort_largeToSmall(a, temp + 1, high);
}
//快速排序（从大到小）
void quick_sort_largeToSmall(int arr[], int n)
{
	_quick_sort_largeToSmall(arr, 0, n - 1);
}

int max(int a, int b)
{
	return a > b ? a : b;
}
int max(int a, int b, int c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}
int max(const int* a, int num)
{
	int res = a[0];
	for (int i = 1; i < num; i++)
	{
		if (a[i] > res)
			res = a[i];
	}
	return res;
}
int min(int a, int b)
{
	return a < b ? a : b;
}
int min(int a, int b, int c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
int min(const int* a, int num)
{
	int res = a[0];
	for (int i = 1; i < num; i++)
	{
		if (a[i] < res)
			res = a[i];
	}
	return res;
}

//二分查找（使用递归），在a的low-high索引间找val
int binary_search_recursion(int val, int* a, int low, int high)
{
	if (low <= high)//递归终止条件
	{
		int mid = (low + high) / 2; //每次递归重新给mid赋值，改变中间值的下标
		if (a[mid] == val) //如果中间值等于目标值，说明查找成功，返回下标
		{
			return mid;
		}
		else if (a[mid] > val) //如果中间值大于目标值，说明目标值在左半边
		{
			high = mid - 1;
			return binary_search_recursion(val, a, low, high);
		}
		else //如果中间值小于目标值，说明目标值在右半边
		{
			low = mid + 1;
			return binary_search_recursion(val, a, low, high);
		}
	}
	else
	{
		return -1;
	}
}
//二分查找（不使用递归），在长度为length的有序（从小到大）数组a中找值val
int binary_search(int val, int* a, int length)
{
	int low = 0, high = length - 1, mid; //最小值、最大值和中间值的下标
	while (low <= high) //循环终止条件
	{
		mid = (low + high) / 2; //每次递归重新给mid赋值，改变中间值的下标
		if (a[mid] == val) //如果中间值等于目标值，说明查找成功，返回下标
		{
			return mid;
		}
		else if (a[mid] > val) //如果中间值大于目标值，说明目标值在左半边
		{
			high = mid - 1; //下一次循环的终点就是中间值前的位置
		}
		else //如果中间值小于目标值，说明目标值在右半边
		{
			low = mid + 1; //下一次循环的起点
		}
	}
	return -1; //循环结束后仍未找到
}
//在长度为length的数组a中找值val，返回它的索引，is_sorted参数代表是否有序（从小到大）
int find_index_byValue(int val, int* a, int length, bool is_sorted = false)
{
	if (is_sorted == false)
	{
		int index = -1;
		for (int i = 0; i < length; i++)
		{
			if (a[i] == val)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
		{
			printf("数组中没有该数(%s)", __func__);
		}
		return index;
	}
	int index = binary_search_recursion(val, a, 0, length);
	if (index == -1)
	{
		printf("数组中没有该数(%s)", __func__);
	}
	return index;
}

//在长度为length的数组a中的索引index处插入值为val的元素，返回新数组长度
int insert_byIndex(int index, int val, int* a, int length)
{
	if (a == NULL)
	{
		printf("%s输入数组为null", __func__);
		return 0;
	}
	if (index > length || index < 0 || length <= 0)
	{
		printf("%s输入的数据有误", __func__);
		return 0;
	}
	for (int i = length - 1; i >= index; i--)
	{
		a[i + 1] = a[i];
	}
	a[index] = val;
	return length + 1;
}
int _insert_byValue_2point(int val, int* a, int length)
{
	int left = length - 1, right = length;//左右指针始终差为1，左指针从原数组的最后一个元素开始探测，右指针负责赋值
	int flag = 0;//标识左指针遍历完数组时是否插入完成
	while (left >= 0)
	{
		if (a[left] <= val)//如果左指针探到的数比要插入的数小或相等，就在右指针的位置插入
		{
			a[right] = val;
			flag = 1;
			break;
		}
		else//如果左指针指向的数较大，就不插入，而是将右指针赋值为左指针（相当于将数组向右平移）
		{
			a[right] = a[left];
			left--;//继续探下一个数
			right--;
		}
	}
	if (flag == 0)//如果没完成，说明要插入的数在数组第一位
	{
		a[0] = val;
	}
	return length + 1;
}
int _insert_byValue_binary(int val, int* a, int length)
{
	int low = 0, high = length - 1, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] == val)
		{
			break;
		}
		else if (a[mid] > val)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	} //二分查找循环结束时的mid值就是原数组中与要插入的数相邻的左/右边数
	if (a[mid] == val)
	{
		insert_byIndex(mid, val, a, length);
	}
	else if (a[mid] < val) //在mid的右边插入
	{
		insert_byIndex(mid + 1, val, a, length);
	}
	else //在mid处插入
	{
		insert_byIndex(mid, val, a, length);
	}
	return length + 1;
}
//在长度为length的有序（从小到大）数组a中插入值为val的元素，返回新数组长度，use_2point为true使用双指针方法，为false使用二分查找法
int insert_byValue(int val, int* a, int length, bool use_2point = false)
{
	if (a == NULL)
	{
		printf("%s输入数组为null", __func__);
		return 0;
	}
	if (use_2point == true)
	{
		return _insert_byValue_2point(val, a, length);
	}
	return _insert_byValue_binary(val, a, length);
}

//删除长度为length的a数组中值为val的元素，返回新数组长度
int delete_byValue(int val, int* a, int length)
{//存在两个指针p1p2，两者初始都指向数组起始位置，遍历整个数组，对指针p1和指针p2所指向的值进行比较，如果*p1!=val，就把*p1赋给*p2，然后p2向后移动。无论相等还是不相等，p1都需要往后移动，即把数组中所有非目标值的元素往前移动，p2移动的次数即为新数组长度
	if (a == NULL)
	{
		printf("%s输入数组为null", __func__);
		return 0;
	}
	int* p1 = a;
	int* p2 = a;
	int len = length;
	while (length-- > 0)//执行length次
	{//用p1来读取数据，p2来写入数据
		if (*p1 != val)//如果 *p1 != val，就将当前元素向前覆盖
		{
			*p2 = *p1;
			p2++;//覆盖后，p2要++
		}
		p1++;//p1需要一直向后移动
	}
	int new_length = p2 - a;
	for (int i = new_length; i < len; i++)
	{
		a[i] = 0;//将a数组空余部分置0
	}
	return new_length;
}
//删除长度为length的a数组中索引为index的元素，返回新数组长度
int delete_byIndex(int index, int* a, int length)
{
	if (a == NULL)
	{
		printf("%s输入数组为null", __func__);
		return 0;
	}
	if (index >= length || index < 0 || length <= 0)
	{
		printf("%s输入的数据有误", __func__);
		return 0;
	}
	for (int i = index; i < length - 1; i++)
	{
		a[i] = a[i + 1];
	}
	a[length - 1] = 0;
	return length - 1;
}

//检测有num个元素的一维数组中是否有重复值（要求元素值必须>=0）
int _hash_test_unique(const int* arr, int num)
{
	for (int i = 0; i < num; i++)
	{
		if (arr[i] < 0)
		{
			printf("要求元素值必须>=0");
			return -1;
		}	
	}
	int flag = 0;
	int hash_length = max(arr, num)+1;
	int* hash = create_array(hash_length);//创建稀疏数组，将arr的元素值对应到稀疏数组的索引
	for (int i = 0; i < hash_length; i++)
	{
		hash[i] = 0;
	}
	for (int i = 0; i < num; i++)
	{
		++hash[arr[i]];
		if (hash[arr[i]] > 1)
		{
			flag = 1;
			break;
		}
	}
	free(hash);
	return flag;
}
//检测长度为n的数组中重复，元素值为0至n-1范围内
void _swap_print_unique(const int* arr, int n, char seq = ' ')
{//通过交换把每个元素归位到以该元素为数组下标的位置上，结果是让a[i]=i
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < 0 || arr[i] >= n)
		{
			printf("要求元素值应为0至n-1范围内");
			return;
		}
	}
	int flag = 0;
	int* data = const_to_var(arr, n);
	for (int i = 0; i < n; i++)
	{
		while (data[i] != i)//当a[i]=i就是正常情况，直接continue
		{
			if (data[i] == data[data[i]])//有重复数时，比如a[3]=3&&a[4]=3中，当循环到i=4时，发现a[4]不等于4而等于3，而我们知道3应该在a[3]位置，所以重复
			{
				flag = 1;
				printf("%d%c", data[i], seq);
				break;
			}
			swap_2_int(data, i, data[i]);
		}
	}
	if (flag==0)
	{
		printf("无重复值");
		return;
	}
}
//输出有num个元素的一维数组中的重复值（要求元素值必须>=0）
void _hash_print_unique(const int* arr, int num, char seq=' ')
{
	int flag = 0;
	int hash_length = max(arr, num) + 1;
	int* hash = create_array(hash_length);
	for (int i = 0; i < hash_length; i++)
	{
		hash[i] = 0;
	}
	for (int i = 0; i < num; i++)
	{
		++hash[arr[i]];
		if (hash[arr[i]] == 2)
		{
			flag = 1;
			printf("%d%c", arr[i], seq);
		}
	}
	if(flag==0)
	{
		printf("无重复值");
	}
	free(hash);
}
int* _hash_return_unique(const int* arr, int num)
{
	int unique_count = 0;
	int hash_length = max(arr, num) + 1;
	int* hash = create_array(hash_length);
	for (int i = 0; i < hash_length; i++)
	{
		hash[i] = 0;
	}
	for (int i = 0; i < num; i++)
	{
		++hash[arr[i]];
		if (hash[arr[i]] == 2)
		{
			unique_count++;
		}
	}
	if (unique_count == 0)
	{
		printf("无重复值");
		return NULL;
	}
	int* res = create_array(unique_count + 1);
	int res_index = 1;
	res[0] = unique_count;
	for (int i = 0; i < hash_length; i++)
	{
		if (hash[i] > 1)
		{
			res[res_index] = i;
			res_index++;
		}
	}
	free(hash);
	return res;
}
//检测有num个元素的一维数组中是否有重复值
int test_unique(const int* arr, int num)
{
	int flag = 0;
	for (int i = 0; i < num - 1; i++)
	{
		flag = 0;
		for (int j = i + 1; j < num; j++)
		{
			if (arr[i] == arr[j])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			break;
		}
	}
	return flag;
}
/*//int* _unique_map(const int* arr, int num)
//{
//	int flag = 0;
//	int unique_count = 0;
//	int* res_data = create_array(num, 2);
//	for (int i = 0; i < num - 1; i++)
//	{
//		for (int j = i + 1; j < num; j++)
//		{
//			if (arr[i] == arr[j])
//			{
//				flag = 1;
//				*(res_data + unique_count * 2) = arr[i]; //第一列保存数组的值
//				*(res_data + unique_count * 2 + 1) = *(res_data + unique_count * 2 + 1) + 1;  //第二列保存数组值的出现次数
//				unique_count++;
//				break;
//			}
//		}
//	}
//	if (flag == 0)
//	{
//		printf("无重复值");
//		return NULL;
//	}
//	int* res = create_array(unique_count - 1, 2);
//	for (int i = 0; i < unique_count - 1; i++)
//	{
//		*(res + (i + 1) * 2) = *(res_data + i * 2);
//		*(res + (i + 1) * 2 + 1) = *(res_data + i * 2 + 1);
//	}
//	free(res_data);
//	*(res) = unique_count;
//	*(res + 1) = 2;
//	return res;
//}*/

//返回有num个元素的一维数组中的重复值，返回数组的第一项为重复值个数，之后项为重复值
int* return_unique(const int* arr, int num)
{
	if (min(arr, num) >= 0)
	{
		return _hash_return_unique(arr,num);
	}
	int arr_min = min(arr, num);
	int unique_count = 0;
	int hash_length = max(arr, num) + 1 - arr_min;
	int* hash = create_array(hash_length + 1);
	for (int i = 0; i < hash_length; i++)
	{
		hash[i] = 0;
	}
	for (int i = 0; i < num; i++)
	{
		++hash[arr[i] - arr_min];
		if (hash[arr[i] - arr_min] == 2)
		{
			unique_count++;
		}
	}
	if (unique_count == 0)
	{
		printf("无重复值");
		return NULL;
	}
	int* res = create_array(unique_count);
	int res_index = 1;
	res[0] = unique_count;
	for (int i = 0; i < hash_length; i++)
	{
		if (hash[i] > 1)
		{
			res[res_index] = i + arr_min;
			res_index++;
		}
	}
	free(hash);
	return res;
}
//输出长度为num的arr数组中的重复值，间隔符为seq
void print_unique(const int* arr, int num, char seq = ' ')
{
	if (min(arr, num) >= 0)
	{
		_hash_print_unique(arr, num, seq);
		return;
	}
	int arr_min = min(arr, num);
	int flag = 0;
	int hash_length = max(arr, num) + 1 - arr_min;
	int* hash = create_array(hash_length + 1);
	for (int i = 0; i < hash_length; i++)
	{
		hash[i] = 0;
	}
	for (int i = 0; i < num; i++)
	{
		++hash[arr[i] - arr_min];
		if (hash[arr[i] - arr_min] == 2)
		{
			flag = 1;
			printf("%d%c", arr[i], seq);
		}
	}
	if (flag == 0)
	{
		printf("无重复值");
	}
}

//对有序数组去重
int* _unique_sorted_array(int* data, int n)
{
	int slow = 0, fast = 0;//慢指针slow走在后面，快指针fast走在前面探路，找到一个不重复的元素就告诉slow并让slow前进一步。当fast指针遍历完整个数组nums后nums[0--slow]就是不重复元素。
	while (fast < n)
	{
		if (data[fast] != data[slow])
		{
			slow++;
			data[slow] = data[fast];
		}
		fast++;
	}
	return index_select_array(data, 0, slow);
}
//去重后的数组长度
int _unique_sorted_array_length(int* data, int n)
{
	int slow = 0, fast = 0;
	while (fast < n)
	{
		if (data[fast] != data[slow])
		{
			slow++;
			data[slow] = data[fast];
		}
		fast++;
	}
	return slow + 1;
}
//对数组去重，返回新数组
int* unique_constArray_normal(const int* a, int n, int isSorted=false)
{
	int* data = const_to_var(a, n);
	if (isSorted == false)
	{
		quick_sort(data, n);
	}
	return _unique_sorted_array(data, n);
}
//对数组去重，返回数组的第一个元素为新数组长度，之后为去重后的序列
int* unique_constArray_show(const int* a, int n, int isSorted = false)
{
	int* data = const_to_var(a, n);
	if (isSorted == false)
	{
		quick_sort(data, n);
	}
	int slow = 0, fast = 0;
	while (fast < n)
	{
		if (data[fast] != data[slow])
		{
			slow++;
			data[slow] = data[fast];
		}
		fast++;
	}
	int* res = create_array(slow + 2);
	res[0] = slow + 1;
	int res_index = 1;
	for (int i = 0; i < slow + 1; i++)
	{
		res[res_index] = data[i];
		res_index++;
	}
	return res;
}
int _unique_array_bySort(int* a, int n, int isSorted = false)
{
	if (isSorted == false)
	{
		quick_sort(a, n);
	}
	int slow = 0, fast = 0;
	while (fast < n)
	{
		if (a[fast] != a[slow])
		{
			slow++;
			a[slow] = a[fast];
		}
		fast++;
	}
	a = index_select_array(a, 0, slow);
	return slow + 1;
}
int _unique_array_byHash(int* a, int n)
{
	int arr_min = min(a, n);
	int unique_count = 0;
	int hash_length = max(a, n) + 1 - arr_min;
	int* hash = create_array(hash_length);
	for (int i = 0; i < hash_length; i++)
	{
		hash[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		++hash[a[i] - arr_min];
		if (hash[a[i] - arr_min] == 1)
		{
			unique_count++;
		}
	}
	int res_index = 0;
	for (int i = 0; i < hash_length; i++)
	{
		if (hash[i] >= 1)
		{
			a[res_index] = i + arr_min;
			res_index++;
		}
	}
	a = index_select_array(a, 0, unique_count - 1);
	free(hash);
	return unique_count;
}
int _unique_array_byLoop(int* a, int n)
{
	int* unique_value = create_array(n);//存储不重复的值
	unique_value[0] = a[0];
	int unique_value_len = 1;
	for (int i = 1; i < n; i++)
	{
		if (is_contain(a[i], unique_value, unique_value_len) == 0)
		{
			unique_value[unique_value_len] = a[i];//如果探到的值不在unique_value中就将其写入
			a[unique_value_len] = a[i];//用不重复的值覆盖重复值
			unique_value_len++;
		}
	}
	for (int i = unique_value_len; i < n; i++)
	{
		a[i] = 0;
	}
	free(unique_value);
	return unique_value_len;
}
//对数组去重（并排序），直接改变原数组，返回新数组元素个数
int unique_array_normal(int* a, int n, int isSorted = false)
{
	if (isSorted == true || n < 20)
	{
		return _unique_array_bySort(a, n, isSorted);
	}
	return _unique_array_byHash(a, n);
}
//合并两个有序且无重复的数组
int _merge_sorted_array(int* res, int* merge1, int merge1_length, int* merge2, int merge2_length)
{//使用双指针方法：将两个数组看作队列，每次从两个数组头部取出比较小的数字放到结果中
	int p1 = 0, p2 = 0;//创建两个指针分别指向merge1和merge2
	int res_index = 0;//计量res元素个数的量
	while (p1 < merge1_length && p2 < merge2_length)
	{
		if (merge1[p1] > merge2[p2])
		{
			res[res_index] = merge2[p2];
			p2++;
			res_index++;//放入一个元素，相应的指针就往后移一位
		}
		else
		{
			res[res_index++] = merge1[p1++];
		}
	}
	if (p1 == merge1_length)//如果merge1的元素已全部放入结果中，就把p2剩下的元素放入
	{
		while (p2 < merge2_length)
		{
			res[res_index++] = merge2[p2++];
		}
	}
	if (p2 == merge2_length)//如果merge2的元素已全部放入结果中，就把p1剩下的元素放入
	{
		while (p1 < merge1_length)
		{
			res[res_index++] = merge1[p1++];
		}
	}
	return res_index;
}
//对有序且无重复的数组合并并去重
int _merge_sorted_array_unique(int* res, int* merge1, int merge1_length, int* merge2, int merge2_length)
{//使用双指针方法
	int p1 = 0, p2 = 0;
	int res_index = 0;
	while (p1 < merge1_length && p2 < merge2_length)
	{
		if (merge1[p1] > merge2[p2])
		{
			res[res_index++] = merge2[p2++];
		}
		else if (merge1[p1] < merge2[p2])
		{
			res[res_index++] = merge1[p1++];
		}
		else
		{
			res[res_index++] = merge1[p1++];
			p2++;
		}
	}
	if (p1 == merge1_length)
	{
		while (p2 < merge2_length)
		{
			res[res_index++] = merge2[p2++];
		}
	}
	if (p2 == merge2_length)
	{
		while (p1 < merge1_length)
		{
			res[res_index++] = merge1[p1++];
		}
	}
	return res_index;
}
//只把两个数组的所有元素都放入新数组中
int _merge_normal_array(int* res, int* merge1, int merge1_length, int* merge2, int merge2_length)
{
	int res_index = 0;
	for (int i = 0; i < merge1_length; i++)
	{
		res[res_index++] = merge1[i];
	}
	for (int i = 0; i < merge2_length; i++)
	{
		res[res_index++] = merge2[i];
	}
	return res_index;
}
enum merge_array_method
{
	notSort_notUnique = 0, notSort_unique, sort_notUnique, sort_unique
};
//合并merge1和merge2，长度分别为merge1_length和merge2_length，将结果保存到res中，返回结果数组长度。res需预先申请内存空间，即：int* res = new int[merge1_length + merge2_length]; merge_array(res,...);
//还需传入枚举类型notSort_notUnique||notSort_unique||sort_notUnique||sort_unique控制是否进行排序sort（从小到大）和去重unique
//is_sorted_and_uniqued参数表示原数组是否有序且无重复元素（默认为false）
int merge_array(int* res, int* merge1, int merge1_length, int* merge2, int merge2_length, merge_array_method method = notSort_notUnique, bool is_sorted_and_uniqued = false)
{
	int len;
	switch (method)
	{
	case notSort_notUnique:
		len = _merge_normal_array(res, merge1, merge1_length, merge2, merge2_length);
		return len;
		break;
	case notSort_unique:
		len = _merge_normal_array(res, merge1, merge1_length, merge2, merge2_length);
		return _unique_array_byLoop(res, len);
		break;
	case sort_notUnique:
		len = _merge_normal_array(res, merge1, merge1_length, merge2, merge2_length);
		quick_sort(res, len);
		return len;
		break;
	case sort_unique:
		if (is_sorted_and_uniqued == false)
		{
			merge1_length = unique_array_normal(merge1, merge1_length);
			merge2_length = unique_array_normal(merge2, merge2_length);
		}
		return _merge_sorted_array_unique(res, merge1, merge1_length, merge2, merge2_length);
		break;
	default:
		printf("输入数据有误%s", __func__);
		res = NULL;
		return -1;
		break;
	}
}
#endif