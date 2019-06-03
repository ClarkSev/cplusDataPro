/**@file:     ��������Ķ����ļ�
  *@Author��  T.H.
  *@Version�� V1.2
  *@Note:     v1.0 --->searchDataByLDR() ʹ�õ��ǵݹ���б�������
			  v1.1 --->�ǵݹ����
	������ͨ�������ָ�����Һ������ֽṹ�У��ǵݹ�������ݣ�ǰ���������Ч�ʸ�
			  v1.2 --->��Ӳ�α���

  *@Attention����������Ҫ����ָ�����ݣ�һ��Ҫ�ö�άָ������޸ģ�
			  ����ֻ���޸ĵ��βζ�����ʵ��
			  ---->eg: fuc(int *tptr){ tptr=nullptr; }
			  �������û�и��ĳɹ�����Ҫʹ�ö�άָ��
			  -->fuc(int **tptr){ *tptr=nullptr; }���������޸ĳɹ�
*/

#pragma once

#ifndef __CPLUS_USRBINARYTREE_H__
#define __CPLUS_USRBINARYTREE_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "usrStack.h"   //�û���ջ��
#include <stack>        //ϵͳ��ջ��
#include <deque>
#include <iostream>
#include <string>

/** ˽�к�------------------------------------------------------------------------*/
#if !defined EN_USR_STACK_CLASS
	#define EN_USR_STACK_CLASS       (1)      //ʹ���û���ջ��
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


/** �ඨ��------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//���ڷǵݹ����ʱ�Ķ�ջԪ��
template<class dataType>
class usrBTStkType
{
public:
	DblNode<dataType> *curptr;   //����ָ��
	bool              status;
};

template<class dataType>
class usrBinaryTree
{
private:
	DblNode<dataType> *treeRoot;  //�����������
	//������������--�ݹ�
	int cntDeepth(DblNode<dataType> *tptr_TreeNode);
	//�����������--�ݹ�
	int cntNumNode(DblNode<dataType> *tptr_TreeNode);
protected:
	//������ݷ���
	bool visitNode(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode = 1)
	{
		if (tbMode)
		{
			if (!memcmp(&tptr_TreeNode->nodeDat, &tdat, sizeof(dataType)))
				return true;
		}
		else
			cout << "������ݣ�" << tptr_TreeNode->nodeDat << endl;
		return false;
	}

public:
	usrBinaryTree() :treeRoot(nullptr){};  //���캯��
	usrBinaryTree(const dataType &tdat);
	//�������������ʹ������������
	//��Ҫ�Ǳ����������󲻳���
	virtual ~usrBinaryTree();  

	//---------------��������������---------------//
	void connectTree(DblNode<dataType> *tptr_root, DblNode<dataType> *tptr_left, \
		DblNode<dataType> *tptr_right)
	{
		if (!treeRoot) treeRoot = tptr_root;
		tptr_root->ptrFront = tptr_left; tptr_root->ptrNext = tptr_right;
	}
	//���������������ɵ�������ַ
	DblNode<dataType>* creatBinaryTreeNode(const dataType &tdat);
	virtual void clrTree(DblNode<dataType> **tptr_TreeNode);  //��ն�����
	int getDeepth();  //��ȡ���������
	int getnumNode(); //��ȡ�����������
	bool isEmpty();  //�ж��Ƿ�Ϊ�������������ǿ���Ϊ������
	virtual DblNode<dataType>* getTreeRoot()const{ return treeRoot; }  //���ظ����ָ��
	virtual void printTree();  //������������ʾ--LDR�ݹ鷨

	//---------------��������������---------------//

	//�������ĵݹ�����������в������ݣ��������ݷ���true
	virtual bool searchDataLDR(const dataType &tdat, DblNode<dataType> *tptr_TreeNode,bool tbMode = 1);
	
	//ʹ�÷ǵݹ鷨���в������ݣ�tbModeΪȫ����������ֻΪ�˲�������
	//tbMode=1--��ʾ�������ݣ�tbMode=0--��ʾȫ���������������ݶ���
	virtual bool searchDataDLR_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode=1);
	//LDR �ǵݹ��������---���ֱ������������ô�
	virtual bool searchDataLDR_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1);
	//LRD �������
	virtual bool searchDataLRD_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1);
	//UpToDn_LToR �������£���������  ��α���
	virtual bool searchDataUpToDn_LToR(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1);
};

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//==========================================���������ʵ��===========================================//

using namespace std;

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

/** ˽�з�����ʵ��---------------------------------------------------------*/

