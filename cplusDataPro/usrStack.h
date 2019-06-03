/**@file:     堆栈类的定义与实现文件
  *@Author：  T.H.
  *@function: 
	1-----进栈、出栈
	2-----栈顶数据获取
	3-----判断是否为空栈
	4-----判断是否为满栈
  *@Version： V1.3
  *@Note:     update-->v1.1 添加可构建固定长度堆栈，判断堆栈是否满
			                提高灵活性，将赋值语句改为 内存拷贝
			 //在使用结构体类型堆栈会出现异常，但是可以将结构体改写为类
			 //实现相应的功能，那么该程序就能完成相关操作
			 v1.2 将清空堆栈函数更改为pop()操作处理，而不是直接对结点操作
			      这提高了处理的一致性
			 v1.3 添加无重复数据的堆栈类
			      添加堆栈数据搜索
*/

#pragma once

#ifndef __CPLUS_USRSTACK_H__
#define __CPLUS_USRSTACK_H__

/** 引入文件----------------------------------------------------------------------*/
#include "Node.h"
#include <iostream>

/** 私有宏------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
	#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE


#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif


template<class dataType>
class usrStack
{
private:
	int length;    //栈大小
	int MaxUsrStackSize;
	Node<dataType> *top;  //栈顶，栈底指针

public:
	//构造函数
	usrStack(int iszStack = 65535) :length(0), MaxUsrStackSize(iszStack), top(nullptr){};    
	virtual ~usrStack(){ clrStack(); }   //析构函数

	/** 公有方法------------------------------------------*/
	int size() const{ return length; }  //长度从1开始的
	virtual bool push(const dataType tdat);    //进栈
	bool pop(dataType &tdat);          //出栈
	void clrStack();   //清空栈
	Node<dataType> *getTopNode() const{ return top; }  //获取栈顶指针
	bool isFull() const{ return MaxUsrStackSize==length; }
	bool isEmpty() const{ return length == 0; };   //判断堆栈是否为空
	//返回数据的位置---从 1 开始计数(栈顶向下计算)
	int getDataPos(const dataType t_stkData);
	/** 应用---------------------------------------------*/
	void printStack() const;  //打印内容
};

template<typename dataType>
class usrStackUnique :public usrStack<dataType>    //无重复数据堆栈
{
public:
	usrStackUnique(int iszStack = 65535) :usrStack<dataType>(iszStack){}; //构造函数
	~usrStackUnique(){ clrStack(); }   //析构函数
	//压入数据，并会检测是否存在重复数据,基类中相对应的函数需为虚函数，才能使用 override
	bool push(const dataType tdat)override;  
};

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif


//---------------------------------堆栈类的实现---------------------------------//
using namespace std;

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif

/** 公有方法实现------------------------------------------*/
//进栈操作
template<class dataType>bool usrStack<dataType>::
push(const dataType tdat)
{
	if (isFull())
	{
		//cout << "The Stack is Full!" << endl; 
		return false;
	}
	Node<dataType>* l_ptrNode = new(Node<dataType>);
	//unique_ptr<Node<dataType>> l_ptrNode(new (Node<dataType>));
	if (l_ptrNode == nullptr)
		return false;
	memcpy(&l_ptrNode->nodeDat, &tdat, sizeof(tdat));  //提高兼容性
	l_ptrNode->ptrNext = top;
	top = l_ptrNode;
	length += 1;
	//放生局部指针，但空间不释放
	l_ptrNode = nullptr;
	return true;
}
//出栈操作
template<class dataType>bool usrStack<dataType>::
pop(dataType &tdat)
{
	if (isEmpty())
	{
		//cout << "The Stack is Empty!" << endl; 
		return false;
	}
	//dataType retDat = top->nodeDat;
	memcpy(&tdat, &top->nodeDat, sizeof(tdat));  //提高兼容性
	Node<dataType>* l_ptrNode = top;  //暂存将要删除的地址
	top = top->ptrNext;  //移动结点
	l_ptrNode->ptrNext = nullptr;  //断开连接
	delete l_ptrNode;
	l_ptrNode = nullptr;  //重定向野指针
	length -= 1;
	return true;
}
//清空栈
template<class dataType>void usrStack<dataType>::
clrStack()
{
	dataType l_cache;
	while (!isEmpty())
	{
		pop(l_cache);
	}
}
template<class dataType>int usrStack<dataType>::
getDataPos(const dataType t_stkData)
{
	int cnt = 1;
	usrStack<dataType>tmpStk;
	dataType stkDataCache;
	this->pop(stkDataCache);
	tmpStk.push(stkDataCache);  //转存
	while ( memcmp(&stkDataCache, &t_stkData, sizeof(dataType)) )  //比较
	{
		if (!this->pop(stkDataCache))
		{
			cnt = -1; break;
		}
		tmpStk.push(stkDataCache);  //转存
		cnt++;
	}
	while (!tmpStk.isEmpty())
	{
		tmpStk.pop(stkDataCache);
		this->push(stkDataCache);
	}
	return cnt;
}
template<class dataType>void usrStack<dataType>::
printStack() const
{
	Node<dataType>* l_ptrNode = top; //用于遍历
	for (int pos = length; pos >= 1; pos--)
	{
		cout << "第" << pos << "个元素 : ";
		cout << l_ptrNode->nodeDat << "  ";
		if (pos % 4 == 0)
			cout << endl;
		l_ptrNode = l_ptrNode->ptrNext;
	}
	cout << endl;
}

//------------------无重复数据堆栈类的实现--------------------//
template<class dataType>bool usrStackUnique<dataType>::
push(const dataType tdat)
{
	if (!isEmpty())
	{
		if (getDataPos(tdat) != -1)
			return false;
	}
	usrStack::push(tdat);
	return true;
}


#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif


#endif //__CPLUS_USRSTACK_H__

