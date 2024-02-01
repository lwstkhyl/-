#pragma once
#ifndef _wth_string_h_
#define _wth_string_h_
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<limits.h>
struct my_string
{
public:
	//用c字符串给my_string赋值，注意该方法只能在声明my_string类对象同时赋值情况下使用
	my_string(const char* str = "");
	//用另一个my_string给my_string赋值，注意该方法只能在声明my_string类对象同时赋值情况下使用
	my_string(const my_string& str);
	//重载=运算符：用c字符串给my_string赋值
	my_string& operator=(const char* str);
	//重载=运算符：用另一个my_string给my_string赋值
	my_string& operator=(const my_string& str);
	
	//形参的&：可改变实参的值，相比指针可读性更强
	//返回值的&：对于class或struct，如果直接返回可能出现问题（官方推荐使用指针或引用返回）
	//&不用分配新的内存，一定程度上提高运行效率

	//输出my_string字符串
	void display() const;
	//得到字符串长度
	int length() const;
	//判断字符串是否为空
	bool is_empty() const;
	//函数后面加const表示函数不可以修改class的成员

	//重载!运算符，若字符串不空则返回true 
	bool operator!() const;
	//重载[]运算符，根据索引获取字符（形参和返回值都为const，不可更改）
	const char& operator[](unsigned int index) const;
	//重载[]运算符，使用[index]更改字符串中字符
	char& operator[](unsigned int index);
	//重载+运算符，实现字符串拼接
	friend my_string operator+(const my_string& s1, const my_string& s2);//类内运算符重载时只能有且仅有一个参数，因此需声明为友元函数类外实现
	//重载+=运算符
	my_string& operator+=(const my_string& str);

	//析构函数
	~my_string();
private:
	char* my_c_string;//my_string类的实际存储方式--c字符串
	//复制一个str（c字符串），包括分配内存
	char* new_c_string(const char* str);
	//将str赋值给my_string类对象，原对象删去
	my_string& assign(const char* str);
};

char* my_string::new_c_string(const char* str)
{
	int length = strlen(str) + 1;//strlen()函数计算字符串str的长度，不包括空结束字符。因此总长度需要在它的基础上+1，结束字符也占内存
	char* new_c_str = new char[length];//申请内存
	memset(new_c_str, 0, length);//memset(str,c,n)函数复制字符c（一个无符号字符）到参数str所指向的字符串的前n个字符。用于在一段内存块中填充某个给定的值，常用于对较大数组清零
	strcpy(new_c_str, str);//strcpy(a,b)函数将b字符串复制到a
	return new_c_str;
}
my_string& my_string::assign(const char* str)
{//赋值操作：先删去原值，再赋上新值
	delete[] my_c_string;//释放原值所占内存
	my_c_string = new_c_string(str);//赋新值
	return *this;//将赋值完成的对象返回
}
my_string::my_string(const char* str)
{
	my_c_string = new_c_string(str);
}
my_string::my_string(const my_string& str)
{
	my_c_string = new_c_string(str.my_c_string);//复制my_string类对象就是复制my_c_string这个存储值
}
my_string& my_string::operator=(const char* str)
{
	return assign(str);
}
my_string& my_string::operator=(const my_string& str)
{
	if (this == &str)//如果赋值符号左右两面是同一个对象（地址相同），那么如果按assign中直接释放原值（左值）内存，则右值（新值）也跟着被释放了（用的是同一块内存）
		return *this;//不用释放，直接返回新值就可以（新值=旧值）
	return assign(str.my_c_string);
}
void my_string::display() const
{
	printf("%s\n", my_c_string);
}
int my_string::length() const
{
	return strlen(my_c_string);
}
bool my_string::is_empty() const
{
	return length() == 0;
}
bool my_string::operator!() const
{
	return !is_empty();
}
const char& my_string::operator[](unsigned int index) const
{
	return my_c_string[index];
}
char& my_string::operator[](unsigned int index)
{
	//常量指针指向的空间的内容不允许被修改，但是使用const_cast进行强制转换就可以修改
	//static_cast相当于把隐式转换给明确写了出来
	return const_cast<char&>(static_cast<const my_string&>(*this)[index]);
	//(*this)指调用[]的my_string类型对象，static_cast<const my_string&>(*this)将这个对象转成const my_string&类型，使之能调用上面定义的const char& operator[]() const运算符，并返回一个const char&类型值，是指my_string串的字符
	//为了能够修改这个值，需要将其变为非const类型；返回其引用，使其能作为左值
}
my_string& my_string::operator+=(const my_string& str)
{//更改this的my_c_string为新值
	int len = strlen(my_c_string) + strlen(str.my_c_string) + 1;//新my_c_string长度，注意结束符要多占1个内存
	char* new_c_string = new char[len];//申请内存
	memset(new_c_string, 0, len);
	strcpy(new_c_string, my_c_string);
	strcat(new_c_string, str.my_c_string);//strcat用于将一个字符串追加到另一个字符串的结尾（覆盖前字符串的结束符），由于str.my_c_string有结束符，所以不用额外加
	delete[] my_c_string;//删除原值，因为新值是新申请的内存并已完成写入，不用担心删除内存使内存丢失
	//就算形参str和*this是同一个对象，新值赋值就相当于str赋值，不可能出现str在+=后丢失数据的情况
	my_c_string = new_c_string;
	return *this;
}
//重载+运算符，实现字符串拼接
my_string operator+(const my_string& s1, const my_string& s2)
{
	my_string str = s1;
	str += s2;
	return str;
}

