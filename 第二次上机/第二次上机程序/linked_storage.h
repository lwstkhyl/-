#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<iostream>
#include<queue>
#include<stack>
using std::stack;
using std::queue;
using std::cin;
using std::cout;
using std::endl;
typedef struct node {
	int data;
	struct node* lchild, * rchild;
} node;
typedef node* bitree;
bitree buildtree()
{
    int c;
    node* p;
    printf("输入节点：");
    cin >> c;
    if (c == 0) return NULL;
    p = new(node);
    p->data = c;
    p->lchild = buildtree();
    p->rchild = buildtree();
    return(p);
}
//先序遍历
void DLR(bitree root)
{
    if (!root)return;
    printf("%d ", root->data);
    DLR(root->lchild);
    DLR(root->rchild);
}
//中序遍历
void LDR(bitree root)
{
    if (!root)return;
    LDR(root->lchild);
    printf("%c ", root->data);
    LDR(root->rchild);
}
//后序遍历
void LRD(bitree root)
{
    if (!root)return;
    LRD(root->lchild);
    LRD(root->rchild);
    printf("%d ", root->data);
}
//镜像
bitree mirror(bitree root)
{
    if (root == NULL) return NULL; //空树无需镜像
    bitree left = mirror(root->lchild); //将该结点的左子树镜像
    bitree right = mirror(root->rchild); //将该结点的将右子树镜像
    root->lchild = right;
    root->rchild = left; //交换该结点的左右子树
    return root;
}
//求高度
int get_depth(bitree root)
{
    if (root == NULL) return 0; //空树高度为0
    int left_depth = get_depth(root->lchild); //递归求左子树高度
    int right_depth = get_depth(root->rchild); //递归求右子树高度
    int depth = 1 + (left_depth > right_depth ? left_depth : right_depth); //树的高度是根到叶子最长路径上的结点的数量
    return depth;
}
//根据前序遍历序列和中序遍历序列还原二叉树
bitree PreInCreate(int* pre, int p_start, int p_end, int* in, int i_start, int i_end)
{
    if (p_start == p_end) return NULL;
    int root_val = pre[p_start];
    bitree root = new node;
    root->data = root_val;
    int i_root_index = 0;
    for (int i = i_start; i < i_end; i++)
    {
        if (root_val == in[i])
        {
            i_root_index = i;
            break;
        }
    }
    int left_num = i_root_index - i_start;
    root->lchild = PreInCreate(pre, p_start + 1, p_start + left_num + 1, in, i_start, i_root_index);
    root->rchild = PreInCreate(pre, p_start + left_num + 1, p_end, in, i_root_index + 1, i_end);
    return root;
}
//分层遍历二叉树
void level_traversal(bitree root)
{
    if (root == NULL) return;
    queue<bitree> q;
    q.push(root);
    while (!q.empty())
    {
        bitree node = q.front();
        q.pop();
        cout << node->data << " ";
        if (node->lchild != NULL) q.push(node->lchild);
        if (node->rchild != NULL) q.push(node->rchild);
    }
    cout << endl;
}
//链式转顺序
void chain_to_order(bitree t, char x[], int i = 1)
{
    if (t)
    {
        x[i] = char(t->data + '0');
        chain_to_order(t->lchild, x, 2 * i);
        chain_to_order(t->rchild, x, 2 * i + 1);
    }
    else x[i] = '0';
}
//求二叉树的宽度
int get_width(bitree root)
{
    if (root == NULL) return 0; //检查根节点是否为空。如果为空,那么树的宽度就是0
    queue<bitree> q;
    q.push(root); //创建一个队列, 并将根节点加入队列。
    int max_width = 0; //最大宽度
    while (!q.empty())
    {
        int level_size = q.size(); //记录当前队列的大小,即当前层的节点数
        max_width = max_width > level_size ? max_width : level_size; //更新maxWidth
        for (int i = 0; i < level_size; i++)
        {
            bitree node = q.front();
            q.pop();
            if (node->lchild != NULL) q.push(node->lchild);
            if (node->rchild != NULL) q.push(node->rchild);
        } //遍历当前层的所有节点,将它们的左右子节点加入队列
    } //当队列为空时,循环结束,此时的maxWidth就是树的最大宽度
    return max_width;
}
//节点个数
int node_count(bitree root)
{
    if (root == NULL) return 0;
    return node_count(root->lchild) + node_count(root->rchild) + 1;
}
//第k层节点数
int node_num_k(bitree root, int k)
{
    if (root == NULL) return 0; //空树直接返回0
    if (k == 1) return 1; //k==1即求根节点的个数，直接返回1
    return node_num_k(root->lchild, k - 1) + node_num_k(root->rchild, k - 1);
}
//叶子节点数
int leaf_count(bitree root)
{
    if (root == NULL) return 0; //空树直接返回0
    if (root->lchild == NULL && root->rchild == NULL) return 1;
    return leaf_count(root->lchild) + leaf_count(root->rchild);
}
//判断两树结构是否相同
bool is_same(bitree t1, bitree t2)
{
    if (t1 == NULL && t2 == NULL) return true;
    else if (t1 == NULL || t2 == NULL) return false;
    else return is_same(t1->lchild, t2->lchild) && is_same(t1->rchild, t2->rchild);
}
//求两个节点的最低公共祖先结点
bitree common_ancestor(bitree root, bitree p, bitree q)
{
    if (root == NULL) return NULL;
    if (root == p || root == q) return root;
    bitree left = common_ancestor(root->lchild, p, q);
    bitree right = common_ancestor(root->rchild, p, q);
    //如果left和right都不空，意味着pq在不同的子树，结果为根节点
    if (left != NULL && right != NULL) return root;
    //如果只有left非空，意味着pq在相同的左子树
    if (left != NULL) return left;
    //如果只有right非空，意味着pq在相同的右子树
    if (right != NULL) return right;
    return NULL;
}
//非递归方法前序遍历
void DLR2(bitree root)
{
    stack<bitree> s;
    s.push(root); //先将头节点入栈
    while (!s.empty()) //栈不为空则继续
    {
        bitree front = s.top();
        s.pop();
        printf("%d", front->data);
        if (front->rchild) s.push(front->rchild); //先将右孩子入栈
        if (front->lchild) s.push(front->lchild); //再将左孩子入栈
    }
}
//非递归方法中序遍历
void LDR2(bitree root)
{
    stack<bitree> s;
    bitree front = root;
    while (!s.empty() || front)
    {
        while (front)
        {
            s.push(front); //节点不为空，就入栈
            front = front->lchild; //找左孩子
        }
        if (!s.empty())
        {
            front = s.top(); //若该节点左孩子为空，将其出栈，后找该节点右孩子
            s.pop();
            printf("%d", front->data);
            front = front->rchild; //后以同样的方法遍历右孩子
        }
    }
}
//非递归方法后序遍历
void LRD2(bitree root)
{
    stack<bitree> s;
    stack<bitree> ss; //创建两个栈ps，pss
    s.push(root);
    while (!s.empty())
    {
        bitree front = s.top();
        s.pop();
        ss.push(front); //将出栈元素放入新的栈中
        if (front->lchild) s.push(front->lchild); //先将左孩子入栈
        if (front->rchild) s.push(front->rchild); //再将右孩子入栈
    }
    while (!ss.empty())
    {
        bitree front = ss.top();
        ss.pop();
        printf("%d", front->data);
    }
}
void test()
{
    bitree t;
    t = buildtree();
    printf("先序遍历：");
    DLR(t);
    
}
/*
1
2
0
3
0
0
4
0
5
6
0
0
0
*/
/*
1
2
0
3
0
0
4
0
5
6
0
0
0
*/