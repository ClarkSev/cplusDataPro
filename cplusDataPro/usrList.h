/**@file:     单向链表类的定义头文件
  *@Author：  T.H.
  *@function: 1---在当前节点后插入数据，并返回插入之后的结点地址
			  2---在第几个元素后插入数据
			  3---删除表中一个对应元素数据并返回当前结点指针
			  4---获取整个链表的长度
			  5---查找链表中元素，返回在链表中的位置，并会传回元素的结点地址
			  6---深层拷贝链表
			  7---清空整个链表
			  8---判断链表是否为空
			  9---打印链表中的数据
			  10--运算符 = 重载
			  11--移动结点到指定位置
			  12--链表逆序实现
  *@Version： V1.4
  *@Note:     1.3更新--> 将数据比对项，使用memcmp函数进行比较
              计算长度时，头结点数据不会计算在长度之中
			  头结点的数据与其他结点数据有所区别
			  1.4更新---> 将表头结点与其他数据结点分离开
*/

#pragma once

#ifndef __CPLUS_USRLIST_H__
#define __CPLUS_USRLIST_H__

/** 引入文件----------------------------------------------------------------------*/
#include "stdafx.h"
#include "Node.h"
#include <iostream>
#include <exception>

using namespace std;

/** 私有宏------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE


#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif

/** 单向链表定义-----------------------------------------------------------*/
template<typename headType,typename nodeType = headType>
class usrList
{
private:
	/** 私有变量-----------------------------------------------------------*/
	int length;
	HeadNode<headType,nodeType>  *headNode;  //表头结点
	Node<nodeType>               *lastNode;  //表尾指针
	//tbUpdLen---表示删除节点是否更新 length 属性 
	Node<nodeType>               *delListNode(Node<nodeType>** tptr,bool tbUpdLen=true);
public:
	/** 公有方法------------------------------------------------------------*/
	usrList();   //默认构造函数
	usrList(const headType headDat);  //构建链表，将其表头数据载入表中
	//usrList(int len=0);    //构造函数
	usrList(const usrList<headType,nodeType> &tslinerlist);  //深层复制构造函数
	~usrList()//析构函数
	{
		clrLinerList();
	}
	/** 线性表操作 ----------------------------------------*/
	void clrLinerList();  //清空链表数据，并释放结点指针
	void clrLinerList(HeadNode<headType, nodeType>** theadNode);  //多态
	//深层复制链表
	usrList<headType, nodeType> &copy(const usrList<headType,nodeType> &tslinerlist);
	//在当前结点之后插入结点或是表尾插入
	Node<nodeType> *insertAfter(const nodeType tdat,Node<nodeType> **tptr=nullptr);
	//在表头结点插入
	bool insertAfterHead(const nodeType tdat); 
	void setHeadVal(const headType tdat)//设置头结点数据
	{
		headNode = headNode->createHeadNode(tdat);
	};  
	//删除表中一个对应元素数据并返回当前结点指针
	Node<nodeType> *delListData(const nodeType tdat);
	//查找tdat的数据在链表中第一次出现的位置（从1计算)
	//其中tposPtr为该数据的结点地址
	int findData(const nodeType tdat, Node<nodeType> **tposPtr = nullptr);
	//获取第datPos个位置的数据，并设置tposPtr为该位置前一个结点的地址
	nodeType getPosData(const int datPos, Node<nodeType> **tposPtr=nullptr);

	//在位置为 pos(数据从 1 开始计算) 之后插入数据
	Node<nodeType> *insertPosAfter(const int pos,const nodeType tdat);

	/** 简单的内联函数-------------------------------------*/
	HeadNode<headType,nodeType>* getHeadNode() const{ return headNode; }
	bool isEmpty(){ return length == 0; }  //此时只有表头指针
	int size()const { return length; } //获取长度

	/** 操作符重载 ----------------------------------------*/
	//深层赋值
	usrList<headType, nodeType> & operator =(const usrList<headType,nodeType> &t_slinerlist);

	/** 线性表应用 ----------------------------------------*/
	void printLinerList() const;   //打印链表中的内容
	//将第datpos个的数据移动到pos（默认为表头）处
	bool moveNodeToPos(int datPos,int pos=1); 
	void inverseList(); //逆序操作
};

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif

/** 单向链表实现文件-----------------------------------------------------------*/

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif

