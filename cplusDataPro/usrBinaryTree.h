/**@file:     二叉树类的定义文件
  *@Author：  T.H.
  *@Version： V1.2
  *@Note:     v1.0 --->searchDataByLDR() 使用的是递归进行遍历操作
			  v1.1 --->非递归遍历
	在这种通过根结点指向左右孩子这种结构中，非递归查找数据，前序遍历法，效率高
			  v1.2 --->添加层次遍历

  *@Attention：函数中想要更改指针数据，一定要用二维指针进行修改，
			  否则只是修改的形参而不是实参
			  ---->eg: fuc(int *tptr){ tptr=nullptr; }
			  在这儿并没有更改成功，需要使用二维指针
			  -->fuc(int **tptr){ *tptr=nullptr; }这样才能修改成功
*/

#pragma once

#ifndef __CPLUS_USRBINARYTREE_H__
#define __CPLUS_USRBINARYTREE_H__

/** 引入文件----------------------------------------------------------------------*/
#include "usrStack.h"   //用户堆栈类
#include <stack>        //系统堆栈类
#include <deque>
#include <iostream>
#include <string>

/** 私有宏------------------------------------------------------------------------*/
#if !defined EN_USR_STACK_CLASS
	#define EN_USR_STACK_CLASS       (1)      //使用用户堆栈类
#endif  //EN_USR_STACK_CLASS

#if EN_USR_STACK_CLASS
	#define macrobtStkTmp     usrStack
	#define macrobtDeqTmp     usrQueue
#else
	#define macrobtStkTmp     stack
	#define macrobtDeqTmp     deque
#endif //EN_USR_STACK_CLASS

#if !defined EN_NMSPACE_USR_DATASTRUCTURE
	#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE


/** 类定义------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//用于非递归遍历时的堆栈元素
template<class dataType>
class usrBTStkType
{
public:
	DblNode<dataType> *curptr;   //当成指针
	bool              status;
};

template<class dataType>
class usrBinaryTree
{
private:
	DblNode<dataType> *treeRoot;  //二叉树根结点
	//计算二叉树深度--递归
	int cntDeepth(DblNode<dataType> *tptr_TreeNode);
	//计算树结点数--递归
	int cntNumNode(DblNode<dataType> *tptr_TreeNode);
protected:
	//结点数据访问
	bool visitNode(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode = 1)
	{
		if (tbMode)
		{
			if (!memcmp(&tptr_TreeNode->nodeDat, &tdat, sizeof(dataType)))
				return true;
		}
		else
			cout << "结点数据：" << tptr_TreeNode->nodeDat << endl;
		return false;
	}

public:
	usrBinaryTree() :treeRoot(nullptr){};  //构造函数
	usrBinaryTree(const dataType &tdat);
	//析构函数，这儿使用虚析构函数
	//主要是避免析构对象不彻底
	virtual ~usrBinaryTree();  

	//---------------二叉树基本操作---------------//
	void connectTree(DblNode<dataType> *tptr_root, DblNode<dataType> *tptr_left, \
		DblNode<dataType> *tptr_right)
	{
		if (!treeRoot) treeRoot = tptr_root;
		tptr_root->ptrFront = tptr_left; tptr_root->ptrNext = tptr_right;
	}
	//生成树，返回生成的树结点地址
	DblNode<dataType>* creatBinaryTreeNode(const dataType &tdat);
	virtual void clrTree(DblNode<dataType> **tptr_TreeNode);  //清空二叉树
	int getDeepth();  //获取二叉树深度
	int getnumNode(); //获取二叉树结点数
	bool isEmpty();  //判断是否为空树，二叉树是可以为空树的
	virtual DblNode<dataType>* getTreeRoot()const{ return treeRoot; }  //返回根结点指针
	virtual void printTree();  //二叉树内容显示--LDR递归法

	//---------------二叉树遍历操作---------------//

	//二叉树的递归遍历操作进行查找数据，存在数据返回true
	virtual bool searchDataLDR(const dataType &tdat, DblNode<dataType> *tptr_TreeNode,bool tbMode = 1);
	
	//使用非递归法进行查找数据，tbMode为全部遍历还是只为了查找数据
	//tbMode=1--表示查找数据，tbMode=0--表示全部遍历，不管数据多少
	virtual bool searchDataDLR_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode=1);
	//LDR 非递归中序遍历---这种遍历方法很有用处
	virtual bool searchDataLDR_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1);
	//LRD 后序遍历
	virtual bool searchDataLRD_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1);
	//UpToDn_LToR 从上至下，从左至右  层次遍历
	virtual bool searchDataUpToDn_LToR(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1);
};

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//==========================================二叉树类的实现===========================================//

using namespace std;

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

/** 私有方法的实现---------------------------------------------------------*/

