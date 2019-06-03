/**@file:     ��ջ��Ķ�����ʵ���ļ�
  *@Author��  T.H.
  *@function: 
	1-----��ջ����ջ
	2-----ջ�����ݻ�ȡ
	3-----�ж��Ƿ�Ϊ��ջ
	4-----�ж��Ƿ�Ϊ��ջ
  *@Version�� V1.3
  *@Note:     update-->v1.1 ��ӿɹ����̶����ȶ�ջ���ж϶�ջ�Ƿ���
			                �������ԣ�����ֵ����Ϊ �ڴ濽��
			 //��ʹ�ýṹ�����Ͷ�ջ������쳣�����ǿ��Խ��ṹ���дΪ��
			 //ʵ����Ӧ�Ĺ��ܣ���ô�ó�����������ز���
			 v1.2 ����ն�ջ��������Ϊpop()��������������ֱ�ӶԽ�����
			      ������˴����һ����
			 v1.3 ������ظ����ݵĶ�ջ��
			      ��Ӷ�ջ��������
*/

#pragma once

#ifndef __CPLUS_USRSTACK_H__
#define __CPLUS_USRSTACK_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "Node.h"
#include <iostream>

/** ˽�к�------------------------------------------------------------------------*/
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
	int length;    //ջ��С
	int MaxUsrStackSize;
	Node<dataType> *top;  //ջ����ջ��ָ��

public:
	//���캯��
	usrStack(int iszStack = 65535) :length(0), MaxUsrStackSize(iszStack), top(nullptr){};    
	virtual ~usrStack(){ clrStack(); }   //��������

	/** ���з���------------------------------------------*/
	int size() const{ return length; }  //���ȴ�1��ʼ��
	virtual bool push(const dataType tdat);    //��ջ
	bool pop(dataType &tdat);          //��ջ
	void clrStack();   //���ջ
	Node<dataType> *getTopNode() const{ return top; }  //��ȡջ��ָ��
	bool isFull() const{ return MaxUsrStackSize==length; }
	bool isEmpty() const{ return length == 0; };   //�ж϶�ջ�Ƿ�Ϊ��
	//�������ݵ�λ��---�� 1 ��ʼ����(ջ�����¼���)
	int getDataPos(const dataType t_stkData);
	/** Ӧ��---------------------------------------------*/
	void printStack() const;  //��ӡ����
};

template<typename dataType>
class usrStackUnique :public usrStack<dataType>    //���ظ����ݶ�ջ
{
public:
	usrStackUnique(int iszStack = 65535) :usrStack<dataType>(iszStack){}; //���캯��
	~usrStackUnique(){ clrStack(); }   //��������
	//ѹ�����ݣ��������Ƿ�����ظ�����,���������Ӧ�ĺ�����Ϊ�麯��������ʹ�� override
	bool push(const dataType tdat)override;  
};

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif


//---------------------------------��ջ���ʵ��---------------------------------//
using namespace std;

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif

/** ���з���ʵ��------------------------------------------*/
//��ջ����
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
	memcpy(&l_ptrNode->nodeDat, &tdat, sizeof(tdat));  //��߼�����
	l_ptrNode->ptrNext = top;
	top = l_ptrNode;
	length += 1;
	//�����ֲ�ָ�룬���ռ䲻�ͷ�
	l_ptrNode = nullptr;
	return true;
}
//��ջ����
template<class dataType>bool usrStack<dataType>::
pop(dataType &tdat)
{
	if (isEmpty())
	{
		//cout << "The Stack is Empty!" << endl; 
		return false;
	}
	//dataType retDat = top->nodeDat;
	memcpy(&tdat, &top->nodeDat, sizeof(tdat));  //��߼�����
	Node<dataType>* l_ptrNode = top;  //�ݴ潫Ҫɾ���ĵ�ַ
	top = top->ptrNext;  //�ƶ����
	l_ptrNode->ptrNext = nullptr;  //�Ͽ�����
	delete l_ptrNode;
	l_ptrNode = nullptr;  //�ض���Ұָ��
	length -= 1;
	return true;
}
//���ջ
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
	tmpStk.push(stkDataCache);  //ת��
	while ( memcmp(&stkDataCache, &t_stkData, sizeof(dataType)) )  //�Ƚ�
	{
		if (!this->pop(stkDataCache))
		{
			cnt = -1; break;
		}
		tmpStk.push(stkDataCache);  //ת��
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
	Node<dataType>* l_ptrNode = top; //���ڱ���
	for (int pos = length; pos >= 1; pos--)
	{
		cout << "��" << pos << "��Ԫ�� : ";
		cout << l_ptrNode->nodeDat << "  ";
		if (pos % 4 == 0)
			cout << endl;
		l_ptrNode = l_ptrNode->ptrNext;
	}
	cout << endl;
}

//------------------���ظ����ݶ�ջ���ʵ��--------------------//
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

