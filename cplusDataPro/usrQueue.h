/**@file:     队列类的定义与实现文件
  *@Author：  T.H.
  *@Version： V1.0
  *@Note:     None
*/
#pragma once

#ifndef __CPLUS_USRQUEUE_H__
#define __CPLUS_USRQUEUE_H__

/** 引入文件----------------------------------------------------------------------*/
#include "Node.h"
#include <iostream>
#include <string>

/** 私有宏------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
	#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//类的定义
template<class dataType>
class usrQueue
{
private:
	int length;  //队列大小
	int MaxUsrQueueSize;  //最大队列大小
	Node<dataType> *front, *rear;  //队首/尾 指针
public:
	usrQueue(int iszQueue = 65535):length(0),MaxUsrQueueSize(iszQueue),\
		front(nullptr), rear(nullptr){};  //构造函数
	~usrQueue();  //析构函数

	//---------------队列表操作-----------------//
	Node<dataType>* getRear()const{ return rear; }  //获取队尾指针
	Node<dataType>* getFront()const { return front; }  //获取队首指针
	bool enQueue(const dataType tdat);  //入队
	bool deQueue(dataType &tdat);  //出队
	bool clrQueue();  //清空队列
	bool isEmpty()const { return length == 0; }  //判断是否为空
	bool isFull()const { return length == MaxUsrQueueSize; }  //判断是否为满
	int size()const { return length; }  //获取队列大小
};

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif //EN_NMSPACE_USR_DATASTRUCTURE

//------------------------------队列类的实现-------------------------------//
using namespace std;

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif //EN_NMSPACE_USR_DATASTRUCTURE

/** 公有方法实现------------------------------------------*/
template<class dataType>usrQueue<dataType>::
~usrQueue()  //析构函数实现
{
	clrQueue();
	front = nullptr; rear = nullptr;
}

//---------------队列表操作实现-----------------//
template<class dataType>bool usrQueue<dataType>::
enQueue(const dataType tdat)  //入队操作
{
	if (isFull())
	{
		//cout << "The Queue is Full!" << endl; 
		return false;
	}
	//在队尾插入结点
	Node<dataType> *l_ptrNode = new(Node<dataType>);
	if (!l_ptrNode)
		return false;
	memcpy(&(l_ptrNode->nodeDat), &tdat, sizeof(tdat));
	l_ptrNode->ptrNext = nullptr;
	if (rear == nullptr)  //插入第一个结点的处理
	{
		rear = l_ptrNode;
		front = rear;
	}
	else
	{
		rear->ptrNext = l_ptrNode; //连接结点
		rear = rear->ptrNext;   //转移结点
	}
	l_ptrNode = nullptr;  //放生指针，但不释放空间
	length += 1;
	return true;
}

template<class dataType>bool usrQueue<dataType>::
deQueue(dataType &tdat)  //出队操作
{
	if (isEmpty())
	{
		//cout << "The Queue is Empty!" << endl; 
		return false;
	}
	//在队首删除节点
	Node<dataType> *l_ptrNode = front;
	memcpy(&tdat, &l_ptrNode->nodeDat, sizeof(tdat));  //获取队首数据
	front = front->ptrNext;
	l_ptrNode->ptrNext = nullptr;   //断开连接
	delete l_ptrNode; l_ptrNode = nullptr;  //删除节点
	length -= 1;
	if (!length)
	{
		rear = nullptr;  //如果是最后一个元素，需要将最后的队尾指针置空
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