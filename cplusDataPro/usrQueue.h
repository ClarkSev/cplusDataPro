/**@file:     ������Ķ�����ʵ���ļ�
  *@Author��  T.H.
  *@Version�� V1.0
  *@Note:     None
*/
#pragma once

#ifndef __CPLUS_USRQUEUE_H__
#define __CPLUS_USRQUEUE_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "Node.h"
#include <iostream>
#include <string>

/** ˽�к�------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
	#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//��Ķ���
template<class dataType>
class usrQueue
{
private:
	int length;  //���д�С
	int MaxUsrQueueSize;  //�����д�С
	Node<dataType> *front, *rear;  //����/β ָ��
public:
	usrQueue(int iszQueue = 65535):length(0),MaxUsrQueueSize(iszQueue),\
		front(nullptr), rear(nullptr){};  //���캯��
	~usrQueue();  //��������

	//---------------���б����-----------------//
	Node<dataType>* getRear()const{ return rear; }  //��ȡ��βָ��
	Node<dataType>* getFront()const { return front; }  //��ȡ����ָ��
	bool enQueue(const dataType tdat);  //���
	bool deQueue(dataType &tdat);  //����
	bool clrQueue();  //��ն���
	bool isEmpty()const { return length == 0; }  //�ж��Ƿ�Ϊ��
	bool isFull()const { return length == MaxUsrQueueSize; }  //�ж��Ƿ�Ϊ��
	int size()const { return length; }  //��ȡ���д�С
};

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif //EN_NMSPACE_USR_DATASTRUCTURE

//------------------------------�������ʵ��-------------------------------//
using namespace std;

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif //EN_NMSPACE_USR_DATASTRUCTURE

/** ���з���ʵ��------------------------------------------*/
template<class dataType>usrQueue<dataType>::
~usrQueue()  //��������ʵ��
{
	clrQueue();
	front = nullptr; rear = nullptr;
}

//---------------���б����ʵ��-----------------//
template<class dataType>bool usrQueue<dataType>::
enQueue(const dataType tdat)  //��Ӳ���
{
	if (isFull())
	{
		//cout << "The Queue is Full!" << endl; 
		return false;
	}
	//�ڶ�β������
	Node<dataType> *l_ptrNode = new(Node<dataType>);
	if (!l_ptrNode)
		return false;
	memcpy(&(l_ptrNode->nodeDat), &tdat, sizeof(tdat));
	l_ptrNode->ptrNext = nullptr;
	if (rear == nullptr)  //�����һ�����Ĵ���
	{
		rear = l_ptrNode;
		front = rear;
	}
	else
	{
		rear->ptrNext = l_ptrNode; //���ӽ��
		rear = rear->ptrNext;   //ת�ƽ��
	}
	l_ptrNode = nullptr;  //����ָ�룬�����ͷſռ�
	length += 1;
	return true;
}

template<class dataType>bool usrQueue<dataType>::
deQueue(dataType &tdat)  //���Ӳ���
{
	if (isEmpty())
	{
		//cout << "The Queue is Empty!" << endl; 
		return false;
	}
	//�ڶ���ɾ���ڵ�
	Node<dataType> *l_ptrNode = front;
	memcpy(&tdat, &l_ptrNode->nodeDat, sizeof(tdat));  //��ȡ��������
	front = front->ptrNext;
	l_ptrNode->ptrNext = nullptr;   //�Ͽ�����
	delete l_ptrNode; l_ptrNode = nullptr;  //ɾ���ڵ�
	length -= 1;
	if (!length)
	{
		rear = nullptr;  //��������һ��Ԫ�أ���Ҫ�����Ķ�βָ���ÿ�
	}
	return true;
}
template<class dataType>bool usrQueue<dataType>::
clrQueue()
{
	dataType l_cache;
	while (!isEmpty())
		deQueue(l_cache);
	return true;
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE


#endif //__CPLUS_USRQUEUE_H__