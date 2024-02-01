#pragma once
#ifndef _wth_number_h_
#define _wth_number_h_
#include"wth_intArray.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
//判断num是不是素数
bool is_prime_base(int num)
{
	if (num <= 1)
	{
		return false;
	}
	if (num == 2)
	{
		return true;
	}	
	if (num % 2 == 0)
	{
		return false;
	}
	int end = sqrt(num);
	for (int i = 3; i <= end; i+=2)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}
//返回[min,max]范围内的素数数量
int array_prime_number_base(int min, int max)
{
	int count = 0;
	for (int i = min; i <= max; i++)
	{
		if (is_prime_base(i) == true)
			count++;
	}
	return count;
}
//判断num是不是素数（基于孪生素数法）
bool is_prime(int num)//原理：大于等于5的素数一定是分布在6倍数的左右两侧，但在6倍数左右两侧的数不一定是素数
{
	if (num <= 1)
	{
		return false;
	}
	if (num == 2 || num == 3)
	{
		return true;
	}
	if (num % 6 != 1 && num % 6 != 5)//如果不在6倍数的两侧就一定不是质数
	{
		return false;
	}
	int end = sqrt(num);
	for (int j = 5; j <= end; j += 6)//在6倍数两侧并且不是质数的数：能整除这个6倍数的左边数或右边数
	{
		if (num % j == 0 || num % (j + 2) == 0)//如果该数能整除6倍数两侧的数，就不是质数
		{
			return false;
		}
	}
	return true;
}
//res[n]的值代表n是否为素数，返回max+1
int _array_prime_bool_bySelect(bool** res, int max)//原理：找出小于等于n的开方的素数，然后将n内所有这些素数的倍数统统去掉，剩下的数就都是素数
{
	*res = new bool[max+1];
	for (int i = 0; i <= max; i++)//先默认所有数都是素数
	{
		(*res)[i] = true;
	}
	(*res)[0] = false;
	(*res)[1] = false;
	for (int i = 2; i * i <= max; i++)//小于等于n的开方的数
	{
		if ((*res)[i] && is_prime(i))//如果i是素数，就把它的倍数都去掉，注意不要把它自己给去掉
		{//*res[i]的意义是 如果已经知道它不是素数了，就不用重复去掉它的倍数了
			int beishu = 2;//倍数
			int index = i * beishu;//要去掉的倍数的索引
			while (index <= max)
			{
				(*res)[index] = false;
				beishu++;
				index = i * beishu;
			}
		}
	}
	return max + 1;
}
//返回[min,max]的素数数量
int array_prime_number(int min, int max)
{
	if (min < 0 || max<0 || min>max)
	{
		printf("%s输入数据有误", __func__);
		return -1;
	}
	int count = 0;
	int flag = 1;
	for (int i = min; i <= max; i++)
	{
		if (i == 0 || i == 1)
			continue;
		if (i == 2 || i == 3)
		{
			count++;
			continue;
		}
		if (i % 6 != 1 && i % 6 != 5)
			continue;
		int end = sqrt(i);
		for (int j = 5; j <= end; j += 6)
		{
			if (i % j == 0 || i % (j + 2) == 0)
			{
				flag = 0;
				break;//不是质数，跳出循环
			}
		}
		if (flag == 0)//如果不是质数，直接执行下一次循环
		{
			flag = 1;//重置flag
			continue;
		}
		count++;//是质数
	}
	return count;
}
//返回[0,max]的素数数量
int array_prime_number(int max)
{
	if (max <= 2)
	{
		return array_prime_number(0, max);
	}
	bool* res;
	int len = _array_prime_bool_bySelect(&res, max);
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (res[i] == 1)
		{
			count++;
		}
	}
	return count;
}
//输出[min,max]的素数
void array_prime_print(int min, int max, char seq = ' ')
{
	if (min < 0 || max<0 || min>max)
	{
		printf("%s输入数据有误", __func__);
		return;
	}
	int flag = 1;
	for (int i = min; i <= max; i++)
	{
		if (i == 0 || i == 1)
			continue;
		if (i == 2 || i == 3)
		{
			printf("%d%c", i, seq);
			continue;
		}
		if (i % 6 != 1 && i % 6 != 5)
			continue;
		int end = sqrt(i);
		for (int j = 5; j <= end; j += 6)
		{
			if (i % j == 0 || i % (j + 2) == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
		{
			flag = 1;
			continue;
		}
		printf("%d%c", i, seq);
	}
}
//输出[0,max]的素数
void array_prime_print(int max, char seq = ' ')
{
	if (max <= 2)
	{
		array_prime_print(0, max, seq);
		return;
	}
	bool* res;
	int len = _array_prime_bool_bySelect(&res, max);
	for (int i = 0; i < len; i++)
	{
		if (res[i] == 1)
		{
			printf("%d%c", i, seq);
		}
	}
	return;
}

int gcd(int a, int b) //辗转相除法：用较小数除较大数，再用出现的余数（第一余数）去除除数，再用出现的余数（第二余数）去除第一余数，直到最后余数是0，得到的最大公约数就是最后的除数
{//假设a<b
	int temp; //表示余数
	while (temp = a % b)
	{
		a = b;
		b = temp;
	}
	return b;
}
//返回a和b的最大公约数
int GCD(int a, int b) //辗转相除法
{
	if (a < b)
		return gcd(a, b);
	else
		return gcd(b, a);
}
//返回a和b的最小公倍数
int LCM(int a, int b) //先求a和b的最大公约数c，再a*b/c即为最小公倍数
{
	return a * b / GCD(a, b);
}
#endif