//������������
template<class dataType>int usrBinaryTree<dataType>::
cntDeepth(DblNode<dataType> *tptr_TreeNode)
{
	int l_deepth_front = 1, l_deepth_next = 1;
	if (tptr_TreeNode != nullptr)   //�������������ڣ�������Ҫl_deepth_front�ĳ���ֵΪ1
	{
		l_deepth_front += cntDeepth(tptr_TreeNode->ptrFront);
		l_deepth_next += cntDeepth(tptr_TreeNode->ptrNext);
		return (l_deepth_front > l_deepth_next ? l_deepth_front : l_deepth_next);
	}
	return 0;
}
//�����������
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

/** ���з�����ʵ��---------------------------------------------------------*/
template<class dataType>usrBinaryTree<dataType>::
usrBinaryTree(const dataType &tdat)   //���캯��
{
	treeRoot = creatBinaryTreeNode(tdat);
}
template<class dataType>usrBinaryTree<dataType>::
~usrBinaryTree()   //��������
{
	clrTree(&treeRoot);
}
template<class dataType>DblNode<dataType>* usrBinaryTree<dataType>::
creatBinaryTreeNode(const dataType &tdat)  //������
{
	DblNode<dataType> *lptr_DblNode = new(DblNode<dataType>);  //���ɽ��
	if (!lptr_DblNode)
		return nullptr;
	memcpy(&lptr_DblNode->nodeDat, &tdat, sizeof(dataType));
	lptr_DblNode->ptrFront = nullptr;
	lptr_DblNode->ptrNext = nullptr;
	return lptr_DblNode;
}
//---------------------------��������������---------------------------//
//�������������������㿪ʼɾ��
template<class dataType>void usrBinaryTree<dataType>::
clrTree(DblNode<dataType> **tptr_TreeNode)
{
	if (!(*tptr_TreeNode))  //���ڵ�Ϊ��
		return;
	clrTree(&(*tptr_TreeNode)->ptrFront);
	clrTree(&(*tptr_TreeNode)->ptrNext);
	if ((!(*tptr_TreeNode)->ptrFront) && (!(*tptr_TreeNode)->ptrNext))  //������Ϊ��
	{
		if (*tptr_TreeNode == treeRoot)
		{
			treeRoot = nullptr;
		}
		delete (*tptr_TreeNode);  *tptr_TreeNode = nullptr;
	}
}
template<class dataType>int usrBinaryTree<dataType>::
getDeepth()  //��ȡ���������
{
	return cntDeepth(treeRoot);
}
template<class dataType>int usrBinaryTree<dataType>::
getnumNode() //��ȡ�����������
{
	return cntNumNode(treeRoot);
}
template<class dataType>bool usrBinaryTree<dataType>::
isEmpty()  //�ж��Ƿ�Ϊ����
{
	return getnumNode() == 0;
}
//������������ʾ������LDR������ʾ
template<class dataType>void usrBinaryTree<dataType>::
printTree()
{
	searchDataLDR(0, treeRoot, 0);   //ʹ�ñ����������д�ӡ����
}

