/**@File:     分类二叉树类的定义文件
  *@Author：  T.H.
  *@Version： V1.1
  *@Note:     这是一种比较特殊的二叉树，其特点：
              1）根结点的左子树小于根结点
			  2）根结点的右子树大于根结点
			  3）左右子树也是分类二叉树
	其中继承了二叉树的公用成员和方法，并重载了其中的所有非递归遍历方法

	2019-6-24:将usrClassifyBT 更改为虚继承 usrBinaryTree

	Update: 添加AVL树--平衡二叉树(添加平衡算法的分类二叉树)

*/

#pragma once

#ifndef __CPLUS_USRCLASSIFYBT_H__
#define __CPLUS_USRCLASSIFYBT_H__

/** 引入文件----------------------------------------------------------------------*/
#include "usrBinaryTree.h"

/** 私有宏------------------------------------------------------------------------*/
#if !defined MIN
#define MIN(x,y)      ((x)>(y)?(y):(x))
#endif
#if !defined MAX
#define MAX(x,y)      ((x)>(y)?(x):(y))
#endif
#if !defined ABS
#define ABS(x)      ((x)>0?(x):(-x))
#endif
/** 类定义------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//-----------------------------------分类二叉树类定义-------------------------------------------//
template<class dataType>
class usrClassifyBT:virtual public usrBinaryTree<dataType>
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

//-----------------------------------分类二叉树类实现-------------------------------------------//
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

//-----------------------------------平衡二叉树类定义-------------------------------------------//

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//定义平衡因子枚举类
//enum class BALANCE_FACTOR:int{};
#define LH_RL					(1)  //左高右低
#define RH_LL					(-1) //左低右高
#define R_EQ_L					(0)  //左右高低一致

//AVL树节点定义
template<typename dataType>
class AVLNode
{
public:
	int bf;  //平衡因子
	dataType nodeDat;  //数据域
	AVLNode *Lchild, *Rchild;    //左右孩子结点

	AVLNode(const dataType &tdat) :nodeDat(tdat),bf(0), Lchild(nullptr), Rchild(nullptr) {};
};
template<typename dataType>
class usrAVLTree
{
private:
	AVLNode<dataType>   *avlTreeRoot;

protected:
	void avlR_Rotation(AVLNode<dataType>* (&tptr));    //对tptr为根结点作右旋处理
	void avlL_Rotation(AVLNode<dataType>* (&tptr));       //对tptr为根结点作左旋处理
	void avlR_Rotate_Balance(AVLNode<dataType>* (&tptr)); //右旋平衡处理
	void avlL_Rotate_Balance(AVLNode<dataType>* (&tptr)); //左旋平衡处理

public:
	usrAVLTree() :avlTreeRoot(nullptr){};
	bool searchDataAVL(const dataType & tdat, AVLNode<dataType>*(&tptr));
	bool insertAVLNode(const dataType tdat);
	int avlUpdateBF(AVLNode<dataType>* (&tPtr));
	void avlUpdateBalance(AVLNode<dataType>* (&tPtr),bool &chg);
	int avlUpdate(AVLNode<dataType>*(&tPtr));
};

//-----------------------------------平衡二叉树类实现-------------------------------------------//
template<typename dataType>void usrAVLTree<dataType>::avlR_Rotation(AVLNode<dataType>* (&tptr))
{
	//右旋，不做bf平衡因子处理
	if (!tptr) return;
	AVLNode<dataType> *lptr = tptr->Lchild;
	tptr->Lchild = lptr->Rchild;
	lptr->Rchild = tptr;
	tptr = lptr;
}
template<typename dataType>void usrAVLTree<dataType>::avlL_Rotation(AVLNode<dataType>* (&tptr))
{
	//左旋，不做bf平衡因子处理
	if (!tptr) return;
	AVLNode<dataType>* lptr = tptr->Rchild;
	tptr->Rchild = lptr->Lchild;
	lptr->Lchild = tptr;
	tptr = lptr;
}
//右旋平衡处理（左孩子高度较右孩子高），并更新bf平衡因子，包含了先左再右双向旋转
//详细的 bf 变化，可以根据画图计算，或是数据结构书 P343 的图解
template<typename dataType>void usrAVLTree<dataType>::avlR_Rotate_Balance(AVLNode<dataType>* (&tptr))
{
	if (!tptr) return;
	if (tptr->bf <= 1 && tptr->bf >= -1) return;  //已经平衡不需要旋转
	AVLNode<dataType> *lptr = tptr->Lchild,*tmp = nullptr;
	switch (lptr->bf)
	{
	case 1:   //左孩子是平衡二叉树，此时只需要对根结点进行一次右旋即可
		//修改平衡因子，只需要更新有重新调节指针指向的结点bf即可
		lptr->bf = 0;
		tptr->bf = 0;
		avlR_Rotation(tptr);
		break;
	//case 2:
	//	//做一次右旋即可
	//	lptr->bf = 0; tptr->bf = -1;
	//	avlR_Rotation(tptr); break;
	case -1:
		//需要进行先左后右双向旋转
		tmp = lptr->Rchild;
		switch (tmp->bf)
		{
		case 0:  //这种情况是 tmp 是叶子结点
			lptr->bf = 0; tptr->bf = 0; break;
		case 1:  //做一次左旋即可
			//更新bf
			lptr->bf = 0;tptr->bf = -1;	break;
		case -1: 
			//左旋，更新bf
			lptr->bf = 0;tptr->bf = 0;break;
		}
		tmp->bf = 0;
		avlL_Rotation(lptr);
		tptr->Lchild = lptr; //更新结点
		avlR_Rotation(tptr);//再右旋
		break;
	}
}
//左旋平衡处理（右孩子较左孩子高）---与右旋平衡类似
template<typename dataType>void usrAVLTree<dataType>::avlL_Rotate_Balance(AVLNode<dataType>* (&tptr))
{
	if (!tptr) return;
	if (tptr->bf <= 1 || tptr->bf >= -1) return;  //已经平衡不需要旋转
	AVLNode<dataType> *lptr = tptr->Rchild, *tmp = nullptr;
	switch (lptr->bf)
	{
	case -1:   //右孩子是平衡二叉树，此时只需要对根结点进行一次左旋即可
			  //修改平衡因子，只需要更新有重新调节指针指向的结点bf即可
		lptr->bf = 0;
		tptr->bf = 0;
		avlL_Rotation(tptr);
		break;
	//case -2: //做一次左旋
	//	tptr->bf = 1; lptr->bf = 0;
	//	avlL_Rotation(tptr); break;
	case 1:
		//需要进行先右后左双向旋转
		tmp = lptr->Lchild;
		switch (tmp->bf)
		{
		case 0:  //这种情况是 tmp 是叶子结点
			lptr->bf = 0; tptr->bf = 0; break;
		case 1: //做一次右旋即可更新bf
			lptr->bf = -1; tptr->bf = 0;break;
		case -1://右旋，更新bf
			lptr->bf = 0; tptr->bf = 1;break;
		}
		tmp->bf = 0;
		avlR_Rotation(lptr);
		tptr->Rchild = lptr;//更新结点
		avlL_Rotation(tptr);//再左旋
		break;
	}
}
//查找数据，将*tptr_TreeNode设置为数据为tdat或是与tdat最近数据的结点
template<typename dataType>bool usrAVLTree<dataType>::
searchDataAVL(const dataType &tdat, AVLNode<dataType> *(&tptr))
{
	AVLNode<dataType> *lPtr = avlTreeRoot;
	while (lPtr)
	{
		//if (tptr)   //若不为空，暂存前一个结点地址
		tptr = lPtr;
		//nodeDat  tdat
		int retcmp = memcmp(&lPtr->nodeDat, &tdat, sizeof(dataType));
		if (retcmp > 0)
			lPtr = lPtr->Lchild;
		else if (retcmp < 0)
			lPtr = lPtr->Rchild;
		else
			return true;
	}
	return false;
}
template<typename dataType>bool usrAVLTree<dataType>::insertAVLNode(const dataType tdat)
{
	if (!avlTreeRoot)
	{
		avlTreeRoot = new AVLNode<dataType>(tdat); return true;
	}
	AVLNode<dataType> *lptr = new AVLNode<dataType>(tdat),
		*tmpPtr = nullptr;
	if (searchDataAVL(tdat, tmpPtr)) //树中已经存在该节点
		return false;
	//nodeData tdat
	int retcmp = memcmp(&tmpPtr->nodeDat, &tdat, sizeof(dataType));
	if (retcmp>0)  //在左边插入
		tmpPtr->Lchild = lptr;
	else   //在右边插入
		tmpPtr->Rchild = lptr;
	//avlUpdateBF(avlTreeRoot);  //更新 bf 
	//avlUpdateBalance(avlTreeRoot);  //平衡
	avlUpdate(avlTreeRoot);
	lptr = nullptr;
	return true;
}
//更新 bf
template<typename dataType>int usrAVLTree<dataType>::avlUpdateBF(AVLNode<dataType>* (&tPtr))
{
	//更新 平衡因子 就是求树的左右孩子高度差
	//使用迭代实现
	//AVLNode<dataType> *lPtr = avlTreeRoot;
	if (!tPtr)return 0;
	int L_length = 0, R_length = 0;
	L_length += avlUpdateBF(tPtr->Lchild);
	R_length += avlUpdateBF(tPtr->Rchild);
	tPtr->bf = L_length - R_length;
	return L_length > R_length ? L_length : R_length;
}
//调节平衡
template<typename dataType>void usrAVLTree<dataType>::avlUpdateBalance(AVLNode<dataType>* (&tPtr),bool &chg)
{
	switch (tPtr->bf)
	{
	case 1:
	case 0:
	case -1: chg = false; break;
	case 2:  //右旋平衡
		chg = true; avlR_Rotate_Balance(tPtr); break;
	case -2: //左旋平衡
		chg = true; avlL_Rotate_Balance(tPtr); break;
	}
}
//AVL树更新算法----包含 更新bf 与 调节平衡

template<typename dataType>int usrAVLTree<dataType>::avlUpdate(AVLNode<dataType>* (&tPtr))
{
	//更新算法，使用迭代；如前面更新 bf 一样，边计算 bf 边平衡
	bool chg = false; int tmp = 0;
	if (!tPtr)return 0;
	int L_length = 1, R_length = 1;
	L_length += avlUpdate(tPtr->Lchild);
	R_length += avlUpdate(tPtr->Rchild);
	tPtr->bf = L_length - R_length;
	avlUpdateBalance(tPtr,chg);  //调节平衡
	if (chg)  //表示调节过平衡
		tmp = MIN(L_length, R_length) + 1;
	else
		tmp = MAX(L_length, R_length);// ABS(tPtr->bf);
	return tmp;
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

#endif //__CPLUS_USRCLASSIFYBT_H__