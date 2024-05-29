#pragma once
#include<iostream>
#include<list>
#include<queue>
#include<vector>
using std::list;
using std::queue;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
struct graph 
{
	int v; //顶点数
	list<int>* adj; //指向一个包含邻接表的数组的指针
public:
	graph(int);
	void add_edge(int, int); //添加边
	void print_graph();
	void BFS(int);
	void DFS(int, bool*);
	void topo_sort();
};
//初始化顶点的数量和邻接列表
graph::graph(int v)
{
	this->v = v;
	adj = new list<int>[v];
}
//为图添加一条边
void graph::add_edge(int v, int w )
{
	adj[v].push_back(w);
}
//打印图的邻接列表
void graph::print_graph()
{
	for (int i = 0; i < v; ++i)
	{
		cout << "顶点邻接表" << i << "：head";
		for (auto x : adj[i])
			cout << "->" << x;
		cout << endl;
	}
}
//BFS
void graph::BFS(int s)
{
	bool* visited = new bool[v]; //记录顶点的访问状态
	for (int i = 0; i < v; i++)
		visited[i] = false; //初始状态都为经过
	queue<int> q;
	visited[s] = true; //将当前节点标记为已访问
	q.push(s); //放入队列
	while (!q.empty())
	{
		s = q.front();
		cout << s << " ";
		q.pop(); //将队列中第一个元素输出并出栈
		//得到已打印点s的所有邻接点，如果某个邻接点没被方法就标记它并让它入队
		for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				q.push(*i);
				visited[*i] = true;
			}
		}
	}
}
//DFS
void graph::DFS(int s, bool* visited)
{
	visited[s] = true; //将当前节点标记为已访问
	cout << s << " "; //输出当前节点
	list<int>::iterator i;
	for (i = adj[s].begin(); i != adj[s].end(); i++)
		if (!visited[*i])
			DFS(*i, visited);
}
//拓扑排序
void graph::topo_sort()
{
	vector<int> in_degree(v + 1, 0);
	for (int u = 0; u < v; u++)
		for (auto i = adj[u].begin(); i != adj[u].end(); i++)
			in_degree[*i]++;
	queue<int> q;
	for (int i = 0; i < v; i++)
		if (in_degree[i] == 0)
			q.push(i);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		cout << u << " ";
		for (auto i = adj[u].begin(); i != adj[u].end(); i++)
		{
			--in_degree[*i];
			if (in_degree[*i] == 0)
				q.push(*i);
		}
	}
}