my_string::~my_string()
{
	delete[] my_c_string;//释放存储信息的内存
}


//测量char a[row][col]型二维数组列数，max_col为正常情况下最大可测量列数，默认为200；特殊情况：实际列数超过它或只有1行，返回第一行字符串长度（包括'\0'）
//使用方式：char a[row][col];  int len = __get_col(*a,...); 正常结果len==col
//注意：重要前提是a已完成初始化（将空余位置补成'\0'），如a[row][col]={""};
int __get_col(char* a, int max_col = 200)
{
	int col = 1;//至少应有1列
	int flag = 1;//是否超过可测量列数
	while (!(*(a + col - 1) == '\0' && *(a + col) != '\0'))//只测第一行（数组至少有1行）
	{//因为二维数组在内存存储连续，第一行的末尾*(a + col - 1)一定是 '\0'，正常情况下第二行开头*(a + col)非'\0'
		col++;
		if (col > max_col)
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1)
	{
		return col;
	}
	else//只有1行或第一行长度超过max_col时
	{
		return strlen(a) + 1;
	}
}
//判断a是否能打印输出（为正规字符）
bool _can_print(char a)
{
	if (a < -1 || a>255)
		return false;
	return isprint(a);
}

//展示a字符串的前num个字符，默认展示全部，间隔符默认为空
void show_string(const char* a, int num = -1, char seq = '\0')
{
	if (a == NULL)
	{
		printf("%s输入数组为NULL\n", __func__);
		return;
	}
	if (num < -1 || num == 0)
	{
		printf("%s输入数据有误\n", __func__);
		return;
	}
	if (a[0] == '\0')
	{
		printf("为空字符串");
		return;
	}
	if (num == -1)
	{
		for (int i = 0; a[i] != '\0'; i++)
		{
			if (a[i + 1] == '\0')//使最后一个字符后面没有分隔符
			{
				printf("%c", a[i]);
				return;
			}
			printf("%c%c", a[i], seq);
		}
		//printf("\n");
	}
	for (int i = 0; i < num; i++)
	{
		if (a[i] == '\0')
		{
			printf("\n%s要展示的长度超出字符串长度", __func__);
			return;
		}
		if (a[i + 1] == '\0' || i >= num-1)//使最后一个字符后面没有分隔符
		{
			printf("%c", a[i]);
		}
		else
		{
			printf("%c%c", a[i], seq);
		}
	}
	//printf("\n");
}
//展示row行col列的二维字符串数组（每行为一个字符串），每行字符串展示的间隔符为word_seq（默认为空格），同字符串各字符间隔符为letter_seq（默认为空）
//传入方式：char a[n][m]; show_string_2(*a,...)
void show_string_2(const char* p, int row, int col, char word_seq = ' ', char letter_seq = '\0')
{
	if (p == NULL)
	{
		printf("%s输入数组为NULL\n",__func__);
		return;
	}
	if (row <= 0 || col <= 0)
	{
		printf("%s输入数据有误\n", __func__);
		return;
	}
	for (int i = 0; i < row; i++)
	{
		if (!_can_print(*(p + i * col)))
		{
			printf("\n%s要展示的行数超出字符串行数", __func__);
			break;
		}
		show_string(p + i * col, -1, letter_seq);
		printf("%c", word_seq);
	}
	printf("\n");
}
//将有col列的二维字符串数组（每行为一个字符串）的所有行展示，每行字符串展示的间隔符为word_seq（默认为空格），同字符串各字符间隔符为letter_seq（默认为空）
//传入方式：char a[n][m]; show_string_2(*a,...)
void show_string_2(const char* p, int col, char word_seq = ' ', char letter_seq = '\0')
{
	if (p == NULL)
	{
		printf("%s输入数组为NULL\n", __func__);
		return;
	}
	if (col <= 0)
	{
		printf("%s输入数据有误\n", __func__);
		return;
	}
	for (int i = 0; _can_print(*(p + i * col)); i++)
	{
		show_string(p + i * col, -1, letter_seq);
		printf("%c", word_seq);
	}
	printf("\n");
}
//展示二维字符串数组（每行为一个字符串）的前row行，默认全部内容，每个字符串间隔符为word_seq，默认为空格
//传入方式：char** a; show_string_2(a,...)
void show_string_2(char** p, char word_seq = ' ', int row = INT_MAX)
{
	if (p == NULL)
	{
		printf("%s输入数组为NULL\n", __func__);
		return;
	}
	int i = 0;
	for (; _can_print(p[i][0]) && i < row; i++)
	{
		printf("%s%c", p[i], word_seq);
	}
	if (i < row && row != INT_MAX)
	{
		printf("\n%s要展示的行数超出字符串行数", __func__);
	}
	printf("\n");
}
//展示二维字符串数组（每行为一个字符串）的前row行，默认全部内容，每个字符串间隔符为word_seq，默认为空格
//传入方式：const char** a; show_string_2(a,...)
//void show_string_2(const char** p, int row = INT_MAX, char word_seq = ' ')
//{
//	show_string_2(p, row, word_seq);
//}

