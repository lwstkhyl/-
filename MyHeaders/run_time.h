#pragma once
#ifndef _run_time_h
#define _run_time_h
#include<windows.h>
//输出代码运行时间
//使用方式：printf_rum_time(/*要测量运行时间的代码*/);
//如printf_rum_time(for (int i = 0; i < 100; i++) printf("%d", i););
//为避免变量冲突，同一main中测多段时间应用不同的printf_run_time
#define printf_run_time(func) \
do{\
double run_time;\
LARGE_INTEGER time_start;\
LARGE_INTEGER time_over;\
double dqFreq;\
LARGE_INTEGER f;\
QueryPerformanceFrequency(&f);\
dqFreq = (double)f.QuadPart;\
QueryPerformanceCounter(&time_start);func;QueryPerformanceCounter(&time_over);\
run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;\
printf("\nrun_time：%fus\n", run_time);\
}while(0)
//输出代码运行时间
//使用方式：printf_rum_time1(/*要测量运行时间的代码*/);
//如printf_rum_time1(for (int i = 0; i < 100; i++) printf("%d", i););
//为避免变量冲突，同一main中测多段时间应用不同的printf_run_time
#define printf_run_time1(func) \
do{\
double run_time1;\
LARGE_INTEGER time_start1;\
LARGE_INTEGER time_over1;\
double dqFreq1;\
LARGE_INTEGER f1;\
QueryPerformanceFrequency(&f1);\
dqFreq1 = (double)f1.QuadPart;\
QueryPerformanceCounter(&time_start1);func;QueryPerformanceCounter(&time_over1);\
run_time1 = 1000000 * (time_over1.QuadPart - time_start1.QuadPart) / dqFreq1;\
printf("\nrun_time：%fus\n", run_time1);\
}while(0)
//输出代码运行时间
//使用方式：printf_rum_time2(/*要测量运行时间的代码*/);
//如printf_rum_time2(for (int i = 0; i < 100; i++) printf("%d", i););
//为避免变量冲突，同一main中测多段时间应用不同的printf_run_time
#define printf_run_time2(func) \
do{\
double run_time2;\
LARGE_INTEGER time_start2;\
LARGE_INTEGER time_over2;\
double dqFreq2;\
LARGE_INTEGER f2;\
QueryPerformanceFrequency(&f2);\
dqFreq2 = (double)f2.QuadPart;\
QueryPerformanceCounter(&time_start2);func;QueryPerformanceCounter(&time_over2);\
run_time2 = 1000000 * (time_over2.QuadPart - time_start2.QuadPart) / dqFreq2;\
printf("\nrun_time：%fus\n", run_time2);\
}while(0)
#endif