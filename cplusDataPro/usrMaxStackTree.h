/**@file:     �Ѷ�������Ķ�����ʵ���ļ�
  *@Author��  T.H.
  *@Version�� V1.0
  *@Note:     
*/

#pragma once

#ifndef __CPLUS_USRMAXSTACKTREE_H__
#define __CPLUS_USRMAXSTACKTREE_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "usrBinaryTree.h"
#include <vector>
/** ˽�к�------------------------------------------------------------------------*/

/** �ඨ��------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

/** ��Ķ���--------------------------*/
template<class dataType>
class usrMaxStackTree
{

	//���з���-----------------//
public:
	usrMaxStackTree(){};   //Ĭ�Ϲ��캯��
	//�����Ļ�������------------------------//
	void initMaxStackTree(vector<dataType>&tdat, usrBinaryTree<dataType>&tusrBT);
	void initMaxStackTree(vector<dataType>&tdat);
};

//��ʼ������
template<class dataType>void usrMaxStackTree<dataType>::
initMaxStackTree(vector<dataType>&tdat)
{
	dataType ldatCache;  //��ʱ���ݻ���
	int isz_vec = tdat.size();
	vector<dataType>lvectDat(isz_vec + 1);
	lvectDat[0] = 0;
	int loop = 1;
	for (auto elem : tdat)
	{
		lvectDat[loop++] = elem;
	}
	//DblNode<dataType> *lptr_curNode = tusrBT.getTreeRoot();
	for (int curparent = isz_vec / 2; curparent > 0;curparent--)
	{
		ldatCache = lvectDat[curparent];
		int sonIndex = 2 * curparent;
		while (sonIndex <= isz_vec)
		{
			//�ҳ�����ӵ�����ֵ
			if (sonIndex < isz_vec&&lvectDat[sonIndex] < lvectDat[sonIndex + 1])
				sonIndex += 1;
			if (lvectDat[sonIndex] <= ldatCache)
				break;
			lvectDat[sonIndex / 2] = lvectDat[sonIndex]; //���ƽ��
			sonIndex *= 2;  //�ȶ���һ�㺢��
		}
		lvectDat[sonIndex / 2] = ldatCache;  //����λ��
	}
	//�����ݹ���Ϊ������
	tdat.assign(lvectDat.begin(), lvectDat.end());
}
template<class dataType>void usrMaxStackTree<dataType>::
initMaxStackTree(vector<dataType>&tdat, usrBinaryTree<dataType>&tusrBT)
{
	initMaxStackTree(tdat);
	//��vector�е����ݹ���Ϊһ����ȫ������
	int szVec = tdat.size();
	vector<DblNode<dataType>*>ltreeNode(szVec);//�����������ָ��
	//���ɽ�����ݣ����ݴ� 1 ��ʼ����
	for (int loop = 1; loop < szVec;loop++)
	{
		ltreeNode[loop] = tusrBT.creatBinaryTreeNode(tdat[loop]);
	}
	//���ӽ��
	for (int index = 1; index < szVec; index++)
	{
		if (index * 2 + 1 < szVec)
		{
			tusrBT.connectTree(ltreeNode[index], ltreeNode[index*2], ltreeNode[index*2+1]);
		}
		else if (index * 2 == szVec - 1)
		{
			tusrBT.connectTree(ltreeNode[index], ltreeNode[index*2], nullptr);
		}
		else
		{
			tusrBT.connectTree(ltreeNode[index], nullptr, nullptr);
		}
	}
	//��ָ���ÿ�
	ltreeNode.clear();
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

#endif  //__CPLUS_USRMAXSTACKTREE_H__