//删除当前结点的下一个，并返回删除后的当前结点指针
template<typename headType, typename nodeType = headType>
Node<nodeType>* usrList<headType,nodeType>::delListNode(Node<nodeType>** tptr,bool bUpdLen)
{
	//if (isEmpty())
	//	return nullptr;
	if (tptr == nullptr){
		return nullptr;
	}
	Node<nodeType>* l_ptrNode = (*tptr)->ptrNext;  //暂存地址
	if (l_ptrNode != nullptr)  //判断是否删除的是表尾结点
	{
		(*tptr)->ptrNext = (*tptr)->ptrNext->ptrNext;  //移动结点
		l_ptrNode->ptrNext = nullptr;   //断开连接
	}
	else
	{
		l_ptrNode = (*tptr);
		*tptr = nullptr;
	}
	//lastNode = *tptr; //向前移动表尾指针
	delete l_ptrNode; //释放空间
	l_ptrNode = nullptr;
	if(bUpdLen)
		length -= 1;
	if (!(*tptr))
		return nullptr;
	return (*tptr)->ptrNext; //返回下一个结点指针
}

/** 单向链表类公有方法的实现------------------------------------------------------*/
template<typename headType, typename nodeType = headType>usrList<headType,nodeType>::
usrList() :length(0)  //构造函数
{
	//只有headNode 是new开辟的空间，所以析构时，只需要delete headNode指针就行
	headNode = new (HeadNode<headType,nodeType>);
	//lastNode = headNode;   //链表表尾指针
	lastNode = nullptr;  //链表表尾指针
	headNode->ptrNext = lastNode;  //连接结点
}
template<typename headType, typename nodeType = headType>usrList<headType, nodeType>::
usrList(const headType headDat):length(0)  //构建链表，将其表头数据载入表中
{
	//只有headNode 是new开辟的空间，所以析构时，只需要delete headNode指针就行
	headNode = new (HeadNode<headType,nodeType>);
	memcpy(&(headNode->nodeDat), &headDat, sizeof(headType));  //加载数据
	lastNode = nullptr;  //链表表尾指针
	headNode->ptrNext = lastNode;  //连接结点
}
template<typename headType, typename nodeType = headType>usrList<headType,nodeType>::
usrList(const usrList<headType,nodeType> &tslinerlist)   //深层复制构造函数
{
	this->copy(tslinerlist);  //深层复制，会另开辟空间
}
/** 线性表操作 --------------------------------------------*/
template<typename headType, typename nodeType = headType>void usrList<headType,nodeType>::
clrLinerList() //清空链表数据，并释放结点指针
{
	if (isEmpty())  //如果为空，退去
		return;
	//从第一个有效结点开始，第一个结点为表头结点之后的结点
	Node<nodeType>* l_curNode = headNode->ptrNext;  
	while (!isEmpty())
	{
		delListNode(&l_curNode);  //释放结点
	}
	delete headNode;
	headNode = nullptr;  //重导向指针
	lastNode = nullptr;
}
template<typename headType, typename nodeType = headType>
void clrLinerList(HeadNode<headType, nodeType> **theadNode)
{
	if (!theadNode)
		return;
	Node<nodeType> *lptrNode = (*theadNode)->ptrNext;
	while (lptrNode)
	{
		delListNode(&lptrNode,false);
		lptrNode = lptrNode->ptrNext;
	}
	delete (*theadNode); *theadNode = nullptr;
}
//深层复制链表
template<typename headType, typename nodeType = headType>usrList<headType, nodeType>&\
usrList<headType,nodeType>::copy(const usrList &tslinerlist)
{
	if (!this->isEmpty())  //不为空表，则清空链表
		this->clrLinerList();
	//length = 0;
	headNode = new (HeadNode<headType,nodeType>); //开辟新空间
	memcpy(&(headNode->nodeDat), &(tslinerlist.headNode->nodeDat), sizeof(headType));  //加载数据
	//更新数据
	lastNode = nullptr;headNode->ptrNext = lastNode;

	//用于遍历
	Node<nodeType>* l_ts_tmpPtrNode = tslinerlist.headNode->ptrNext;
	//将数据复制到新的链表中
	while(l_ts_tmpPtrNode)  //this->length在insetAfter函数中会自动更新
	{
		insertAfter(l_ts_tmpPtrNode->nodeDat);
		l_ts_tmpPtrNode = l_ts_tmpPtrNode->ptrNext;
	}
	return *this;
}
#if  1
//在当前结点之后插入结点或是表尾结点插入
template<typename headType, typename nodeType = headType>Node<nodeType>* \
usrList<headType,nodeType>::insertAfter(const nodeType tdat, Node<nodeType> **tptr)
{
	Node<nodeType>* l_ptrNode = new (Node<nodeType>);
	memcpy(&l_ptrNode->nodeDat, &tdat, sizeof(tdat));
	if (lastNode == nullptr)  //表示当前为第一个节点
	{
		lastNode = l_ptrNode;
	}
	if (tptr == nullptr)
	{
		tptr = &lastNode;
	}
	if ((*tptr)->ptrNext != nullptr)
		l_ptrNode->ptrNext = (*tptr)->ptrNext;  //向后连接结点
	else
		l_ptrNode->ptrNext = nullptr;
	if (lastNode != l_ptrNode)  //如果不是第一个节点，就连接各个结点
	{
		(*tptr)->ptrNext = l_ptrNode; // 空间会在析构函数中释放
		(*tptr) = (*tptr)->ptrNext;     //移动当前指针
	}
	else
		headNode->ptrNext = lastNode;  //若是第一个节点，将其连接到头结点上
	l_ptrNode = nullptr;       //空间并没有释放，只是将该指针释放了
	length += 1;
	return (*tptr);  //返回当前结点指针
}
#endif //0

