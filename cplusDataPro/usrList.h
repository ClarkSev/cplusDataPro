/**@file:     ����������Ķ���ͷ�ļ�
  *@Author��  T.H.
  *@function: 1---�ڵ�ǰ�ڵ��������ݣ������ز���֮��Ľ���ַ
			  2---�ڵڼ���Ԫ�غ��������
			  3---ɾ������һ����ӦԪ�����ݲ����ص�ǰ���ָ��
			  4---��ȡ��������ĳ���
			  5---����������Ԫ�أ������������е�λ�ã����ᴫ��Ԫ�صĽ���ַ
			  6---��㿽������
			  7---�����������
			  8---�ж������Ƿ�Ϊ��
			  9---��ӡ�����е�����
			  10--����� = ����
			  11--�ƶ���㵽ָ��λ��
			  12--��������ʵ��
  *@Version�� V1.4
  *@Note:     1.3����--> �����ݱȶ��ʹ��memcmp�������бȽ�
              ���㳤��ʱ��ͷ������ݲ�������ڳ���֮��
			  ͷ�����������������������������
			  1.4����---> ����ͷ������������ݽ����뿪
*/

#pragma once

#ifndef __CPLUS_USRLIST_H__
#define __CPLUS_USRLIST_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "stdafx.h"
#include "Node.h"
#include <iostream>
#include <exception>

using namespace std;

/** ˽�к�------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE


#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif

/** ����������-----------------------------------------------------------*/
template<typename headType,typename nodeType = headType>
class usrList
{
private:
	/** ˽�б���-----------------------------------------------------------*/
	int length;
	HeadNode<headType,nodeType>  *headNode;  //��ͷ���
	Node<nodeType>               *lastNode;  //��βָ��
	//tbUpdLen---��ʾɾ���ڵ��Ƿ���� length ���� 
	Node<nodeType>               *delListNode(Node<nodeType>** tptr,bool tbUpdLen=true);
public:
	/** ���з���------------------------------------------------------------*/
	usrList();   //Ĭ�Ϲ��캯��
	usrList(const headType headDat);  //�������������ͷ�����������
	//usrList(int len=0);    //���캯��
	usrList(const usrList<headType,nodeType> &tslinerlist);  //��㸴�ƹ��캯��
	~usrList()//��������
	{
		clrLinerList();
	}
	/** ���Ա���� ----------------------------------------*/
	void clrLinerList();  //����������ݣ����ͷŽ��ָ��
	void clrLinerList(HeadNode<headType, nodeType>** theadNode);  //��̬
	//��㸴������
	usrList<headType, nodeType> &copy(const usrList<headType,nodeType> &tslinerlist);
	//�ڵ�ǰ���֮���������Ǳ�β����
	Node<nodeType> *insertAfter(const nodeType tdat,Node<nodeType> **tptr=nullptr);
	//�ڱ�ͷ������
	bool insertAfterHead(const nodeType tdat); 
	void setHeadVal(const headType tdat)//����ͷ�������
	{
		headNode = headNode->createHeadNode(tdat);
	};  
	//ɾ������һ����ӦԪ�����ݲ����ص�ǰ���ָ��
	Node<nodeType> *delListData(const nodeType tdat);
	//����tdat�������������е�һ�γ��ֵ�λ�ã���1����)
	//����tposPtrΪ�����ݵĽ���ַ
	int findData(const nodeType tdat, Node<nodeType> **tposPtr = nullptr);
	//��ȡ��datPos��λ�õ����ݣ�������tposPtrΪ��λ��ǰһ�����ĵ�ַ
	nodeType getPosData(const int datPos, Node<nodeType> **tposPtr=nullptr);

	//��λ��Ϊ pos(���ݴ� 1 ��ʼ����) ֮���������
	Node<nodeType> *insertPosAfter(const int pos,const nodeType tdat);

	/** �򵥵���������-------------------------------------*/
	HeadNode<headType,nodeType>* getHeadNode() const{ return headNode; }
	bool isEmpty(){ return length == 0; }  //��ʱֻ�б�ͷָ��
	int size()const { return length; } //��ȡ����

