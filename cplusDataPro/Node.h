/**@file:     �����Ķ�����ʵ���ļ�
  *@Author��  T.H.
  *@function: �򵥵Ľ�����ݵĶ���
  *@Version�� V1.0
  *@Note:     None
*/

#pragma once

#ifndef __CPLUS_USRNODE_H__
#define __CPLUS_USRNODE_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "stdafx.h"
#include <iostream>

/** ˽�к�------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE


#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif

/** ����ඨ��-----------------------------------------------------------*/
template<class dataType>
class Node    //���ڵ���
{
public:
	dataType        nodeDat;    //�������
	Node<dataType>  *ptrNext;   //���ָ��

	Node() :ptrNext(nullptr){};  // ���캯��--ֻ�ǽ��ض�����Ұָ��
	~Node(){ ptrNext = nullptr; };  //��������
	Node<dataType> *createNode(const dataType t_dat)
	{
		Node<dataType> *l_ptr = new (Node<dataType>);
		memcpy(&(l_ptr->nodeDat), &t_dat, sizeof(dataType));
		l_ptr->ptrNext = nullptr;
		return l_ptr;
	}
};
template<typename headType, typename nodeType = headType>
class HeadNode  //ͷ�������
{
public:
	headType       nodeDat;    //ͷ�������
	Node<nodeType> *ptrNext;   //�������ָ��

	HeadNode() :ptrNext(nullptr){};  // ���캯��--ֻ�ǽ��ض�����Ұָ��
	~HeadNode(){ ptrNext = nullptr; };  //��������
	HeadNode<headType,nodeType> *createHeadNode(const headType t_dat)
	{
		HeadNode<headType, nodeType> *l_ptr = new (HeadNode<headType, nodeType>);
		memcpy(&(l_ptr->nodeDat), &t_dat, sizeof(headType));
		l_ptr->ptrNext = nullptr;
		return l_ptr;
	}
};
template<class dataType>
class DblNode   //˫�����
{
public:
	dataType          nodeDat;           //�������
	DblNode<dataType> *ptrFront,*ptrNext;//���ָ��

	DblNode() :ptrFront(nullptr), ptrNext(nullptr){};     //���캯��
	~DblNode(){ ptrFront = nullptr; ptrNext = nullptr; }  //��������
};


#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif

#endif //__CPLUS_USRNODE_H__
