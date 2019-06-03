/**@file:     堆二叉树类的定义与实现文件
  *@Author：  T.H.
  *@Version： V1.0
  *@Note:     
*/

#pragma once

#ifndef __CPLUS_USRMAXSTACKTREE_H__
#define __CPLUS_USRMAXSTACKTREE_H__

/** 引入文件----------------------------------------------------------------------*/
#include "usrBinaryTree.h"
#include <vector>
/** 私有宏------------------------------------------------------------------------*/

/** 类定义------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

/** 类的定义--------------------------*/
template<class dataType>
class usrMaxStackTree
{

	//公有方法-----------------//
public:
	usrMaxStackTree(){};   //默认构造函数
	//堆树的基本操作------------------------//
	void initMaxStackTree(vector<dataType>&tdat, usrBinaryTree<dataType>&tusrBT);
	void initMaxStackTree(vector<dataType>&tdat);
};

//初始化堆树
template<class dataType>void usrMaxStackTree<dataType>::
initMaxStackTree(vector<dataType>&tdat)
{
	dataType ldatCache;  //临时数据缓存
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
			//找出最大孩子的索引值
			if (sonIndex < isz_vec&&lvectDat[sonIndex] < lvectDat[sonIndex + 1])
				sonIndex += 1;
			if (lvectDat[sonIndex] <= ldatCache)
				break;
			lvectDat[sonIndex / 2] = lvectDat[sonIndex]; //上移结点
			sonIndex *= 2;  //比对下一层孩子
		}
		lvectDat[sonIndex / 2] = ldatCache;  //交换位置
	}
	//将数据构建为二叉树
	tdat.assign(lvectDat.begin(), lvectDat.end());
}
template<class dataType>void usrMaxStackTree<dataType>::
initMaxStackTree(vector<dataType>&tdat, usrBinaryTree<dataType>&tusrBT)
{
	initMaxStackTree(tdat);
	//将vector中的数据构建为一个完全二叉树
	int szVec = tdat.size();
	vector<DblNode<dataType>*>ltreeNode(szVec);//定义三个结点指针
	//生成结点数据，数据从 1 开始计算
	for (int loop = 1; loop < szVec;loop++)
	{
		ltreeNode[loop] = tusrBT.creatBinaryTreeNode(tdat[loop]);
	}
	//连接结点
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
	//将指针置空
	ltreeNode.clear();
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

#endif  //__CPLUS_USRMAXSTACKTREE_H__