//---------------------------��������������----------------------------//
//�������---�ݹ����
template<class dataType>bool usrBinaryTree<dataType>::
searchDataLDR(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	bool lb_flag = false;
	if (tptr_TreeNode != nullptr)
	{
		lb_flag = searchDataLDR(tdat, tptr_TreeNode->ptrFront, tbMode);  // ����������
		if (visitNode(tdat, tptr_TreeNode, tbMode))
			return true;
		lb_flag |= searchDataLDR(tdat, tptr_TreeNode->ptrNext, tbMode);  // ����������
	}
	return lb_flag;
}
//ǰ�����---ʹ�÷ǵݹ鷨���в�������
//����ʹ�÷ǵݹ�ķ�������������ʱ���������и����ָ�����������Ľṹ��
//ǰ���Ч�ʱ�������Ҫ�ߣ���Ϊ��������˳���У�ͬ����Ҫ��ͨ������㣬
//���ܷ��������ķ�֧
template<class dataType>bool usrBinaryTree<dataType>::
searchDataDLR_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	macrobtStkTmp<DblNode<dataType>*>lBtStk;   //������ʱ��ջ
	if (!tptr_TreeNode)  //Ϊ��ָ���ʾ��treeRoot��㿪ʼ����
		lptr_DblNode = treeRoot;
	while (lptr_DblNode || !lBtStk.isEmpty())
	{
		if (!lptr_DblNode)  //������Ϊ��
		{
			lBtStk.pop(lptr_DblNode);  //��ջ����������ָ���ҽ��
			lptr_DblNode = lptr_DblNode->ptrNext;
		}
		else
		{
			lBtStk.push(lptr_DblNode);   //����ͷָ��
			if (visitNode(tdat, lptr_DblNode, tbMode))
				return true;
			lptr_DblNode = lptr_DblNode->ptrFront;  //ָ������
		}
	}
	return false;
}
//�������---�ǵݹ����
template<class dataType>bool usrBinaryTree<dataType>::
searchDataLDR_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	macrobtStkTmp<DblNode<dataType>*>lBtStk;   //������ʱ��ջ
	if (!tptr_TreeNode)  //Ϊ��ָ���ʾ��treeRoot��㿪ʼ����
		lptr_DblNode = treeRoot;
	while (lptr_DblNode || !lBtStk.isEmpty())
	{
		while (lptr_DblNode)   //�ҵ�����ߵĽ��
		{
			lBtStk.push(lptr_DblNode);
			lptr_DblNode = lptr_DblNode->ptrFront; //�л�������
		}
		if (!lBtStk.isEmpty())
		{
			lBtStk.pop(lptr_DblNode);  //����ջ������
			//��������
			if (visitNode(tdat, lptr_DblNode, tbMode))
				return true;
			lptr_DblNode = lptr_DblNode->ptrNext;  //ָ���ҽ��
		}
	}
	return false;
}
//LRD �������---��Ϊ��������ᾭ�����θ����
//������Ҫһ����־λ�����жϽ����ʴ���,
//�����usrBTStkType�� ������������־λ����
template<class dataType>bool usrBinaryTree<dataType>::
searchDataLRD_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	macrobtStkTmp<usrBTStkType<dataType>>lBtStk;   //������ʱ��ջ
	usrBTStkType<dataType>lstkTmp;
	if (!tptr_TreeNode)  //Ϊ��ָ���ʾ��treeRoot��㿪ʼ����
		lptr_DblNode = treeRoot;
	while (lptr_DblNode || !lBtStk.isEmpty())
	{
		//�ҵ�����ߵĽ��
		while (lptr_DblNode)
		{
			lstkTmp.curptr = lptr_DblNode;
			lstkTmp.status = false;
			lBtStk.push(lstkTmp);
			lptr_DblNode = lptr_DblNode->ptrFront;
		}
		//�������ݣ������������
		if (!lBtStk.isEmpty())
		{
			lBtStk.pop(lstkTmp);  //��ʱlstkTmp.curptr�����Ǹ����
			lptr_DblNode = lstkTmp.curptr;   //װ�ؽ��ָ��
			//������������
			if (lstkTmp.status)  //�ڶ��η���
			{
				if (visitNode(tdat, lptr_DblNode, tbMode))
					return true;
				lptr_DblNode = nullptr;  //������ǰ���
			}
			else  //��һ�η��ʸ����
			{
				lstkTmp.status = true;
				lBtStk.push(lstkTmp);
				lptr_DblNode = lptr_DblNode->ptrNext;  //�л����ҽ��
			}
		}
	}
	return false;
}
//���ϵ��£��������ҵķǵݹ����
//����ʹ�õ��˶��нṹ��ʹ�ö��д洢���ʵ��ĸ��������Һ��ӽ��
template<class dataType>bool usrBinaryTree<dataType>::
searchDataUpToDn_LToR(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	macrobtDeqTmp<DblNode<dataType>*>lBtDeq;   //������ʱ���У����ڴ洢���
	if (!tptr_TreeNode)  //Ϊ��ָ���ʾ��treeRoot��㿪ʼ����
		lptr_DblNode = treeRoot;
	while (1)  //����Ϊ�գ����ҽ���
	{
		//���Һ��ӽ���
		if (lptr_DblNode->ptrFront)
			lBtDeq.enQueue(lptr_DblNode->ptrFront);  
		if (lptr_DblNode->ptrNext)
			lBtDeq.enQueue(lptr_DblNode->ptrNext);
		//���ʽ������
		if (visitNode(tdat, lptr_DblNode, tbMode))
			return true;
		if (!lBtDeq.isEmpty())
			lBtDeq.deQueue(lptr_DblNode);   //����
		else
			break;
	}
	return false;
}


#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE


#endif //__CPLUS_USRBINARYTREE_H__

 