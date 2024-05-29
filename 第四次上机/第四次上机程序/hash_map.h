#pragma once
#include<iostream>
#include<unordered_map>
using std::unordered_map;
using std::cout;
using std::endl;
using std::cin;
using std::string;
//向表中插入数据
void hash_insert(unordered_map<string,int> &hash_table)
{
	string key;
	int val;
	while (1)
	{
		cout << "请输入key：";
		cin >> key;
		if(hash_table.find(key) == hash_table.end()) //如果该key不存在就可以进行插入
			break; 
		else cout << key << "已存在" << endl;
	}
	cout << "请输入val：";
	cin >> val;
	hash_table[key] = val;
}
//删除key
void hash_delete(unordered_map<string, int>& hash_table, string key)
{
	if (hash_table.find(key) == hash_table.end())
	{
		cout << key << "不存在" << endl;
		return;
	}
	hash_table.erase(key);
}
//将key的值修改为val
void hash_change(unordered_map<string, int>& hash_table, string key, int val)
{
	if (hash_table.find(key) == hash_table.end())
	{
		cout << key << "不存在" << endl;
		return;
	}
	hash_table[key] = val;
}
//输出h中的数据
void hash_show(unordered_map<string, int>& hash_table)
{
	for(auto i:hash_table)
		cout << i.first << ":" << i.second << "       ";
	cout << endl;
}