#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include"linked_storage.h"
//使用一个字符型数组来存储二叉树，其中第一个元素x[0]标识数组长度，根节点为x[1]
//空元素使用0进行占位，左节点为x[2n]，右节点为x[2n+1]

//先序遍历
void DLR_seq(char x[], int n = 1)
{
    if (x[n] == '0' || n > x[0]) return;
    printf("%c ", x[n]);
    DLR_seq(x, 2 * n);
    DLR_seq(x, 2 * n + 1);
}
//中序遍历
void LDR_seq(char x[], int n)
{
    if (x[n] == '0' || n > x[0]) return;
    LDR_seq(x, 2 * n);
    printf("%c ", x[n]);
    LDR_seq(x, 2 * n + 1);
}
//后序遍历
void LRD_seq(char x[], int n)
{
    if (x[n] == '0' || n > x[0]) return;
    LRD_seq(x, 2 * n);
    LRD_seq(x, 2 * n + 1);
    printf("%c ", x[n]);
}
//层序遍历
void level_traversal_seq(char x[])
{
    for (int i = 1; i <= x[0]; i++)
    {
        if (x[i] != '0')
            printf("%c", x[i]);
    }
    printf("\n");
}
//遍历输出
void foreach_tree_seq(char x[], char seq = ' ')
{
    for (int i = 1; i <= x[0]; i++)
    {
        printf("%c%c", x[i], seq);
    }
    printf("\n");
}
//交换两个整数的值
void swap(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}
//镜像
void mirror_seq(char x[], int index = 1)
{
    if (index >= x[0]) return;
   // if (2 * index > x[0] || 2 * index + 1 > x[0]) return;
    mirror_seq(x, 2 * index);
    mirror_seq(x, 2 * index + 1);
    swap(x[2 * index], x[2 * index + 1]); //交换左右节点的值
}
//求深度
int get_depth_seq(char x[], int index = 1)
{
    if (index > x[0] || x[index] == 0) return 0;
    int left_depth = get_depth_seq(x, 2 * index);
    int right_depth = get_depth_seq(x, 2 * index + 1);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}
//转为链式存储
bitree order_to_chain(char x[], int index = 1)
{
    if (index > x[0] || x[index] == 0) return NULL;
    bitree root = new node;
    root->data = x[index] - '0';
    root->lchild = order_to_chain(x, 2 * index);
    root->rchild = order_to_chain(x, 2 * index + 1);
    return root;
}
//求宽度
int get_width_seq(char x[])
{
    int depth = get_depth_seq(x); //高度
    int max_width = 0;
    for (int i = 1; i <= depth; i++)
    {
        int width=0;
        for (int j = pow(2, i - 1); j < pow(2, i); j++)
            if (x[j] != '0') width++;
        if (width > max_width) max_width = width;
    }
    return max_width;
}
//节点个数
int get_node_num_seq(char x[])
{
    int count = 0;
    for (int i = 1; i <= x[0]; i++)
    {
        if (x[i] != '0') count++;
    }
    return count;
}
//k层节点个数
int get_k_num_seq(char x[], int i)
{
    int count = 0;
    for (int j = pow(2, i - 1); j < pow(2, i); j++)
    {
        if (x[j] != '0') count++;
    }
    return count;
}
//叶子节点数
int get_leaf_num_seq(char x[])
{
    int count = 0;
    int size = x[0];
    for (int i = 1; i <= size; i++)
    {
        if (x[i] != '0' && (2 * i > size || x[2 * i] == '0') && (2 * i + 1 > size || x[2 * i + 1] == '0'))
            count++;
    }
    return count;
}
//判断结构是否相同
bool is_same_seq(char x1[], char x2[])
{
    if (x1[0] != x2[0]) return false; //节点数不同，结构不同
    for (int i = 1; i <= x1[0]; i++)
    {
        if ((x1[i] != '0' && x2[i] == '0') || (x1[i] == '0' && x2[i] != '0'))
        {
            return false;
        }
    }
    return true;
}
//求两个节点的最低公共祖先结点，返回它的索引
int common_ancestor_seq(char x[], int p, int q, int root = 1)
{
    if (root >= x[0] || x[root] == '0') return 0;
    if (root == p || root == q) return root;
    int left = common_ancestor_seq(x, p, q, 2 * root);
    int right = common_ancestor_seq(x, p, q, 2 * root + 1);
    //如果left和right都不空，意味着pq在不同的子树，结果为根节点
    if (left != 0 && right != 0) return root;
    //如果只有left非空，意味着pq在相同的左子树
    if (left != 0) return left;
    //如果只有right非空，意味着pq在相同的右子树
    if (right != 0) return right;
    return 0;
}
//非递归方法前序遍历
void DLR2_seq(char x[])
{
    stack<int> s;
    s.push(1); //先将头节点入栈
    while (!s.empty()) //栈不为空则继续
    {
        int front = s.top();
        s.pop();
        printf("%c", x[front]);
        if (2 * front + 1 <= x[0] && x[2 * front + 1] != '0') s.push(2 * front + 1); //先将右孩子入栈
        if (2 * front <= x[0] && x[2 * front] != '0') s.push(2 * front); //再将左孩子入栈
    }
}
//非递归方法中序遍历
void LDR2_seq(char x[])
{
    stack<int> s;
    int front = 1;
    while (!s.empty() || (front <= x[0] && x[front] != '0'))
    {
        while (front <= x[0] && x[front] != '0')
        {
            s.push(front); //节点不为空，就入栈
            front = 2 * front; //找左孩子
        }
        if (!s.empty())
        {
            front = s.top(); //若该节点左孩子为空，将其出栈，后找该节点右孩子
            s.pop();
            printf("%c", x[front]);
            front = 2 * front + 1; //后以同样的方法遍历右孩子
        }
    }
}
//非递归方法后序遍历
void LRD2_seq(char x[])
{
    stack<int> s;
    stack<int> ss; //创建两个栈ps，pss
    s.push(1);
    while (!s.empty())
    {
        int front = s.top();
        s.pop();
        ss.push(front); //将出栈元素放入新的栈中
        if (2 * front <= x[0] && x[2 * front] != '0') s.push(2 * front); //先将左孩子入栈
        if (2 * front + 1 <= x[0] && x[2 * front + 1] != '0') s.push(2 * front + 1); //再将右孩子入栈
    }
    while (!ss.empty())
    {
        int front = ss.top();
        ss.pop();
        printf("%c", x[front]);
    }
}

void test_seq()
{
    int len;
    printf("输入数组长度：");
    cin >> len; 
    char* tree = new char[len + 1];
    tree[0] = len; 
    for (int i = 1; i <= len; i++)
    {
        printf("输入第%d个数：", i);
        cin >> tree[i];
    }
    printf("层序遍历：");
    level_traversal_seq(tree);
}

/*
15
1
2
3
0
4
5
0
0
0
6
0
0
7
0
0
*/
/*
7
1
2
3
0
4
5
0
*/
/*
13
1
2
3
0
4
5
0
0
0
6
0
0
7
*/
/*
7
1
2
3
0
0
5
0
*/