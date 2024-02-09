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
#include"random_int.h"
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

	//去除字符串两边空格，返回新字符串，all控制是否去除全部空格（默认false不去除全部）；若该字符串只由空格组成则返回空串
	my_string trim(bool all = false);
	//字符串切片，返回索引[start,end)的新字符串
	my_string slice(int start,int end);
	//字符串删除，在index的位置总共删除num个元素（包括index的那个元素），默认从开头删一个元素
	my_string splice(int index = 0, int num = 1);

	//重载!运算符，若字符串不空则返回true 
	bool operator!() const;
	//重载==运算符，比较字符串是否相等（比较的是字符ASCII码大小）
	bool operator==(const my_string& str) const;
	//重载>运算符（比较的是字符ASCII码大小）
	bool operator>(const my_string& str) const;
	//重载<运算符（比较的是字符ASCII码大小）
	bool operator<(const my_string& str) const;
	//重载>=运算符（比较的是字符ASCII码大小）
	bool operator>=(const my_string& str) const;
	//重载<=运算符（比较的是字符ASCII码大小）
	bool operator<=(const my_string& str) const;
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
	if ((this->length()) == 0)
	{
		printf("字符串为空\n");
		return;
	}
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

my_string my_string::trim(bool all)
{
	int len = strlen(my_c_string);
	int left = 0, right = len - 1;
	for (; left < len; left++)
	{
		if (my_c_string[left] != ' ')
		{
			break;
		}
	}
	if (left == len) //整个字符串只有空格
	{
		printf("%s：字符串只有空格", __func__);
		return my_string(); //返回空串
	}
	for (; right >= 0; right--)
	{
		if (my_c_string[right] != ' ')
		{
			break;
		}
	}
	if (all == false) return this->slice(left, right + 1);
	char* new_string = new char[right - left + 2];
	int p1 = 0, p2 = left; //p2探测 p1赋值
	while (p2 <= right)
	{
		if (my_c_string[p2] != ' ')
		{
			new_string[p1] = my_c_string[p2];
			p1++;
			p2++;
		}
		if (my_c_string[p2] == ' ') p2++;
	}
	new_string[p1] = '\0';
	return my_string(new_string);
}
my_string my_string::slice(int start, int end) 
{
	if (start >= end)
	{
		printf("%s输入数据有误", __func__);
		return my_string();
	}
	char* new_string = new char[end - start];
	int new_string_index = 0;
	for (int i = start; i < end; i++)
	{
		new_string[new_string_index] = my_c_string[i];
		new_string_index++;
	}
	new_string[new_string_index] = '\0';
	return my_string(new_string);
}
my_string my_string::splice(int index, int num)
{
	int p1 = 0, p2 = 0; //p2探测 p1赋值
	int len = strlen(my_c_string);
	char* new_string = new char[len - num + 1];
	while (p2 < len)
	{
		if (p2 != index)
		{
			new_string[p1] = my_c_string[p2];
			p1++;
			p2++;
		}
		if (p2 == index)
			p2 += num;
	}
	new_string[p1] = '\0';
	return my_string(new_string);
}
bool my_string::operator!() const
{
	return !is_empty();
}
bool my_string::operator==(const my_string& str) const
{
	return strcmp(my_c_string, str.my_c_string) == 0;
}
bool my_string::operator>(const my_string& str) const
{
	return strcmp(my_c_string, str.my_c_string) > 0;
}
bool my_string::operator<(const my_string& str) const
{
	return strcmp(my_c_string, str.my_c_string) < 0;
}
bool my_string::operator>=(const my_string& str) const
{
	return strcmp(my_c_string, str.my_c_string) >= 0;
}
bool my_string::operator<=(const my_string& str) const
{
	return strcmp(my_c_string, str.my_c_string) <= 0;
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

//判断a是否能打印输出（为正规字符）
bool _can_print(char a)
{
	if (a < -1 || a > 255)
		return false;
	return isprint(a);
}
//测量char a[row][col]型二维数组列数，max_col为正常情况下最大可测量列数，默认为100；特殊情况：实际列数超过它或只有1行，返回第一行字符串长度（包括'\0'）
//使用方式：char a[row][col];  int len = __get_col(*a,...); 正常结果len==col
//注意：重要前提是a已完成初始化（将空余位置补成'\0'），如a[row][col]={""};
int __get_col(const char* a, int max_col = 100)
{
	int col = 1;//至少应有1列
	int flag = 1;//是否超过可测量列数
	while (!(!_can_print(*(a + col - 1)) && _can_print(*(a + col))))//只测第一行（数组至少有1行）
	{//因为二维数组在内存存储连续，第一行的末尾*(a + col - 1)一定是 '\0'，正常情况下第二行开头*(a + col)非'\0'
		col++;
		if (col > max_col)//无法根据这个原理进行判断
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
//利用__get_col测量char a[row][col]型二维数组行数，建议指定列数
//使用方式：char a[row][col];  int len = __get_row(*a,...); 正常结果len==row
//注意：重要前提是a已完成初始化（将空余位置补成'\0'），如a[row][col]={""};
int __get_row(const char* a, int col = -1, int max_col = 100)
{
	if (col == -1)
		col = __get_col(a, max_col);
	int row = 0;
	while (_can_print(*(a + row * col)) == true)
	{
		row++;
	}
	return row;
}
//将const型字符串转成普通可变型字符串
//使用方式：char a[10] = "xxx";  char* res = const_to_var(a);
char* const_to_var(const char* data)
{
	int len = strlen(data);
	char* res = new char[len + 1];
	int i;
	for (i = 0; i < len; i++)
	{
		res[i] = data[i];
	}
	res[i] = '\0';
	return res;
}
//将const型row行col列的字符串数组转成普通可变型字符串数组
//使用方式：char a[4][20]={"a","a","1","1"};  char** res = const_to_var_2(*a, 4, 20);
char** const_to_var_2(const char* data, int row = -1, int col = -1, int max_col = 100)
{
	if (col == -1)
		col = __get_col(data, max_col);
	if (row == -1)
		row = __get_row(data, col);
	char** res = new char* [row];
	for (int i = 0; i < row; i++)
	{
		res[i] = new char[col];
		if (*(data + i * col) == '\0')
			res[i][0] = '\0';
		else strcpy(res[i], data + i * col);
	}
	return res;
}

void show_char(char a, char seq = '\0')
{
	printf("%c%c", a, seq);
}
void show_bool(bool a, char seq = '\0')
{
	if(a==true)
		printf("true%c", seq);
	else printf("false%c", seq);
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
//将列数小于max_col（默认为200）的二维字符串数组（每行为一个字符串）的所有行展示，每行字符串展示的间隔符为word_seq（默认为空格），同字符串各字符间隔符为letter_seq（默认为空）
//传入方式：char a[n][m]; show_string_2(*a,...)
void show_string_2(const char*p, char word_seq = ' ', char letter_seq = '\0', int max_col = 200)
{
	int col = __get_col(p, max_col);
	show_string_2(p, col, word_seq, letter_seq);
}
//展示二维字符串数组（每行为一个字符串）的前row行，默认全部内容，每个字符串间隔符为word_seq，默认为空格
//传入方式：char** a; show_string_2(a,...)
void show_string_2(char** p, int row = INT_MAX, char word_seq = ' ')
{
	if (p == NULL)
	{
		printf("%s输入数组为NULL\n", __func__);
		return;
	}
	int i = 0;
	for (;i < row; i++)
	{
		if (row != INT_MAX && !_can_print(p[i][0]))
		{
			printf("空字符串%c", word_seq);
		}
		else
		{
			if (!_can_print(p[i][0]))
				break;
			printf("%s%c", p[i], word_seq);
		}
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

//生成长度为length的随机字符串，元素ASCII码取值min-max，unique控制是否可以出现重复字符（默认为可以false）
//'0-9'=48-57  'A-Z'=65-90  'a-z'=97-122
//使用方式：char* res = random_string(...);
char* random_string(int length, int min = 97, int max = 122,bool unique=false)
{
	char* res = new char[length + 1];
	res[length] = '\0';
	int* random_seq;
	if (unique == false) random_seq = random_int_seq(length, min, max);
	else random_seq = random_int_seq_unique(length, min, max);
	for (int i = 0; i < length; i++)
	{
		res[i] = char(random_seq[i]);
	}
	return res;
}

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
	printf("%s请输入字符串：", __func__);
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
	printf("%s请输入字符串：", __func__);
	while ((ch = getchar()) != end_char)
	{
		res[i] = ch;
		i++;
	}
	res[i] = '\0';
	return i;
}
//输入num行字符串，每行结束符为end_char（默认为回车），每行输入字符串长度最大为max_length（默认为256）
//使用方式：char **str = cin_string(...);
char** cin_string(int num, char end_char = '\n', int max_length = 256)
{
	char** res = new char* [num];
	int res_index = 0;
	printf("%s需输入%d行\n", __func__, num);
	printf("（第1行）");
	for (int i = 0; i < num; i++)
	{
		res[i] = cin_string(end_char, max_length);
		if (i == num - 1)
			break;
		printf("（第%d行）",i + 2);
	}
	return res;
}
//输入多行字符串，每行结束符为end_row（默认为回车），每行输入字符串长度最大为max_word_length（默认为256）；
//当输入end_cin时结束输入（默认为over），返回已输入的行数（不包括end_cin），最多输入max_row行（默认为10）
//使用方式：char** res = new char* [max_row];  int len = cin_string(res,...);
int cin_string(char** res, char end_row = '\n', const char* end_cin = "over", int max_word_length = 256, int max_row = 10) 
{
	char* row = new char[max_word_length];
	int res_index = 0;
	printf("%s结束符为%s\n", __func__, end_cin);
	printf("（第%d行）", res_index + 1);
	while (1)
	{
		cin_string(row, end_row);
		if (strcmp(row, end_cin) == 0 || res_index >= max_row) 
			break;
		res[res_index] = new char[max_word_length];
		strcpy(res[res_index], row);
		res_index++;
		if (res_index >= max_row)
			break;
		printf("（第%d行）", res_index + 1);
	}
	delete[] row;
	return res_index;
}

//将字符串转为小写，返回新串，不改变原串
//使用方式：char* res = str_toLower(str);
char* str_toLower(const char* str)
{
	int len = strlen(str) + 1;
	char* res = new char[len];
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		res[i] = char(tolower(str[i]));
	}
	res[i] = '\0';
	return res;
}
//将字符串转为大写，返回新串，不改变原串
//使用方式：char* res = str_toUpper(str);
char* str_toUpper(const char* str)
{
	int len = strlen(str) + 1;
	char* res = new char[len];
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		res[i] = char(toupper(str[i]));
	}
	res[i] = '\0';
	return res;
}
//在data字符串中找substring子串，返回子串数量，将所有子串的索引（第一个匹配字符的索引）存在res数组中（可选），case_sensitive控制是否区分大小写（默认true区分）
//使用方式：int res[100]; int num = find_substring(data,substring,res,..);
int find_substring(const char* data, const char* substring, int* res = NULL, bool repeatly_find = true, bool case_sensitive = true)
{
	int data_len = strlen(data);
	int substring_len = strlen(substring);
	if (data_len == 0 || substring_len == 0 || substring_len > data_len)
	{
		printf("%s输入数据有误\n", __func__);
		res = NULL;
		return -1;
	}
	if (case_sensitive == false) //若忽略大小写就将字符串都转为小写
	{
		data = str_toLower(data); //const char* 类型不能改变指针指向的数据，但能改变指针的指向（并且根据前面推断，这个改变只在函数中起作用，不会改变原指针）
		substring = str_toLower(substring);
	}
	int count = 0;
	//思路：源字符串第一个字符下创建一个指针p1；若p1指向的字符与子串的第一个字符不相等,p1向后走;当相等时，源字符串从该位置创建一个临时指针p3,目标字符串从头部创建一个临时指针p4；
	//p3,p4向后移动，直至p4等于'\0',查找成功;否则该字符串不匹配；退出临时指针，p1,p2继续向后走，如此循环直到源字符串走完。
	int p1 = 0;
	while (p1 <= data_len - substring_len) //最后一个可能的索引为data_len - substring_len，之后的原串长度将小于子串长，不可能有子串
	{
		if (data[p1] == substring[0])
		{
			int p3 = p1 + 1, p4 = 1, flag = 1; //此处作了简化，因为data[p1] == substring[0]已判断，所以从p1和0的下一位开始
			while (substring[p4] != '\0') //因为前面作了限定，不可能出现data[p3]取不到的情况
			{
				if (data[p3] != substring[p4])
				{
					flag = 0;
					break;
				}
				p3++;
				p4++;
			}
			if (flag == 1)
			{
				if (res != NULL) res[count] = p1;
				count++;
			}
		}
		if (repeatly_find == false) p1 += substring_len;
		else p1++;
	}
	return count;
}
//KMP算法中求next数组，next[i]=j含义为：下标为i的字符前的字符串最长相等前后缀的长度为j
int* _get_next(const char* data)
{
	int len = strlen(data);
	int* res = new int[len];
	int j = 0; //j表明当前已匹配的字符串长度
	int k = -1; //k指向当前已匹配字符串中最长相等前缀的后一个字符
	res[0] = -1; //第一个字符前无字符串，给值-1
	while (j < len - 1)//因为next数组中j最大为t.length-1,而每一步next数组赋值都是在j++之后，所以最后一次经过while循环时j为t.length-2
	{
		if (k == -1 || data[j] == data[k])
		{
			j++;
			k++;
			res[j] = k;
		}
		else
		{
			k = res[k];
		}
	}
	return res;
}
//KMP算法改进版中求nextval数组，nextval[i]=j含义为：下标为i的字符前的字符串最长相等前后缀的长度为j
int* _get_nextval(const char* data)
{
	int len = strlen(data);
	int* res = new int[len];
	int j = 0; //j表明当前已匹配的字符串长度
	int k = -1; //k指向当前已匹配字符串中最长相等前缀的后一个字符
	res[0] = -1; //第一个字符前无字符串，给值-1
	while (j < len)
	{
		if (k == -1 || data[j] == data[k])
		{
			j++;
			k++;
			if (data[j] != data[k])
				res[j] = k;
			else
				res[j] = res[k];
		}
		else
		{
			k = res[k];
		}
	}
	return res;
}
//KMP算法：使用next数组在data字符串中找substring子串
int _find_substring_byKMP(const char* data, const char* substring, int* next, int* res = NULL, bool repeatly_find = true, bool case_sensitive = true)
{
	int data_len = strlen(data), substring_len = strlen(substring);
	if (data_len == 0 || substring_len == 0 || substring_len > data_len)
	{
		printf("%s输入数据有误\n", __func__);
		res = NULL;
		return -1;
	}
	if (case_sensitive == false)
	{
		data = str_toLower(data); 
		substring = str_toLower(substring);
	}
	int i = 0, j = 0;
	int count = 0;
	while (i < data_len)
	{
		j = 0;
		while (j < substring_len)
		{
			if (i == data_len) break;
			if (j == -1 || data[i] == substring[j])
			{
				i++;
				j++;
			}
			else j = next[j];
		}
		if (j >= substring_len)
		{
			if (res != NULL) res[count] = i - substring_len;
			if(repeatly_find == true) i = i - substring_len + 1;
			count++;
		}
	}
	return count;
}
//使用KMP算法在data字符串中找substring子串，返回子串数量，将所有子串的索引（第一个匹配字符的索引）存在res数组中（可选）
//repeatly_find控制是否重复查找，默认为true（"aaaa"中查找"aa"，若是true就是找到3个，索引为012；false就找到2个，索引为02）；case_sensitive控制是否区分大小写（默认true区分）
//使用方式：int res[100]; int num = find_substring(data,substring,res,..);
int find_substring_byKMP(const char* data, const char* substring, int* res = NULL, bool repeatly_find = true, bool case_sensitive = true)
{
	int* next = _get_next(substring);
	return _find_substring_byKMP(data, substring, next, res, repeatly_find, case_sensitive);
}
//使用KMP算法的改进版在data字符串中找substring子串，返回子串数量，将所有子串的索引（第一个匹配字符的索引）存在res数组中（可选）
//repeatly_find控制是否重复查找，默认为true（"aaaa"中查找"aa"，若是true就是找到3个，索引为012；false就找到2个，索引为02）；case_sensitive控制是否区分大小写（默认true区分）
//使用方式：int res[100]; int num = find_substring(data,substring,res,..);
int find_substring_byKMPimprove(const char* data, const char* substring, int* res = NULL, bool repeatly_find = true, bool case_sensitive = true)
{
	int* nextval = _get_nextval(substring);
	return _find_substring_byKMP(data, substring, nextval, res, repeatly_find, case_sensitive);
}

//交换data字符串索引为i和j的两个字符
void swap_char(char* data, int i, int j)
{
	char temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}
//交换data二维字符串数组索引为i和j的行，每行字符串长度不超过max_length（默认为256）
void swap_string(char** data, int i, int j, int max_length = 256)
{
	char* temp = new char[max_length];
	strcpy(temp, data[i]);
	strcpy(data[i], data[j]);
	strcpy(data[j], temp);
	delete[] temp;
}
//将data字符串倒序
void reverse(char* data)
{
	int len = strlen(data);
	for (int i = 0; i < len / 2; i++)
	{
		swap_char(data, i, len - i - 1);
	}
}
//将data二维字符串数组倒序（以行为单位）
void reverse(char** data, int row, int max_length = 256)
{
	for (int i = 0; i < row / 2; i++)
	{
		swap_string(data, i, row - i - 1, max_length);
	}
}

//按data二维字符串数组每行的长度排序，默认从小到大
void sort_byLength(char** data, int row, bool largeToSmall = false)
{
	int* length = new int[row];
	for (int i = 0; i < row; i++)
		length[i] = strlen(data[i]);
	for (int i = 0; i < row - 1; i++)
	{
		for (int j = 0; j < row - 1 - i; j++)
		{
			if (largeToSmall == false)
			{
				if (length[j] > length[j + 1])
				{
					swap_2_int(length, j, j + 1);
					swap_string(data, j, j + 1);
				}
			}
			else 
			{
				if (length[j] < length[j + 1])
				{
					swap_2_int(length, j, j + 1);
					swap_string(data, j, j + 1);
				}
			}
		}
	}
}
//按data二维字符串数组每行的ASCII码排序，默认从小到大
void sort_byASCII(char** data, int row, bool largeToSmall = false)
{
	for (int i = 0; i < row - 1; i++)
	{
		for (int j = i + 1; j < row; j++)
		{
			if (largeToSmall == false)
			{
				if (strcmp(data[i], data[j]) > 0)
				{
					swap_string(data, i, j);
				}
			}
			else
			{
				if (strcmp(data[i], data[j]) < 0)
				{
					swap_string(data, i, j);
				}
			}
		}
	}
}
void _quick_sort_byLength(char** data, int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int first = low, last = high;
	char* key = new char[strlen(data[first]) + 1];
	strcpy(key, data[first]);
	int temp = first;
	while (first < last)
	{
		while (first < last && strlen(data[last]) >= strlen(key))
			--last;
		strcpy(data[temp], data[last]);
		temp = last;
		while (first < last && strlen(data[first]) <= strlen(key))
			++first;
		strcpy(data[temp], data[first]);
		temp = first;
	}
	strcpy(data[temp], key);
	_quick_sort_byLength(data, low, temp - 1);
	_quick_sort_byLength(data, temp + 1, high);
}
//按data二维字符串数组每行的长度排序，默认从小到大
void quick_sort_byLength(char** data, int row, bool largeToSmall = false)
{
	_quick_sort_byLength(data, 0, row - 1);
	if (largeToSmall)
		reverse(data, row);
}
void _quick_sort_byASCII(char** data, int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int first = low, last = high;
	char* key = new char[strlen(data[first]) + 1];
	strcpy(key, data[first]);
	int temp = first;
	while (first < last)
	{
		while (first < last && strcmp(data[last], key) >= 0)
			--last;
		strcpy(data[temp], data[last]);
		temp = last;
		while (first < last && strcmp(data[first], key) <= 0)
			++first;
		strcpy(data[temp], data[first]);
		temp = first;
	}
	strcpy(data[temp], key);
	_quick_sort_byASCII(data, low, temp - 1);
	_quick_sort_byASCII(data, temp + 1, high);
}
//按data二维字符串数组每行的ASCII码排序，默认从小到大
void quick_sort_byASCII(char** data, int row, bool largeToSmall = false)
{
	_quick_sort_byASCII(data, 0, row - 1);
	if (largeToSmall)
		reverse(data, row);
}
#endif