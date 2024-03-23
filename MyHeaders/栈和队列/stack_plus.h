#pragma once
#include"my_stack.h"
#include<string>
#include<ctype.h>
using std::string;
//判断str中的括号()[]{}是否正确匹配，若正确匹配则返回true，否则返回false
bool brackets_match(const char* str)
{
	stack s = init_stack(); //创建一个空栈
	int data; //用于存储弹出栈的元素
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			push(s, str[i]);
		}
		else if (str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			pop(s, data);
			switch (str[i])
			{
			case ')':
				if (data != '(') return false;
				break;
			case ']':
				if (data != '[') return false;
				break;
			case '}':
				if (data != '{') return false;
				break;
			}
		}
		else;
	}
	return is_empty(s); //若栈空，则括号匹配，返回true；否则返回false
}

//定义各符号的优先级
int _define_priority(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1; //+-的优先级为1
	case '*':
	case '/':
		return 2; //*/的优先级为2
	default:
		return 0;
	}
}
//判断c是不是字母/数字
bool is_var(char c)
{
	return isalpha(c) || isdigit(c);
}
//正常表达式转后缀表达式
string infix_to_postfix(const char* str)
{
	stack optr = init_stack(); //用于储存运算符的栈
	string res;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (is_var(str[i])) //如果是单字母变量/数字
			res += str[i]; //就把它添加到结果数组中
		else if (str[i] == '(') //如果遇到左括号
			push(optr, str[i]); //就将其压入栈中
		else if (str[i] == ')') //如果遇到右括号
		{
			while (!is_empty(optr) && char(get_top(optr)) != '(') //直到遇到左括号/栈空为止
			{
				res += char(get_top(optr));
				pop(optr);  //从栈中弹出运算符并添加到结果数组中
			}
			if (char(get_top(optr)) == '(') pop(optr); //并将左括号出栈
		}
		else //如果遇到运算符
		{
			while (!is_empty(optr) &&
				_define_priority(get_top(optr)) >= _define_priority(str[i])) 
			{ //先从栈中弹出所有优先级更高或相等的运算符
				res += char(get_top(optr)); //并添加到结果数组中
				pop(optr); 
			}
			push(optr, str[i]); //再压入栈中
		}
	}
	while (!is_empty(optr)) //如果表达式已遍历完毕，但栈中仍有运算符
	{
		res += char(get_top(optr)); //就将它们全部添加到结果数组中
		pop(optr);
	}
	return res;
}