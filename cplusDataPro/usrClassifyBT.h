/**@file:     分类二叉树类的定义文件
  *@Author：  T.H.
  *@Version： V1.0
  *@Note:     这是一种比较特殊的二叉树，其特点：
              1）根结点的左子树小于根结点
			  2）根结点的右子树大于根结点
			  3）左右子树也是分类二叉树
	其中继承了二叉树的公用成员和方法，并重载了其中的所有非递归遍历方法
*/

#pragma once

#ifndef __CPLUS_USRCLASSIFYBT_H__
#define __CPLUS_USRCLASSIFYBT_H__

/** 引入文件----------------------------------------------------------------------*/
#include "usrBinaryTree.h"

/** 私有宏------------------------------------------------------------------------*/

/** 类定义------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE


//---------------------分类二叉树类定义-------------------------//
template<class dataType>
class usrClassifyBT:public usrBinaryTree<dataType>
{
private:
	DblNode<dataType> *classifyTreeRoot;  //分类二叉树根结点
	void deleteNode(DblNode<dataType> **tptr_TreeNode)
	{
		if (tptr_TreeNode){
			delete (*tptr_TreeNode); (*tptr_TreeNode) = nullptr; 
		}
	};

public:
	usrClassifyBT() :usrBinaryTree(), classifyTreeRoot(nullptr){};  //默认构造函数
	usrClassifyBT(const dataType &tdat);
	virtual ~usrClassifyBT(){};  //默认析构函数

	//-------------------分类二叉树的应用------------------//
	//查找数据，并将其所在的结点传回给tptr指针
	//若不存在，则将结束前的结点传回，因为此时的结点数据与tdat数值最相近
	//可以用于后续的数据插入
	bool searchDataClassifyBT(const dataType &tdat,DblNode<dataType> **tptr_TreeNode = nullptr);
	//bInsertMode -- 表示插入结点的模式
	//bInsertMode=1---允许插入相同数据结点(default) bInsertMode = 0---不允许
	bool insertNodeDat(const dataType &tdat, const bool bInsertMode = true);
	//删除数据有几种分类--->
	//1.当被删除节点是叶子结点时，直接删除就ok
	//2.当该结点是树根结点且只有一个孩子时
	//直接删除根结点，并将其孩子作为新的树根节点
	//3.结点非树根结点且只有一个孩子，移动其孩子结点
	//作为新的结点，然后删除该结点
	//4.若结点有两个孩子，则将左子树中最右边的结点（左子树中最大数据）
	//或是右子树最左边的结点（即右子树中最小数据）移动作为新的根结点
	bool deleteNodeDat(const dataType &tdat);

	//-------------------多态-------------------//
	//重载了二叉树基类的函数
	DblNode<dataType>* getTreeRoot()const override{ return classifyTreeRoot; }
	//DLR 前序遍历
	bool searchDataDLR_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1)override;
	//LDR 非递归中序遍历---这种遍历方法很有用处
	bool searchDataLDR_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1)override;
	//LRD 后序遍历
	bool searchDataLRD_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1)override;
	//UpToDn_LToR 从上至下，从左至右  层次遍历
	bool searchDataUpToDn_LToR(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1)override;
	
	void printTree()override;
};

//---------------------分类二叉树类实现-------------------------//
//---------私有方法实现--------//

//---------公有方法实现--------//
//构造函数
template<class dataType>usrClassifyBT<dataType>::
usrClassifyBT(const dataType &tdat)
{
	classifyTreeRoot = usrBinaryTree::creatBinaryTreeNode(tdat);
}

//查找数据，将*tptr_TreeNode设置为数据为tdat或是与tdat最近数据的结点
template<class dataType>bool usrClassifyBT<dataType>::
searchDataClassifyBT(const dataType &tdat,DblNode<dataType> **tptr_TreeNode)
{
	DblNode<dataType>* lptr_DblNode = getTreeRoot();
	while (lptr_DblNode)
	{
		if (tptr_TreeNode)   //若不为空，暂存前一个结点地址
			*tptr_TreeNode = lptr_DblNode;
		//nodeDat  tdat
		int retcmp = memcmp(&lptr_DblNode->nodeDat, &tdat, sizeof(dataType));
		if (retcmp > 0)
			lptr_DblNode = lptr_DblNode->ptrFront;
		else if (retcmp < 0)
			lptr_DblNode = lptr_DblNode->ptrNext;
		else
			return true;

	}
	return false;
}
template<class dataType>bool usrClassifyBT<dataType>::
insertNodeDat(const dataType &tdat, const bool bInsertMode)
{
	//判断是否存在该数据
	//若存在，则插入失败；否则新建结点，并插入
	DblNode<dataType> *lptr_curTreeNode = nullptr;
	//bInsertMode=false 表示不允许插入相同数据结点
	if (searchDataClassifyBT(tdat, &lptr_curTreeNode) && (!bInsertMode))
		return false;
	//创建结点
	DblNode<dataType>* lptr_DblNode = creatBinaryTreeNode(tdat);
	// nodeDat   tdat
	if (!lptr_curTreeNode)  //第一个结点数据
	{
		classifyTreeRoot = lptr_DblNode;
		lptr_DblNode = nullptr;   //重定向指针
		return true;
	}
	int retcmp = memcmp(&lptr_curTreeNode->nodeDat, &tdat, sizeof(dataType));
	if (retcmp>0)
		lptr_curTreeNode->ptrFront = lptr_DblNode; // nodeDat>tdat
	else
		lptr_curTreeNode->ptrNext = lptr_DblNode;  //nodeDat<=tdat
	return true;
}
//删除结点数据
//删除数据有几种分类--->
//1.当被删除节点是叶子结点时，直接删除就ok
//2.当该结点是树根结点且只有一个孩子时
//直接删除根结点，并将其孩子作为新的树根节点
//3.结点非树根结点且只有一个孩子，移动其孩子结点
//作为新的结点，然后删除该结点
//4.若结点有两个孩子，则将左子树中最右边的结点（左子树中最大数据）
//或是右子树最左边的结点（即右子树中最小数据）移动作为新的根结点
template<class dataType>bool usrClassifyBT<dataType>::
deleteNodeDat(const dataType &tdat)
{
	DblNode<dataType> *lptr_curTreeNode = classifyTreeRoot,
		*lptr_parentNode = nullptr,
		*lptr_sonNode = nullptr,//孩子结点
		*lptr_sonparentNode = nullptr;  //孩子的父结点
	int retcmp = memcmp(&lptr_curTreeNode->nodeDat, &tdat, sizeof(dataType));
	//查找数据，并找出其所在的父结点
	while (lptr_curTreeNode && \
		( (retcmp = memcmp(&lptr_curTreeNode->nodeDat, &tdat, sizeof(dataType)) ) != 0))
	{
		lptr_parentNode = lptr_curTreeNode;
		if (retcmp > 0)
			lptr_curTreeNode = lptr_curTreeNode->ptrFront;
		else
			lptr_curTreeNode = lptr_curTreeNode->ptrNext;
	}
	if (!lptr_curTreeNode)  //没有找到数据
		return false;
	if ((!lptr_curTreeNode->ptrFront) && (!lptr_curTreeNode->ptrNext))
	{
		//如果结点为情况1，直接删除结点
		deleteNode(&lptr_curTreeNode);
		return true;
	}
	//情况2、3
	if (lptr_curTreeNode->ptrFront && (!lptr_curTreeNode->ptrNext))  //只有左孩子
	{
		lptr_sonNode = lptr_curTreeNode->ptrFront;

	}
	else if ( ( !lptr_curTreeNode->ptrFront) && lptr_curTreeNode->ptrNext )  //只有右孩子
	{
		lptr_sonNode = lptr_curTreeNode->ptrNext;
	}
	if ( (lptr_curTreeNode == classifyTreeRoot) && lptr_sonNode )
	{
		classifyTreeRoot = lptr_sonNode;
		lptr_sonNode = nullptr;//断开连接
		deleteNode(&lptr_curTreeNode);//删除结点
		return true;
	}
	else if (lptr_sonNode)   //只有但孩子的一般结点，情况3
	{
		if (lptr_parentNode->ptrFront == lptr_curTreeNode)
			lptr_parentNode->ptrFront = lptr_sonNode;
		else
			lptr_parentNode->ptrNext = lptr_sonNode;
		lptr_sonNode = nullptr;//断开连接
		deleteNode(&lptr_curTreeNode);//删除结点
		return true;
	}
	//情况4--一般结点，两个孩子结点，将左子树中最大数作为新的根结点
	lptr_sonNode = lptr_curTreeNode->ptrFront;
	lptr_sonparentNode = lptr_curTreeNode;
	while (lptr_sonNode->ptrNext)
	{
		lptr_sonparentNode = lptr_sonNode;
		lptr_sonNode = lptr_sonNode->ptrNext;
	}
	lptr_curTreeNode->nodeDat = lptr_sonNode->nodeDat;  //移动结点
	//断开连接，这是必要的
	if (lptr_sonparentNode->ptrFront == lptr_sonNode)
		lptr_sonparentNode->ptrFront = nullptr;
	else
		lptr_sonparentNode->ptrNext = nullptr;
	deleteNode(&lptr_sonNode);//删除结点
	return true;

}

//--------------------------------多态------------------------------//
template<class dataType>void usrClassifyBT<dataType>::
printTree()  //二叉树的重载
{
	cout << "中序遍历结果---------->\n";
	searchDataLDR_Noiter(0, classifyTreeRoot, false);
}
//前序遍历
template<class dataType>bool usrClassifyBT<dataType>::
searchDataDLR_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	if (!tptr_TreeNode)
		lptr_DblNode = classifyTreeRoot;
	return usrBinaryTree::searchDataDLR_Noiter(tdat, lptr_DblNode, tbMode);
}
//中序遍历
template<class dataType>bool usrClassifyBT<dataType>::
searchDataLDR_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	if (!tptr_TreeNode)
		lptr_DblNode = classifyTreeRoot;
	return usrBinaryTree::searchDataLDR_Noiter(tdat, lptr_DblNode, tbMode);
}
//后续遍历
template<class dataType>bool usrClassifyBT<dataType>::
searchDataLRD_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	if (!tptr_TreeNode)
		lptr_DblNode = classifyTreeRoot;
	return usrBinaryTree::searchDataLRD_Noiter(tdat, lptr_DblNode, tbMode);
}
//UpToDn_LToR 从上至下，从左至右  层次遍历
template<class dataType>bool usrClassifyBT<dataType>::
searchDataUpToDn_LToR(const dataType &tdat,DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	if (!tptr_TreeNode)
		lptr_DblNode = classifyTreeRoot;
	return usrBinaryTree::searchDataUpToDn_LToR(tdat, lptr_DblNode, tbMode);
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

#endif //__CPLUS_USRCLASSIFYBT_H__