	/** ���������� ----------------------------------------*/
	//��㸳ֵ
	usrList<headType, nodeType> & operator =(const usrList<headType,nodeType> &t_slinerlist);

	/** ���Ա�Ӧ�� ----------------------------------------*/
	void printLinerList() const;   //��ӡ�����е�����
	//����datpos���������ƶ���pos��Ĭ��Ϊ��ͷ����
	bool moveNodeToPos(int datPos,int pos=1); 
	void inverseList(); //�������
};

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif

/** ��������ʵ���ļ�-----------------------------------------------------------*/

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif

//ɾ����ǰ������һ����������ɾ����ĵ�ǰ���ָ��
template<typename headType, typename nodeType = headType>
Node<nodeType>* usrList<headType,nodeType>::delListNode(Node<nodeType>** tptr,bool bUpdLen)
{
	//if (isEmpty())
	//	return nullptr;
	if (tptr == nullptr){
		return nullptr;
	}
	Node<nodeType>* l_ptrNode = (*tptr)->ptrNext;  //�ݴ��ַ
	if (l_ptrNode != nullptr)  //�ж��Ƿ�ɾ�����Ǳ�β���
	{
		(*tptr)->ptrNext = (*tptr)->ptrNext->ptrNext;  //�ƶ����
		l_ptrNode->ptrNext = nullptr;   //�Ͽ�����
	}
	else
	{
		l_ptrNode = (*tptr);
		*tptr = nullptr;
	}
	//lastNode = *tptr; //��ǰ�ƶ���βָ��
	delete l_ptrNode; //�ͷſռ�
	l_ptrNode = nullptr;
	if(bUpdLen)
		length -= 1;
	if (!(*tptr))
		return nullptr;
	return (*tptr)->ptrNext; //������һ�����ָ��
}

