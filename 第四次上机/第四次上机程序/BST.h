#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int ElementType;
typedef struct TNode* Position;
typedef Position BinTree; /* 二叉树类型 */
struct TNode { /* 树结点定义 */
	ElementType Data; /* 结点数据 */
	BinTree Left;     /* 指向左子树 */
	BinTree Right;    /* 指向右子树 */
};
//查找
Position Find(ElementType X, BinTree BST)
{
	if (!BST) return NULL; /*查找失败*/
	if (X > BST->Data)
		return Find(X, BST->Right); /*在右子树中继续查找*/
	else if (X < BST->Data)
		return Find(X, BST->Left); /*在左子树中继续查找*/
	else /* X == BST->Data */
		return BST; /*查找成功，返回结点的找到结点的地址*/
}
//查找最小元素
Position FindMin(BinTree BST)
{
	if (!BST)
		return NULL; /*空的二叉搜索树，返回NULL*/
	else if (!BST->Left)
		return BST; /*找到最左叶结点并返回*/
	else
		return FindMin(BST->Left); /*沿左分支继续查找*/
}
//查找最大元素
Position FindMax(BinTree BST)
{
	if (BST)
		while (BST->Right)  /*沿右分支继续查找，直到最右叶结点*/
			BST = BST->Right;
	return BST;
}
//插入
BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST) { /* 若原树为空，生成并返回一个结点的二叉搜索树 */
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else { /* 开始找要插入元素的位置 */
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);   /*递归插入左子树*/
		else  if (X > BST->Data)
			BST->Right = Insert(BST->Right, X); /*递归插入右子树*/
		/* else X已经存在，什么都不做 */
	}
	return BST;
}
//删除
BinTree Delete(BinTree BST, ElementType X)
{
	Position Tmp;
	if (!BST)
		printf("要删除的元素未找到");
	else {
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X);   /* 从左子树递归删除 */
		else if (X > BST->Data)
			BST->Right = Delete(BST->Right, X); /* 从右子树递归删除 */
		else
		{ /* BST就是要删除的结点 */
			/* 如果被删除结点有左右两个子结点 */
			if (BST->Left && BST->Right)
			{
				/* 从右子树中找最小的元素填充删除结点 */
				Tmp = FindMin(BST->Right);
				BST->Data = Tmp->Data;
				/* 从右子树中删除最小元素 */
				BST->Right = Delete(BST->Right, BST->Data);
			}
			else
			{ /* 被删除结点有一个或无子结点 */
				Tmp = BST;
				if (!BST->Left)       /* 只有右孩子或无子结点 */
					BST = BST->Right;
				else                   /* 只有左孩子 */
					BST = BST->Left;
				free(Tmp);
			}
		}
	}
	return BST;
}
void show_bst(BinTree t, int val)
{
	printf("\n最大元素为%d", FindMax(t)->Data);
	printf("\n最小元素为%d", FindMin(t)->Data);
	if (Find(val, t))
	{
		printf("\n找到了%d结点，它的左子结点为%d，右子结点为%d", val, Find(val, t)->Left->Data, Find(val, t)->Right->Data);
	}
	else
	{
		printf("\n未找到%d结点", val);
	}
}