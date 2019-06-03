/**@file:     结点类的定义与实现文件
  *@Author：  T.H.
  *@function: 简单的结点数据的定义
  *@Version： V1.0
  *@Note:     None
*/

#pragma once

#ifndef __CPLUS_USRNODE_H__
#define __CPLUS_USRNODE_H__

/** 引入文件----------------------------------------------------------------------*/
#include "stdafx.h"
#include <iostream>

/** 私有宏------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE


#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif

/** 结点类定义-----------------------------------------------------------*/
template<class dataType>
class Node    //单节点类
{
public:
	dataType        nodeDat;    //结点数据
	Node<dataType>  *ptrNext;   //结点指针

	Node() :ptrNext(nullptr){};  // 构造函数--只是将重定向了野指针
	~Node(){ ptrNext = nullptr; };  //析构函数
	Node<dataType> *createNode(const dataType t_dat)
	{
		Node<dataType> *l_ptr = new (Node<dataType>);
		memcpy(&(l_ptr->nodeDat), &t_dat, sizeof(dataType));
		l_ptr->ptrNext = nullptr;
		return l_ptr;
	}
};
template<typename headType, typename nodeType = headType>
class HeadNode  //头结点类型
{
public:
	headType       nodeDat;    //头结点数据
	Node<nodeType> *ptrNext;   //后续结点指针

	HeadNode() :ptrNext(nullptr){};  // 构造函数--只是将重定向了野指针
	~HeadNode(){ ptrNext = nullptr; };  //析构函数
	HeadNode<headType,nodeType> *createHeadNode(const headType t_dat)
	{
		HeadNode<headType, nodeType> *l_ptr = new (HeadNode<headType, nodeType>);
		memcpy(&(l_ptr->nodeDat), &t_dat, sizeof(headType));
		l_ptr->ptrNext = nullptr;
		return l_ptr;
	}
};
template<class dataType>
class DblNode   //双结点类
{
public:
	dataType          nodeDat;           //结点数据
	DblNode<dataType> *ptrFront,*ptrNext;//结点指针

	DblNode() :ptrFront(nullptr), ptrNext(nullptr){};     //构造函数
	~DblNode(){ ptrFront = nullptr; ptrNext = nullptr; }  //析构函数
};


#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif

#endif //__CPLUS_USRNODE_H__