/** ���������๫�з�����ʵ��------------------------------------------------------*/
template<typename headType, typename nodeType = headType>usrList<headType,nodeType>::
usrList() :length(0)  //���캯��
{
	//ֻ��headNode ��new���ٵĿռ䣬��������ʱ��ֻ��Ҫdelete headNodeָ�����
	headNode = new (HeadNode<headType,nodeType>);
	//lastNode = headNode;   //�����βָ��
	lastNode = nullptr;  //�����βָ��
	headNode->ptrNext = lastNode;  //���ӽ��
}
template<typename headType, typename nodeType = headType>usrList<headType, nodeType>::
usrList(const headType headDat):length(0)  //�������������ͷ�����������
{
	//ֻ��headNode ��new���ٵĿռ䣬��������ʱ��ֻ��Ҫdelete headNodeָ�����
	headNode = new (HeadNode<headType,nodeType>);
	memcpy(&(headNode->nodeDat), &headDat, sizeof(headType));  //��������
	lastNode = nullptr;  //�����βָ��
	headNode->ptrNext = lastNode;  //���ӽ��
}
template<typename headType, typename nodeType = headType>usrList<headType,nodeType>::
usrList(const usrList<headType,nodeType> &tslinerlist)   //��㸴�ƹ��캯��
{
	this->copy(tslinerlist);  //��㸴�ƣ������ٿռ�
}
/** ���Ա���� --------------------------------------------*/
template<typename headType, typename nodeType = headType>void usrList<headType,nodeType>::
clrLinerList() //����������ݣ����ͷŽ��ָ��
{
	if (isEmpty())  //���Ϊ�գ���ȥ
		return;
	//�ӵ�һ����Ч��㿪ʼ����һ�����Ϊ��ͷ���֮��Ľ��
	Node<nodeType>* l_curNode = headNode->ptrNext;  
	while (!isEmpty())
	{
		delListNode(&l_curNode);  //�ͷŽ��
	}
	delete headNode;
	headNode = nullptr;  //�ص���ָ��
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
//��㸴������
template<typename headType, typename nodeType = headType>usrList<headType, nodeType>&\
usrList<headType,nodeType>::copy(const usrList &tslinerlist)
{
	if (!this->isEmpty())  //��Ϊ�ձ����������
		this->clrLinerList();
	//length = 0;
	headNode = new (HeadNode<headType,nodeType>); //�����¿ռ�
	memcpy(&(headNode->nodeDat), &(tslinerlist.headNode->nodeDat), sizeof(headType));  //��������
	//��������
	lastNode = nullptr;headNode->ptrNext = lastNode;

	//���ڱ���
	Node<nodeType>* l_ts_tmpPtrNode = tslinerlist.headNode->ptrNext;
	//�����ݸ��Ƶ��µ�������
	while(l_ts_tmpPtrNode)  //this->length��insetAfter�����л��Զ�����
	{
		insertAfter(l_ts_tmpPtrNode->nodeDat);
		l_ts_tmpPtrNode = l_ts_tmpPtrNode->ptrNext;
	}
	return *this;
}
#if  1
//�ڵ�ǰ���֮���������Ǳ�β������
template<typename headType, typename nodeType = headType>Node<nodeType>* \
usrList<headType,nodeType>::insertAfter(const nodeType tdat, Node<nodeType> **tptr)
{
	Node<nodeType>* l_ptrNode = new (Node<nodeType>);
	memcpy(&l_ptrNode->nodeDat, &tdat, sizeof(tdat));
	if (lastNode == nullptr)  //��ʾ��ǰΪ��һ���ڵ�
	{
		lastNode = l_ptrNode;
	}
	if (tptr == nullptr)
	{
		tptr = &lastNode;
	}
	if ((*tptr)->ptrNext != nullptr)
		l_ptrNode->ptrNext = (*tptr)->ptrNext;  //������ӽ��
	else
		l_ptrNode->ptrNext = nullptr;
	if (lastNode != l_ptrNode)  //������ǵ�һ���ڵ㣬�����Ӹ������
	{
		(*tptr)->ptrNext = l_ptrNode; // �ռ���������������ͷ�
		(*tptr) = (*tptr)->ptrNext;     //�ƶ���ǰָ��
	}
	else
		headNode->ptrNext = lastNode;  //���ǵ�һ���ڵ㣬�������ӵ�ͷ�����
	l_ptrNode = nullptr;       //�ռ䲢û���ͷţ�ֻ�ǽ���ָ���ͷ���
	length += 1;
	return (*tptr);  //���ص�ǰ���ָ��
}
#endif //0

//��ͷ���֮���������
template<typename headType, typename nodeType = headType>bool \
usrList<headType, nodeType>::insertAfterHead(const nodeType tdat)
{
	//�����������
	Node<nodeType>* l_ptrNode = new (Node<nodeType>);
	if (!l_ptrNode)
		return false;
	memcpy(&l_ptrNode->nodeDat, &tdat, sizeof(tdat));
	//�ƶ����
	l_ptrNode->ptrNext = headNode->ptrNext;  //���ӽ��
	headNode->ptrNext = l_ptrNode; //���뵽������
	l_ptrNode = nullptr;       //�ռ䲢û���ͷţ�ֻ�ǽ���ָ���ͷ���
	length += 1;
	return true;
}
//ɾ������һ����ӦԪ�����ݲ����ص�ǰ���ָ��
template<typename headType, typename nodeType = headType>
Node<nodeType>* usrList<headType,nodeType>::delListData(const nodeType tdat)
{
	if (isEmpty())  //�ձ�
		return nullptr;
	Node<nodeType> *l_ptrNode = headNode;
	findData(tdat, &l_ptrNode);  //��������
	if (l_ptrNode == nullptr)  //û���ҵ�����
		return nullptr;
	//�ҵ����ݣ���ɾ����Ӧ�Ľ��
	return delListNode(&l_ptrNode);
}
//����tdat�������������е�һ�γ��ֵ�λ��
//����tposPtrΪ�����ݵ�ǰһ������ַ
template<typename headType, typename nodeType = headType>
int usrList<headType,nodeType>::findData(const nodeType tdat, Node<nodeType> **tposPtr)
{
	Node<nodeType>* l_ptrNode = headNode->ptrNext; //���ڱ�������
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
	while (l_ptrNode->ptrNext)  //�ж��Ƿ�Ϊ��������
	{
		if (!memcmp(&l_ptrNode->nodeDat, &tdat, sizeof(tdat)))
		{
			if (tposPtr != nullptr)
				*tposPtr = l_ptrNode;
			return pos;
		}
		//����λ������
		l_ptrNode = l_ptrNode->ptrNext;
		pos++;
	}
	return (-1);
}
//��ȡ��datPos��λ�õ����ݣ�������tposPtrΪ��λ��ǰһ�����ĵ�ַ
template<typename headType, typename nodeType = headType>nodeType usrList<headType,nodeType>::
getPosData(const int datPos, Node<nodeType> **tposPtr)
{
	if (datPos <= 0 || length <= 0 || datPos>length)  //�������
		return static_cast<nodeType>(NULL);
	Node<nodeType>* l_ptrNode = headNode->ptrNext; //���ڱ�������
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

//��λ��Ϊ pos(���ݴ� 1 ��ʼ����) ֮���������
//�� pos=0 ��ʾ�ڱ�ͷ���������
template<typename headType, typename nodeType = headType>Node<nodeType>* \
usrList<headType,nodeType>::insertPosAfter(const int pos, const nodeType tdat)
{
	if (pos >= length)  //��β��������
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
/** ���������� ----------------------------------------*/

//��㸳ֵ
template<typename headType,typename nodeType=headType>usrList<headType,nodeType>&\
usrList<headType, nodeType>::operator =(const usrList<headType,nodeType> &t_slinerlist)
{
	this->copy(t_slinerlist);
	return *this;
}

/** ���Ա�Ӧ�� ----------------------------------------*/
//��ӡ�����е�����
template<typename headType, typename nodeType = headType>
void usrList<headType,nodeType>::printLinerList() const
{
	Node<nodeType>* l_ptrNode = headNode->ptrNext; //���ڱ���
	int pos = 1;
	while (l_ptrNode)
	{
		cout << "��" << pos << "��Ԫ�� : " << l_ptrNode->nodeDat << "  ";
		if (pos++ % 4 == 0)
			cout << endl;
		l_ptrNode = l_ptrNode->ptrNext;
	}
	cout << endl;
}
//����datpos���������ƶ���pos��Ĭ��Ϊ��ͷ����
template<typename headType, typename nodeType = headType>
bool usrList<headType,nodeType>::moveNodeToPos(int datPos, int pos)
{
	int minpos = (datPos > pos) ? pos : datPos;
	int maxpos = (datPos < pos) ? pos : datPos;
	datPos = minpos; pos = maxpos;
	if (length <= 0 || pos < 0 || datPos <= 0 || datPos>length)  //�ձ���������
		return false;
	if (datPos == pos)  //��㲻��Ҫ�ƶ�
		return true;
	Node<nodeType> *l_curNode = nullptr;
	if (datPos!=1)
	{
		getPosData(datPos, &l_curNode);  //��������
		if (l_curNode == nullptr)  //û���ҵ�����
			return false;
	}
	//�ҵ����ݣ���ɾ����Ӧ�Ľ�㣬�����ͷſռ�
	//���潫�ƶ��ĵ�ַ
	Node<nodeType> *l_ptrNode = (datPos==1)?(headNode->ptrNext):(l_curNode->ptrNext); 
	if (datPos == 1)  //�ƶ����
		headNode->ptrNext = l_ptrNode->ptrNext;
	else
		l_curNode->ptrNext = l_ptrNode->ptrNext; 
	getPosData(pos-1, &l_curNode);
	if (l_curNode == nullptr)  //û���ҵ�����
		return false;
	l_ptrNode->ptrNext = l_curNode->ptrNext; //�ƶ����
	l_curNode->ptrNext = l_ptrNode;
	return true;  //�ƶ����
}
//�������----ʹ��˫����ָ��ʵ�֣����Ӷ�Ϊ O(length)
template<typename headType, typename nodeType = headType>
void usrList<headType,nodeType>::inverseList()
{
	lastNode = headNode->ptrNext;  //���±�βָ��
	Node<nodeType> *l_tmpForntNode = headNode->ptrNext, *l_curNode;
	headNode->ptrNext = nullptr;  //�Ͽ�����
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