//表头结点之后插入数据
template<typename headType, typename nodeType = headType>bool \
usrList<headType, nodeType>::insertAfterHead(const nodeType tdat)
{
	//产生结点数据
	Node<nodeType>* l_ptrNode = new (Node<nodeType>);
	if (!l_ptrNode)
		return false;
	memcpy(&l_ptrNode->nodeDat, &tdat, sizeof(tdat));
	//移动结点
	l_ptrNode->ptrNext = headNode->ptrNext;  //连接结点
	headNode->ptrNext = l_ptrNode; //插入到链表中
	l_ptrNode = nullptr;       //空间并没有释放，只是将该指针释放了
	length += 1;
	return true;
}
//删除表中一个对应元素数据并返回当前结点指针
template<typename headType, typename nodeType = headType>
Node<nodeType>* usrList<headType,nodeType>::delListData(const nodeType tdat)
{
	if (isEmpty())  //空表
		return nullptr;
	Node<nodeType> *l_ptrNode = headNode;
	findData(tdat, &l_ptrNode);  //查找数据
	if (l_ptrNode == nullptr)  //没有找到数据
		return nullptr;
	//找到数据，则删除相应的结点
	return delListNode(&l_ptrNode);
}
//查找tdat的数据在链表中第一次出现的位置
//其中tposPtr为该数据的前一个结点地址
template<typename headType, typename nodeType = headType>
int usrList<headType,nodeType>::findData(const nodeType tdat, Node<nodeType> **tposPtr)
{
	Node<nodeType>* l_ptrNode = headNode->ptrNext; //用于遍历数据
	int pos = 1;
	if (isEmpty())
		return (-1);
	if (size() == 1)
	{
		if (!memcmp(&l_ptrNode->nodeDat, &tdat, sizeof(tdat)))
		{
			if (tposPtr != nullptr)
				*tposPtr = l_ptrNode;
			return 1;
		}
		else
		{
			if (tposPtr != nullptr)
				*tposPtr = nullptr;
			return(-1);
		}
	}
	while (l_ptrNode->ptrNext)  //判断是否为最后的数据
	{
		if (!memcmp(&l_ptrNode->nodeDat, &tdat, sizeof(tdat)))
		{
			if (tposPtr != nullptr)
				*tposPtr = l_ptrNode;
			return pos;
		}
		//更新位置数据
		l_ptrNode = l_ptrNode->ptrNext;
		pos++;
	}
	return (-1);
}
//获取第datPos个位置的数据，并设置tposPtr为该位置前一个结点的地址
template<typename headType, typename nodeType = headType>nodeType usrList<headType,nodeType>::
getPosData(const int datPos, Node<nodeType> **tposPtr)
{
	if (datPos <= 0 || length <= 0 || datPos>length)  //参数检查
		return static_cast<nodeType>(NULL);
	Node<nodeType>* l_ptrNode = headNode->ptrNext; //用于遍历数据
	int l_pos = 0;
	while (l_pos++ < datPos - 1 && l_ptrNode != nullptr)
	{
		l_ptrNode = l_ptrNode->ptrNext;
	}
	if (l_ptrNode == nullptr)
	{
		*tposPtr = nullptr;
		return static_cast<nodeType>(NULL);
	}
	if (tposPtr != nullptr)
	{
		*tposPtr = l_ptrNode;
	}
	return l_ptrNode->nodeDat;
}

