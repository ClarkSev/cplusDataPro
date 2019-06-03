/**@file:     �����������Ķ����ļ�
  *@Author��  T.H.
  *@Version�� V1.0
  *@Note:     ����һ�ֱȽ�����Ķ����������ص㣺
              1��������������С�ڸ����
			  2�����������������ڸ����
			  3����������Ҳ�Ƿ��������
	���м̳��˶������Ĺ��ó�Ա�ͷ����������������е����зǵݹ��������
*/

#pragma once

#ifndef __CPLUS_USRCLASSIFYBT_H__
#define __CPLUS_USRCLASSIFYBT_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "usrBinaryTree.h"

/** ˽�к�------------------------------------------------------------------------*/

/** �ඨ��------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE


//---------------------����������ඨ��-------------------------//
template<class dataType>
class usrClassifyBT:public usrBinaryTree<dataType>
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

//---------------------�����������ʵ��-------------------------//
//---------˽�з���ʵ��--------//

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

#endif //__CPLUS_USRCLASSIFYBT_H__
