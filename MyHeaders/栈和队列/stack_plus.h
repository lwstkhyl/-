#pragma once
#include"my_stack.h"
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