//在位置为 pos(数据从 1 开始计算) 之后插入数据
//若 pos=0 表示在表头后插入数据
template<typename headType, typename nodeType = headType>Node<nodeType>* \
usrList<headType,nodeType>::insertPosAfter(const int pos, const nodeType tdat)
{
	if (pos >= length)  //表尾插入数据
	{
		return insertAfter(tdat);
	}
	int l_tpos = 1;
	Node<nodeType>* l_ptrNode = headNode->ptrNext;
	while (l_tpos != pos)
	{
		l_ptrNode = l_ptrNode->ptrNext;
		l_tpos++;
	}
	return insertAfter(tdat, &l_ptrNode);
}
/** 操作符重载 ----------------------------------------*/

//深层赋值
template<typename headType,typename nodeType=headType>usrList<headType,nodeType>&\
usrList<headType, nodeType>::operator =(const usrList<headType,nodeType> &t_slinerlist)
{
	this->copy(t_slinerlist);
	return *this;
}

/** 线性表应用 ----------------------------------------*/
//打印链表中的内容
template<typename headType, typename nodeType = headType>
void usrList<headType,nodeType>::printLinerList() const
{
	Node<nodeType>* l_ptrNode = headNode->ptrNext; //用于遍历
	int pos = 1;
	while (l_ptrNode)
	{
		cout << "第" << pos << "个元素 : " << l_ptrNode->nodeDat << "  ";
		if (pos++ % 4 == 0)
			cout << endl;
		l_ptrNode = l_ptrNode->ptrNext;
	}
	cout << endl;
}
//将第datpos个的数据移动到pos（默认为表头）处
template<typename headType, typename nodeType = headType>
bool usrList<headType,nodeType>::moveNodeToPos(int datPos, int pos)
{
	int minpos = (datPos > pos) ? pos : datPos;
	int maxpos = (datPos < pos) ? pos : datPos;
	datPos = minpos; pos = maxpos;
	if (length <= 0 || pos < 0 || datPos <= 0 || datPos>length)  //空表或参数错误
		return false;
	if (datPos == pos)  //结点不需要移动
		return true;
	Node<nodeType> *l_curNode = nullptr;
	if (datPos!=1)
	{
		getPosData(datPos, &l_curNode);  //查找数据
		if (l_curNode == nullptr)  //没有找到数据
			return false;
	}
	//找到数据，则删除相应的结点，不会释放空间
	//储存将移动的地址
	Node<nodeType> *l_ptrNode = (datPos==1)?(headNode->ptrNext):(l_curNode->ptrNext); 
	if (datPos == 1)  //移动结点
		headNode->ptrNext = l_ptrNode->ptrNext;
	else
		l_curNode->ptrNext = l_ptrNode->ptrNext; 
	getPosData(pos-1, &l_curNode);
	if (l_curNode == nullptr)  //没有找到数据
		return false;
	l_ptrNode->ptrNext = l_curNode->ptrNext; //移动结点
	l_curNode->ptrNext = l_ptrNode;
	return true;  //移动完成
}
//逆序操作----使用双缓存指针实现，复杂度为 O(length)
template<typename headType, typename nodeType = headType>
void usrList<headType,nodeType>::inverseList()
{
	lastNode = headNode->ptrNext;  //更新表尾指针
	Node<nodeType> *l_tmpForntNode = headNode->ptrNext, *l_curNode;
	headNode->ptrNext = nullptr;  //断开连接
	while (l_tmpForntNode != nullptr)
	{
		l_curNode = l_tmpForntNode;
		l_tmpForntNode = l_tmpForntNode->ptrNext;
		l_curNode->ptrNext = headNode->ptrNext;
		headNode->ptrNext = l_curNode;
	}
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif


#endif  //__CPLUS_USRLIST_H__