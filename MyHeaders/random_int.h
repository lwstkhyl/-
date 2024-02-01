#pragma once
#ifndef _random_int_h_
#define _random_int_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//生成随机整数
int random_int()
{
    int a;
    srand(time(NULL));
    a = rand();
    return a;
}
//生成0-max的随机整数
int random_int(int max)
{
    int a;
    srand(time(NULL));
    a = rand() % (max + 1);
    return a;
}
//生成min-max的随机整数
int random_int(int min, int max)
{
    int a;
    srand(time(NULL));
    a = rand() % (max - min + 1) + min;
    //rand()是生成0-32767的随机数  以min=-10 max=10为例：rand() % 21对前面生成的随机数取模，表示0-20的随机数  rand() % 21 - 10就是对0-20的范围减10变为-10至10的范围
    return a;
}
//生成n长度的随机数组，元素值为[min,max]区间
//注意在同一次执行main时要想多次调用random_int_seq系列函数，需要在每一次调用后加上Sleep(1000);使随机序列不同
int* random_int_seq(int n,int min,int max)
{
    srand(time(NULL));
    int* arr;
    if ((arr = (int*)malloc(sizeof(int) * n)) == NULL) 
    { 
        printf("random_int_seq分配内存空间失败!\n");
        return NULL;
    }
    for (int i = 0; i < n; i++) 
    { 
        arr[i] = (rand() % (max - min + 1) + min);
    }
    //为什么不在循环内写srand(time(NULL));
    //同一循环中time(NULL)的值相同（循环执行的太快），使种子被设定相同，于是数组中每个数都是相同的，无法达到预期效果
    //解决办法是在random_int_seq中加上srand(time(NULL));  这样每次执行random_int_seq生成的随机数组就不同（调用random_int_seq至少相隔1s）
    return arr;
}
//生成n长度的随机数组，元素值为随机整数
//注意在同一次执行main时要想多次调用random_int_seq系列函数，需要在每一次调用后加上Sleep(1000);使随机序列不同
int* random_int_seq(int n)
{
    srand(time(NULL));
    int* arr;
    if ((arr = (int*)malloc(sizeof(int) * n)) == NULL)
    {
        printf("random_int_seq分配内存空间失败!\n");
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }
    return arr;
}
//生成n长度的随机数组，元素值为[0,max]区间
//注意在同一次执行main时要想多次调用random_int_seq系列函数，需要在每一次调用后加上Sleep(1000);使随机序列不同
int* random_int_seq(int n,int max)
{
    srand(time(NULL));
    int* arr;
    if ((arr = (int*)malloc(sizeof(int) * n)) == NULL)
    {
        printf("random_int_seq分配内存空间失败!\n");
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (max + 1);
    }
    return arr;
}
//生成min到max的随机数列，包含max-min+1个元素
//注意在同一次执行main时要想多次调用random_int_seq系列函数，需要在每一次调用后加上Sleep(1000);使随机序列不同
int* random_int_seq_unique(int min, int max)//生成min到max的随机数列，包含max-min+1个元素
{
    if (min > max)
    {
        printf("random_int_seq_unique输入数据有误：最大值应大于最小值");
        return NULL;
    }
    srand(time(NULL));
    int* arr;
    if ((arr = (int*)malloc(sizeof(int) * (max - min + 1))) == NULL)
    {
        printf("random_int_seq_unique分配内存空间失败!\n");
        return NULL;
    }
    for (int i = min; i <= max; i++)
    {
        arr[i - min] = i;
    }
    for (int i = 0; i < max - min + 1; i++)
    {
        int rand_idx = i + rand() % (max - min + 1 - i);
        swap_2_int(arr, i, rand_idx);
    }
    return arr;
}
//生成含n个数的不重复数列，元素取值为[min,max]
//注意在同一次执行main时要想多次调用random_int_seq系列函数，需要在每一次调用后加上Sleep(1000);使随机序列不同
int* random_int_seq_unique(int n, int min, int max)//生成含n个数的不重复数列，元素取值为[min,max]
{
    if (max - min + 1 == n && n > 0)
    {
        return random_int_seq_unique(min, max);
    }
    if (max - min + 1 < n || n <= 0)
    {
        printf("random_int_seq_unique输入数据有误：最大值应大于最小值/数列长度应大于0");
        return NULL;
    }
    srand(time(NULL));
    int* arr;
    if ((arr = (int*)malloc(sizeof(int) * (max - min + 1))) == NULL)
    {
        printf("random_int_seq_unique分配内存空间失败!\n");
        return NULL;
    }
    int* res;
    if ((res = (int*)malloc(sizeof(int) * (max - min + 1))) == NULL)
    {
        printf("random_int_seq_unique分配内存空间失败!\n");
        return NULL;
    }
    for (int i = min; i <= max; i++)
    {
        arr[i - min] = i;//将min到max的整数放入一个数组中
    }
    for (int i = 0; i < n; i++) 
    {
        int rand_idx = i + rand() % (max - min + 1 - i);//从前到后依次遍历前n个元素，并等概率地将其与自己或自己后面的元素交换
        swap_2_int(arr, i, rand_idx);
        res[i] = arr[i];//将已完成交换的元素保存到结果中
    }
    free(arr);
    return res;
}
#endif