//计算二叉树深度
template<class dataType>int usrBinaryTree<dataType>::
cntDeepth(DblNode<dataType> *tptr_TreeNode)
{
	int l_deepth_front = 1, l_deepth_next = 1;
	if (tptr_TreeNode != nullptr)   //将根结点计算在内，所以需要l_deepth_front的初试值为1
	{
		l_deepth_front += cntDeepth(tptr_TreeNode->ptrFront);
		l_deepth_next += cntDeepth(tptr_TreeNode->ptrNext);
		return (l_deepth_front > l_deepth_next ? l_deepth_front : l_deepth_next);
	}
	return 0;
}
//计算树结点数
template<class dataType>int usrBinaryTree<dataType>::
cntNumNode(DblNode<dataType> *tptr_TreeNode)
{
	int lcnt_numNode = 0;
	if (!tptr_TreeNode)
		return 0;
	lcnt_numNode += cntNumNode(tptr_TreeNode->ptrFront);
	lcnt_numNode += cntNumNode(tptr_TreeNode->ptrNext);
	return ++lcnt_numNode;
}

/** 公有方法的实现---------------------------------------------------------*/
template<class dataType>usrBinaryTree<dataType>::
usrBinaryTree(const dataType &tdat)   //构造函数
{
	treeRoot = creatBinaryTreeNode(tdat);
}
template<class dataType>usrBinaryTree<dataType>::
~usrBinaryTree()   //析构函数
{
	clrTree(&treeRoot);
}
template<class dataType>DblNode<dataType>* usrBinaryTree<dataType>::
creatBinaryTreeNode(const dataType &tdat)  //生成树
{
	DblNode<dataType> *lptr_DblNode = new(DblNode<dataType>);  //生成结点
	if (!lptr_DblNode)
		return nullptr;
	memcpy(&lptr_DblNode->nodeDat, &tdat, sizeof(dataType));
	lptr_DblNode->ptrFront = nullptr;
	lptr_DblNode->ptrNext = nullptr;
	return lptr_DblNode;
}
//---------------------------二叉树基本操作---------------------------//
//清除整颗树，从树根结点开始删除
template<class dataType>void usrBinaryTree<dataType>::
clrTree(DblNode<dataType> **tptr_TreeNode)
{
	if (!(*tptr_TreeNode))  //主节点为空
		return;
	clrTree(&(*tptr_TreeNode)->ptrFront);
	clrTree(&(*tptr_TreeNode)->ptrNext);
	if ((!(*tptr_TreeNode)->ptrFront) && (!(*tptr_TreeNode)->ptrNext))  //左右树为空
	{
		if (*tptr_TreeNode == treeRoot)
		{
			treeRoot = nullptr;
		}
		delete (*tptr_TreeNode);  *tptr_TreeNode = nullptr;
	}
}
template<class dataType>int usrBinaryTree<dataType>::
getDeepth()  //获取二叉树深度
{
	return cntDeepth(treeRoot);
}
template<class dataType>int usrBinaryTree<dataType>::
getnumNode() //获取二叉树结点数
{
	return cntNumNode(treeRoot);
}
template<class dataType>bool usrBinaryTree<dataType>::
isEmpty()  //判断是否为空树
{
	return getnumNode() == 0;
}
//二叉树内容显示，采用LDR遍历显示
template<class dataType>void usrBinaryTree<dataType>::
printTree()
{
	searchDataLDR(0, treeRoot, 0);   //使用遍历函数进行打印数据
}