//判断a是不是分隔符
bool _is_delimeter(const char* delimeter, char a)
{
	for (int i = 0; delimeter[i] != '\0'; i++)
	{
		if (a == delimeter[i])
		{
			return true;
		}
	}
	return false;
}
//每执行一次该函数，按顺序返回data中的一个单词。当返回NULL时表示无单词可提取
//delimeter数组表示分隔符，默认为" "；max_length为要提取的最大单词长度，默认为50
char* _get_word(const char* data, const char* delimeter = " ", int max_length = 50)
{
	char* word = new char[max_length];
	static int pos = 0;//记录已读取数据的位置，static使下一次执行该函数时，pos不改变，使从新的位置读数据
	if (data[pos] == '\0')//已提取完，返回NULL
	{
		return NULL;
	}
	while (data[pos] != '\0' && _is_delimeter(delimeter, data[pos]))//是分隔符就跳过
	{
		pos++;
	}
	int word_index = 0;//向结果数组word中写入单词的索引
	while (data[pos] != '\0' && !_is_delimeter(delimeter, data[pos]))//不是分割符就进行写入，一直写入到data[pos]又是分隔符（此时退出循环）
	{
		word[word_index] = data[pos];
		pos++;
		word_index++;
	}
	word[word_index] = '\0';//对结果串进行封闭
	if (word[0] == '\0')//说明data以分割符结尾，最后一次提取时提取不到内容，直接返回NULL
	{
		return NULL;
	}
	else
	{
		return word;
	}
}
//统计单词数，delimeter为分隔符，默认为空格
int word_number(const char* a, const char* delimeter = " ")//思路：根据变换来判断是否是一个单词，如果当前字符是字母下一个是空格，那么这就是一个单词，或者当前是空格下一个是字母，也是一个单词。
{//对于当前是空格下一个是单词，需要讨论开头是否有空格
	int count = 0;
	for (int i = 0; a[i + 1] != '\0'; i++)
	{
		if (_is_delimeter(delimeter, a[i]) && !_is_delimeter(delimeter, a[i + 1]))//如果当前字符是分隔符，而下一个字符不是，则单词数+1
		{
			count++;
		}
	}
	if (!_is_delimeter(delimeter, a[0]))//如果开头不是分隔符，直接是单词，就需要补上它（因为前面的判断逻辑是“分隔符+单词”）{
	{
		return count + 1;
	}
	return count;//开头是分隔符，就说明所有单词都符合判断模式，不用+1
}
//提取data里面的单词，分隔符为delimeter，默认为空格。每个单词最大长度为max_word_length，默认为50；最大总单词数为max_word_numbe，默认为100
//使用方式：char** res = word_list(data,...);
char** word_list(const char* data, const char* delimeter = " ", int max_word_length = 50, int max_word_number = 100)
{
	char** res = new char* [max_word_number];
	for (int i = 0; i < max_word_number; i++)
	{
		res[i] = new char[max_word_length];
	}
	char* word;
	int res_index = 0;
	while (word = _get_word(data, delimeter))
	{
		strcpy(res[res_index], word);
		res_index++;
	}
	return res;
}
//提取data里面的单词，分隔符为delimeter，默认为空格，将结果保存在res中。每个单词最大长度为max_word_length，默认为50；最大总单词数为max_word_numbe，默认为100
//使用方式：char** res = new char* [100];  int len = word_list(res,data,...);
int word_list(char** res, const char* data, const char* delimeter = " ", int max_word_length = 50, int max_word_number = 100)
{
	for (int i = 0; i < max_word_number; i++)
	{
		res[i] = new char[max_word_length];
	}
	char* word;
	int res_index = 0;
	while (word = _get_word(data, delimeter))
	{
		strcpy(res[res_index], word);
		res_index++;
	}
	return res_index;
}

//统计二维字符串数组的行数（字符串数）
int word_list_length(char** data)
{
	int count = 0;
	while (_can_print(data[count][0]))
	{
		count++;
	}
	return count;
}
//将输入内容存储在char*中返回，结束符为end_char，默认为回车，且它不会出现在结果中。max_length设定存储最大长度，默认为256
//使用方式：char *str = cin_string(...);
char* cin_string(char end_char = '\n', int max_length = 256)
{
	char* res = new char[max_length];
	int i = 0;
	char ch;
	while ((ch = getchar()) != end_char)
	{
		res[i] = ch;
		i++;
	}
	res[i] = '\0';
	return res;
}
//将输入内容存储在res中，返回输入内容的长度（不包括结束符和'\0'），结束符为end_char，默认为回车，且它不会出现在结果中
//使用方式：char* res = new char[256]; int len = cin_string(res,...);
int cin_string(char* res, char end_char = '\n')
{
	int i = 0;
	char ch;
	while ((ch = getchar()) != end_char)
	{
		res[i] = ch;
		i++;
	}
	res[i] = '\0';
	return i;
}
#endif