/**@File:     �����������Ķ����ļ�
  *@Author��  T.H.
  *@Version�� V1.1
  *@Note:     ����һ�ֱȽ�����Ķ����������ص㣺
              1��������������С�ڸ����
			  2�����������������ڸ����
			  3����������Ҳ�Ƿ��������
	���м̳��˶������Ĺ��ó�Ա�ͷ����������������е����зǵݹ��������

	2019-6-24:��usrClassifyBT ����Ϊ��̳� usrBinaryTree

	Update: ���AVL��--ƽ�������(���ƽ���㷨�ķ��������)

*/

#pragma once

#ifndef __CPLUS_USRCLASSIFYBT_H__
#define __CPLUS_USRCLASSIFYBT_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "usrBinaryTree.h"

/** ˽�к�------------------------------------------------------------------------*/
#if !defined MIN
#define MIN(x,y)      ((x)>(y)?(y):(x))
#endif
#if !defined MAX
#define MAX(x,y)      ((x)>(y)?(x):(y))
#endif
#if !defined ABS
#define ABS(x)      ((x)>0?(x):(-x))
#endif
/** �ඨ��------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//-----------------------------------����������ඨ��-------------------------------------------//
template<class dataType>
class usrClassifyBT:virtual public usrBinaryTree<dataType>
{
private:
	DblNode<dataType> *classifyTreeRoot;  //��������������
	void deleteNode(DblNode<dataType> **tptr_TreeNode)
	{
		if (tptr_TreeNode){
			delete (*tptr_TreeNode); (*tptr_TreeNode) = nullptr; 
		}
	};

public:
	usrClassifyBT() :usrBinaryTree(), classifyTreeRoot(nullptr){};  //Ĭ�Ϲ��캯��
	usrClassifyBT(const dataType &tdat);
	virtual ~usrClassifyBT(){};  //Ĭ����������

	//-------------------�����������Ӧ��------------------//
	//�������ݣ����������ڵĽ�㴫�ظ�tptrָ��
	//�������ڣ��򽫽���ǰ�Ľ�㴫�أ���Ϊ��ʱ�Ľ��������tdat��ֵ�����
	//�������ں��������ݲ���
	bool searchDataClassifyBT(const dataType &tdat,DblNode<dataType> **tptr_TreeNode = nullptr);
	//bInsertMode -- ��ʾ�������ģʽ
	//bInsertMode=1---���������ͬ���ݽ��(default) bInsertMode = 0---������
	bool insertNodeDat(const dataType &tdat, const bool bInsertMode = true);
	//ɾ�������м��ַ���--->
	//1.����ɾ���ڵ���Ҷ�ӽ��ʱ��ֱ��ɾ����ok
	//2.���ý�������������ֻ��һ������ʱ
	//ֱ��ɾ������㣬�����亢����Ϊ�µ������ڵ�
	//3.�������������ֻ��һ�����ӣ��ƶ��亢�ӽ��
	//��Ϊ�µĽ�㣬Ȼ��ɾ���ý��
	//4.��������������ӣ��������������ұߵĽ�㣨��������������ݣ�
	//��������������ߵĽ�㣨������������С���ݣ��ƶ���Ϊ�µĸ����
	bool deleteNodeDat(const dataType &tdat);

	//-------------------��̬-------------------//
	//�����˶���������ĺ���
	DblNode<dataType>* getTreeRoot()const override{ return classifyTreeRoot; }
	//DLR ǰ�����
	bool searchDataDLR_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1)override;
	//LDR �ǵݹ��������---���ֱ������������ô�
	bool searchDataLDR_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1)override;
	//LRD �������
	bool searchDataLRD_Noiter(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1)override;
	//UpToDn_LToR �������£���������  ��α���
	bool searchDataUpToDn_LToR(const dataType &tdat, \
		DblNode<dataType> *tptr_TreeNode = nullptr, bool tbMode = 1)override;
	
	void printTree()override;
};

//-----------------------------------�����������ʵ��-------------------------------------------//
//---------���з���ʵ��--------//
//���캯��
template<class dataType>usrClassifyBT<dataType>::
usrClassifyBT(const dataType &tdat)
{
	classifyTreeRoot = usrBinaryTree::creatBinaryTreeNode(tdat);
}
//�������ݣ���*tptr_TreeNode����Ϊ����Ϊtdat������tdat������ݵĽ��
template<class dataType>bool usrClassifyBT<dataType>::
searchDataClassifyBT(const dataType &tdat,DblNode<dataType> **tptr_TreeNode)
{
	DblNode<dataType>* lptr_DblNode = getTreeRoot();
	while (lptr_DblNode)
	{
		if (tptr_TreeNode)   //����Ϊ�գ��ݴ�ǰһ������ַ
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
	//�ж��Ƿ���ڸ�����
	//�����ڣ������ʧ�ܣ������½���㣬������
	DblNode<dataType> *lptr_curTreeNode = nullptr;
	//bInsertMode=false ��ʾ�����������ͬ���ݽ��
	if (searchDataClassifyBT(tdat, &lptr_curTreeNode) && (!bInsertMode))
		return false;
	//�������
	DblNode<dataType>* lptr_DblNode = creatBinaryTreeNode(tdat);
	// nodeDat   tdat
	if (!lptr_curTreeNode)  //��һ���������
	{
		classifyTreeRoot = lptr_DblNode;
		lptr_DblNode = nullptr;   //�ض���ָ��
		return true;
	}
	int retcmp = memcmp(&lptr_curTreeNode->nodeDat, &tdat, sizeof(dataType));
	if (retcmp>0)
		lptr_curTreeNode->ptrFront = lptr_DblNode; // nodeDat>tdat
	else
		lptr_curTreeNode->ptrNext = lptr_DblNode;  //nodeDat<=tdat
	return true;
}
//ɾ���������
//ɾ�������м��ַ���--->
//1.����ɾ���ڵ���Ҷ�ӽ��ʱ��ֱ��ɾ����ok
//2.���ý�������������ֻ��һ������ʱ
//ֱ��ɾ������㣬�����亢����Ϊ�µ������ڵ�
//3.�������������ֻ��һ�����ӣ��ƶ��亢�ӽ��
//��Ϊ�µĽ�㣬Ȼ��ɾ���ý��
//4.��������������ӣ��������������ұߵĽ�㣨��������������ݣ�
//��������������ߵĽ�㣨������������С���ݣ��ƶ���Ϊ�µĸ����
template<class dataType>bool usrClassifyBT<dataType>::
deleteNodeDat(const dataType &tdat)
{
	DblNode<dataType> *lptr_curTreeNode = classifyTreeRoot,
		*lptr_parentNode = nullptr,
		*lptr_sonNode = nullptr,//���ӽ��
		*lptr_sonparentNode = nullptr;  //���ӵĸ����
	int retcmp = memcmp(&lptr_curTreeNode->nodeDat, &tdat, sizeof(dataType));
	//�������ݣ����ҳ������ڵĸ����
	while (lptr_curTreeNode && \
		( (retcmp = memcmp(&lptr_curTreeNode->nodeDat, &tdat, sizeof(dataType)) ) != 0))
	{
		lptr_parentNode = lptr_curTreeNode;
		if (retcmp > 0)
			lptr_curTreeNode = lptr_curTreeNode->ptrFront;
		else
			lptr_curTreeNode = lptr_curTreeNode->ptrNext;
	}
	if (!lptr_curTreeNode)  //û���ҵ�����
		return false;
	if ((!lptr_curTreeNode->ptrFront) && (!lptr_curTreeNode->ptrNext))
	{
		//������Ϊ���1��ֱ��ɾ�����
		deleteNode(&lptr_curTreeNode);
		return true;
	}
	//���2��3
	if (lptr_curTreeNode->ptrFront && (!lptr_curTreeNode->ptrNext))  //ֻ������
	{
		lptr_sonNode = lptr_curTreeNode->ptrFront;

	}
	else if ( ( !lptr_curTreeNode->ptrFront) && lptr_curTreeNode->ptrNext )  //ֻ���Һ���
	{
		lptr_sonNode = lptr_curTreeNode->ptrNext;
	}
	if ( (lptr_curTreeNode == classifyTreeRoot) && lptr_sonNode )
	{
		classifyTreeRoot = lptr_sonNode;
		lptr_sonNode = nullptr;//�Ͽ�����
		deleteNode(&lptr_curTreeNode);//ɾ�����
		return true;
	}
	else if (lptr_sonNode)   //ֻ�е����ӵ�һ���㣬���3
	{
		if (lptr_parentNode->ptrFront == lptr_curTreeNode)
			lptr_parentNode->ptrFront = lptr_sonNode;
		else
			lptr_parentNode->ptrNext = lptr_sonNode;
		lptr_sonNode = nullptr;//�Ͽ�����
		deleteNode(&lptr_curTreeNode);//ɾ�����
		return true;
	}
	//���4--һ���㣬�������ӽ�㣬�����������������Ϊ�µĸ����
	lptr_sonNode = lptr_curTreeNode->ptrFront;
	lptr_sonparentNode = lptr_curTreeNode;
	while (lptr_sonNode->ptrNext)
	{
		lptr_sonparentNode = lptr_sonNode;
		lptr_sonNode = lptr_sonNode->ptrNext;
	}
	lptr_curTreeNode->nodeDat = lptr_sonNode->nodeDat;  //�ƶ����
	//�Ͽ����ӣ����Ǳ�Ҫ��
	if (lptr_sonparentNode->ptrFront == lptr_sonNode)
		lptr_sonparentNode->ptrFront = nullptr;
	else
		lptr_sonparentNode->ptrNext = nullptr;
	deleteNode(&lptr_sonNode);//ɾ�����
	return true;
}
//--------------------------------��̬------------------------------//
template<class dataType>void usrClassifyBT<dataType>::
printTree()  //������������
{
	cout << "����������---------->\n";
	searchDataLDR_Noiter(0, classifyTreeRoot, false);
}
//ǰ�����
template<class dataType>bool usrClassifyBT<dataType>::
searchDataDLR_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	if (!tptr_TreeNode)
		lptr_DblNode = classifyTreeRoot;
	return usrBinaryTree::searchDataDLR_Noiter(tdat, lptr_DblNode, tbMode);
}
//�������
template<class dataType>bool usrClassifyBT<dataType>::
searchDataLDR_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	if (!tptr_TreeNode)
		lptr_DblNode = classifyTreeRoot;
	return usrBinaryTree::searchDataLDR_Noiter(tdat, lptr_DblNode, tbMode);
}
//��������
template<class dataType>bool usrClassifyBT<dataType>::
searchDataLRD_Noiter(const dataType &tdat, DblNode<dataType> *tptr_TreeNode, bool tbMode)
{
	DblNode<dataType> *lptr_DblNode = tptr_TreeNode;
	if (!tptr_TreeNode)
		lptr_DblNode = classifyTreeRoot;
	return usrBinaryTree::searchDataLRD_Noiter(tdat, lptr_DblNode, tbMode);
}
//UpToDn_LToR �������£���������  ��α���
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

//-----------------------------------ƽ��������ඨ��-------------------------------------------//

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//����ƽ������ö����
//enum class BALANCE_FACTOR:int{};
#define LH_RL					(1)  //����ҵ�
#define RH_LL					(-1) //����Ҹ�
#define R_EQ_L					(0)  //���Ҹߵ�һ��

//AVL���ڵ㶨��
template<typename dataType>
class AVLNode
{
public:
	int bf;  //ƽ������
	dataType nodeDat;  //������
	AVLNode *Lchild, *Rchild;    //���Һ��ӽ��

	AVLNode(const dataType &tdat) :nodeDat(tdat),bf(0), Lchild(nullptr), Rchild(nullptr) {};
};
template<typename dataType>
class usrAVLTree
{
private:
	AVLNode<dataType>   *avlTreeRoot;

protected:
	void avlR_Rotation(AVLNode<dataType>* (&tptr));    //��tptrΪ���������������
	void avlL_Rotation(AVLNode<dataType>* (&tptr));       //��tptrΪ���������������
	void avlR_Rotate_Balance(AVLNode<dataType>* (&tptr)); //����ƽ�⴦��
	void avlL_Rotate_Balance(AVLNode<dataType>* (&tptr)); //����ƽ�⴦��

public:
	usrAVLTree() :avlTreeRoot(nullptr){};
	bool searchDataAVL(const dataType & tdat, AVLNode<dataType>*(&tptr));
	bool insertAVLNode(const dataType tdat);
	int avlUpdateBF(AVLNode<dataType>* (&tPtr));
	void avlUpdateBalance(AVLNode<dataType>* (&tPtr),bool &chg);
	int avlUpdate(AVLNode<dataType>*(&tPtr));
};

//-----------------------------------ƽ���������ʵ��-------------------------------------------//
template<typename dataType>void usrAVLTree<dataType>::avlR_Rotation(AVLNode<dataType>* (&tptr))
{
	//����������bfƽ�����Ӵ���
	if (!tptr) return;
	AVLNode<dataType> *lptr = tptr->Lchild;
	tptr->Lchild = lptr->Rchild;
	lptr->Rchild = tptr;
	tptr = lptr;
}
template<typename dataType>void usrAVLTree<dataType>::avlL_Rotation(AVLNode<dataType>* (&tptr))
{
	//����������bfƽ�����Ӵ���
	if (!tptr) return;
	AVLNode<dataType>* lptr = tptr->Rchild;
	tptr->Rchild = lptr->Lchild;
	lptr->Lchild = tptr;
	tptr = lptr;
}
//����ƽ�⴦�����Ӹ߶Ƚ��Һ��Ӹߣ���������bfƽ�����ӣ���������������˫����ת
//��ϸ�� bf �仯�����Ը��ݻ�ͼ���㣬�������ݽṹ�� P343 ��ͼ��
template<typename dataType>void usrAVLTree<dataType>::avlR_Rotate_Balance(AVLNode<dataType>* (&tptr))
{
	if (!tptr) return;
	if (tptr->bf <= 1 && tptr->bf >= -1) return;  //�Ѿ�ƽ�ⲻ��Ҫ��ת
	AVLNode<dataType> *lptr = tptr->Lchild,*tmp = nullptr;
	switch (lptr->bf)
	{
	case 1:   //������ƽ�����������ʱֻ��Ҫ�Ը�������һ����������
		//�޸�ƽ�����ӣ�ֻ��Ҫ���������µ���ָ��ָ��Ľ��bf����
		lptr->bf = 0;
		tptr->bf = 0;
		avlR_Rotation(tptr);
		break;
	//case 2:
	//	//��һ����������
	//	lptr->bf = 0; tptr->bf = -1;
	//	avlR_Rotation(tptr); break;
	case -1:
		//��Ҫ�����������˫����ת
		tmp = lptr->Rchild;
		switch (tmp->bf)
		{
		case 0:  //��������� tmp ��Ҷ�ӽ��
			lptr->bf = 0; tptr->bf = 0; break;
		case 1:  //��һ����������
			//����bf
			lptr->bf = 0;tptr->bf = -1;	break;
		case -1: 
			//����������bf
			lptr->bf = 0;tptr->bf = 0;break;
		}
		tmp->bf = 0;
		avlL_Rotation(lptr);
		tptr->Lchild = lptr; //���½��
		avlR_Rotation(tptr);//������
		break;
	}
}
//����ƽ�⴦���Һ��ӽ����Ӹߣ�---������ƽ������
template<typename dataType>void usrAVLTree<dataType>::avlL_Rotate_Balance(AVLNode<dataType>* (&tptr))
{
	if (!tptr) return;
	if (tptr->bf <= 1 || tptr->bf >= -1) return;  //�Ѿ�ƽ�ⲻ��Ҫ��ת
	AVLNode<dataType> *lptr = tptr->Rchild, *tmp = nullptr;
	switch (lptr->bf)
	{
	case -1:   //�Һ�����ƽ�����������ʱֻ��Ҫ�Ը�������һ����������
			  //�޸�ƽ�����ӣ�ֻ��Ҫ���������µ���ָ��ָ��Ľ��bf����
		lptr->bf = 0;
		tptr->bf = 0;
		avlL_Rotation(tptr);
		break;
	//case -2: //��һ������
	//	tptr->bf = 1; lptr->bf = 0;
	//	avlL_Rotation(tptr); break;
	case 1:
		//��Ҫ�������Һ���˫����ת
		tmp = lptr->Lchild;
		switch (tmp->bf)
		{
		case 0:  //��������� tmp ��Ҷ�ӽ��
			lptr->bf = 0; tptr->bf = 0; break;
		case 1: //��һ���������ɸ���bf
			lptr->bf = -1; tptr->bf = 0;break;
		case -1://����������bf
			lptr->bf = 0; tptr->bf = 1;break;
		}
		tmp->bf = 0;
		avlR_Rotation(lptr);
		tptr->Rchild = lptr;//���½��
		avlL_Rotation(tptr);//������
		break;
	}
}
//�������ݣ���*tptr_TreeNode����Ϊ����Ϊtdat������tdat������ݵĽ��
template<typename dataType>bool usrAVLTree<dataType>::
searchDataAVL(const dataType &tdat, AVLNode<dataType> *(&tptr))
{
	AVLNode<dataType> *lPtr = avlTreeRoot;
	while (lPtr)
	{
		//if (tptr)   //����Ϊ�գ��ݴ�ǰһ������ַ
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
	if (searchDataAVL(tdat, tmpPtr)) //�����Ѿ����ڸýڵ�
		return false;
	//nodeData tdat
	int retcmp = memcmp(&tmpPtr->nodeDat, &tdat, sizeof(dataType));
	if (retcmp>0)  //����߲���
		tmpPtr->Lchild = lptr;
	else   //���ұ߲���
		tmpPtr->Rchild = lptr;
	//avlUpdateBF(avlTreeRoot);  //���� bf 
	//avlUpdateBalance(avlTreeRoot);  //ƽ��
	avlUpdate(avlTreeRoot);
	lptr = nullptr;
	return true;
}
//���� bf
template<typename dataType>int usrAVLTree<dataType>::avlUpdateBF(AVLNode<dataType>* (&tPtr))
{
	//���� ƽ������ �������������Һ��Ӹ߶Ȳ�
	//ʹ�õ���ʵ��
	//AVLNode<dataType> *lPtr = avlTreeRoot;
	if (!tPtr)return 0;
	int L_length = 0, R_length = 0;
	L_length += avlUpdateBF(tPtr->Lchild);
	R_length += avlUpdateBF(tPtr->Rchild);
	tPtr->bf = L_length - R_length;
	return L_length > R_length ? L_length : R_length;
}
//����ƽ��
template<typename dataType>void usrAVLTree<dataType>::avlUpdateBalance(AVLNode<dataType>* (&tPtr),bool &chg)
{
	switch (tPtr->bf)
	{
	case 1:
	case 0:
	case -1: chg = false; break;
	case 2:  //����ƽ��
		chg = true; avlR_Rotate_Balance(tPtr); break;
	case -2: //����ƽ��
		chg = true; avlL_Rotate_Balance(tPtr); break;
	}
}
//AVL�������㷨----���� ����bf �� ����ƽ��

template<typename dataType>int usrAVLTree<dataType>::avlUpdate(AVLNode<dataType>* (&tPtr))
{
	//�����㷨��ʹ�õ�������ǰ����� bf һ�����߼��� bf ��ƽ��
	bool chg = false; int tmp = 0;
	if (!tPtr)return 0;
	int L_length = 1, R_length = 1;
	L_length += avlUpdate(tPtr->Lchild);
	R_length += avlUpdate(tPtr->Rchild);
	tPtr->bf = L_length - R_length;
	avlUpdateBalance(tPtr,chg);  //����ƽ��
	if (chg)  //��ʾ���ڹ�ƽ��
		tmp = MIN(L_length, R_length) + 1;
	else
		tmp = MAX(L_length, R_length);// ABS(tPtr->bf);
	return tmp;
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

#endif //__CPLUS_USRCLASSIFYBT_H__