//---------------------------二叉树遍历操作----------------------------//
//中序遍历---递归操作
template<class dataType>bool usrBinaryTree<dataType>::
searchDataLDR(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	bool lb_flag = false;
	if (tptr_TreeNode != nullptr)
	{
		lb_flag = searchDataLDR(tdat, tptr_TreeNode->ptrFront, tbMode);  // 访问左子树
		if (visitNode(tdat, tptr_TreeNode, tbMode))
			return true;
		lb_flag |= searchDataLDR(tdat, tptr_TreeNode->ptrNext, tbMode);  // 访问右子树
	}
	return lb_flag;
}
//前序遍历---使用非递归法进行查找数据
//这种使用非递归的方法，查找数据时，在这种有根结点指向左右子树的结构中
//前序的效率比其他的要高，因为在其他的顺序中，同样需要先通过根结点，
//才能访问其他的分支
template<class dataType>bool usrBinaryTree<dataType>::
searchDataDLR_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	macrobtStkTmp<DblNode<dataType>*>lBtStk;   //创建临时堆栈
	if (!tptr_TreeNode)  //为空指针表示从treeRoot结点开始查找
		lptr_DblNode = treeRoot;
	while (lptr_DblNode || !lBtStk.isEmpty())
	{
		if (!lptr_DblNode)  //如果结点为空
		{
			lBtStk.pop(lptr_DblNode);  //退栈，将其重新指向右结点
			lptr_DblNode = lptr_DblNode->ptrNext;
		}
		else
		{
			lBtStk.push(lptr_DblNode);   //访问头指针
			if (visitNode(tdat, lptr_DblNode, tbMode))
				return true;
			lptr_DblNode = lptr_DblNode->ptrFront;  //指向左结点
		}
	}
	return false;
}
//中序遍历---非递归遍历
template<class dataType>bool usrBinaryTree<dataType>::
searchDataLDR_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	macrobtStkTmp<DblNode<dataType>*>lBtStk;   //创建临时堆栈
	if (!tptr_TreeNode)  //为空指针表示从treeRoot结点开始查找
		lptr_DblNode = treeRoot;
	while (lptr_DblNode || !lBtStk.isEmpty())
	{
		while (lptr_DblNode)   //找到最左边的结点
		{
			lBtStk.push(lptr_DblNode);
			lptr_DblNode = lptr_DblNode->ptrFront; //切换到左结点
		}
		if (!lBtStk.isEmpty())
		{
			lBtStk.pop(lptr_DblNode);  //弹出栈顶数据
			//访问数据
			if (visitNode(tdat, lptr_DblNode, tbMode))
				return true;
			lptr_DblNode = lptr_DblNode->ptrNext;  //指向右结点
		}
	}
	return false;
}
//LRD 后序遍历---因为后序遍历会经过两次根结点
//所以需要一个标志位用于判断结点访问次数,
//这里的usrBTStkType类 含有树结点与标志位属性
template<class dataType>bool usrBinaryTree<dataType>::
searchDataLRD_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	macrobtStkTmp<usrBTStkType<dataType>>lBtStk;   //创建临时堆栈
	usrBTStkType<dataType>lstkTmp;
	if (!tptr_TreeNode)  //为空指针表示从treeRoot结点开始查找
		lptr_DblNode = treeRoot;
	while (lptr_DblNode || !lBtStk.isEmpty())
	{
		//找到最左边的结点
		while (lptr_DblNode)
		{
			lstkTmp.curptr = lptr_DblNode;
			lstkTmp.status = false;
			lBtStk.push(lstkTmp);
			lptr_DblNode = lptr_DblNode->ptrFront;
		}
		//弹出数据，访问左边数据
		if (!lBtStk.isEmpty())
		{
			lBtStk.pop(lstkTmp);  //此时lstkTmp.curptr结点就是根结点
			lptr_DblNode = lstkTmp.curptr;   //装载结点指针
			//访问左结点数据
			if (lstkTmp.status)  //第二次访问
			{
				if (visitNode(tdat, lptr_DblNode, tbMode))
					return true;
				lptr_DblNode = nullptr;  //锁定当前结点
			}
			else  //第一次访问根结点
			{
				lstkTmp.status = true;
				lBtStk.push(lstkTmp);
				lptr_DblNode = lptr_DblNode->ptrNext;  //切换到右结点
			}
		}
	}
	return false;
}
//从上到下，从左至右的非递归遍历
//其中使用到了队列结构，使用队列存储访问到的根结点的左右孩子结点
template<class dataType>bool usrBinaryTree<dataType>::
searchDataUpToDn_LToR(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	macrobtDeqTmp<DblNode<dataType>*>lBtDeq;   //创建临时队列，用于存储结点
	if (!tptr_TreeNode)  //为空指针表示从treeRoot结点开始查找
		lptr_DblNode = treeRoot;
	while (1)  //队列为空，查找结束
	{
		//左右孩子进队
		if (lptr_DblNode->ptrFront)
			lBtDeq.enQueue(lptr_DblNode->ptrFront);  
		if (lptr_DblNode->ptrNext)
			lBtDeq.enQueue(lptr_DblNode->ptrNext);
		//访问结点数据
		if (visitNode(tdat, lptr_DblNode, tbMode))
			return true;
		if (!lBtDeq.isEmpty())
			lBtDeq.deQueue(lptr_DblNode);   //出队
		else
			break;
	}
	return false;
}


#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE


#endif //__CPLUS_USRBINARYTREE_H__

 