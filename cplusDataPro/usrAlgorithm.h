/**@file:     �㷨���ʵ���ļ�
  *@Author��  T.H.
  *@Version�� V1.0
  *@Note:     �����㷨�����ڻ����������ͣ��㷨������
			  1.��������---------ʱ�临�Ӷ�O(n^2)���ռ临�Ӷ�O(1)���ȶ�����
			  2.�۰����������1�����
			  3.ϣ������---------ʱ�临�Ӷ�O(n(logn)^2)���ռ临�Ӷ�O(1)�����ȶ�����


			  �����㷨����:
			  1.���ֲ���
*/
#pragma once

#ifndef __USRALGORITHM_H__
#define __USRALGORITHM_H__
/** �����ļ�----------------------------------------------------------------------*/
#include <iostream>
using namespace std;

/** ˽�к�------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif //EN_NMSPACE_USR_DATASTRUCTURE

	/** �����㷨����---------------------------------------------------------*/

	template<typename elemType>void usrInsertSort(elemType Element[],const int szElem, \
		int sortBegin=1, int sortEnd=0);  //��������
	template<typename elemType>void usrBinInsertSort(elemType Element[], const int szElem, \
		int sortBegin=1,int sortEnd=0);
	//ϣ������--tspanΪ������
	template<typename elemType>void usrShellSort(elemType Element[], const int szElem, const int tspan); 
	template<typename elemType>	void usrBubSort(elemType Element[], const int szElem);  //ð������
	/** �����㷨����---------------------------------------------------------*/
	//���ֲ��ң�����������е����ݣ�tDat--���ҵ�����
	template<typename elemType>int usrBinSearch(const elemType Element[],const int szElem,const elemType tDat);  

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif //EN_NMSPACE_USR_DATASTRUCTURE

/** ���з�����ʵ��---------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif //EN_NMSPACE_USR_DATASTRUCTURE

/** �����㷨ʵ��-------------------------------------------------------------------------------------*/

/**
  @Func: ˳��ṹ�Ĳ�������
  @Para: Element--��������ڴ棬szElem--������ڴ��С
  @Note: ˼��-----���ڴ��еĵ�һ��Ԫ����Ϊ�Ѿ�����������ݣ�Ȼ��ڶ���Ԫ�غ͵�һ��Ԫ�رȽϣ�
  ����С��������ڵ�һ��֮ǰ��Ҳ���ǽ������ݣ������ϴ󣬾Ͳ��ı䣬
  ��������Ԫ����ǰ��Ԫ�����αȽϣ�����R(i-1)<Rj<Ri���������Ri֮ǰ��ͬʱ������Ri��Rj-1����������ƶ�
  ����ȫ��������ɣ����������
*/
template<typename elemType>void usrInsertSort(elemType Element[],const int szElem,int sortBegin,int sortEnd)
{
	elemType tmp;
	int i = 0, j = 0;
	if (sortEnd == 0)
		sortEnd = szElem - 1;
	for (i = sortBegin; i <= sortEnd; i++)
	{
		tmp = Element[i]; //������Ҫ���������
		for (j = i-1; j >= sortBegin&&Element[j]>tmp; j--)  //����������ƶ�
		{
			Element[j + 1] = Element[j];
		}
		Element[j + 1] = tmp;  //��������
	}
}
/**
  @Func: �۰��������
  @Para: Element--��������ڴ棬szElem--������ڴ��С
  sortBegin/sortEnd-��ʼ�����λ�ã������� 0 ��ʼ����
  @Note: ˼��-----��ֱ�Ӳ����������ƣ�ֻ���ڲ��Ҽ�������������
  ���Ҳ���λ��ʱ�����Ѿ�����������ݽ��ж԰���ң����ַ���
  eg: usrBinInsertSort(Element,szElem,1,3)---������Element���� 1--3 ��Ԫ�ؽ�������
*/
template<typename elemType>void usrBinInsertSort(elemType Element[],const int szElem,int sortBegin,int sortEnd) 
{
	elemType tmp;
	int startPos = 0, midPos = 0,endPos = 0;
	int i = 0, j = 0;
	if (sortEnd == 0)
		sortEnd = szElem-1;
	for (i = sortBegin; i <= sortEnd; i++)
	{
		startPos = sortBegin;
		endPos = i-1;
		tmp = Element[i];  //�ݴ�����������
		while (startPos <= endPos)  //��λ�����λ��--����R(i-1)<Rj<Ri
		{
			midPos = (startPos + endPos) / 2;
			if (Element[midPos] > tmp)
			{
				//��ǰ��
				endPos = midPos - 1;
			}
			else  //Ϊ���ȶ������� = Ҳ��������
			{
				//�����
				startPos = midPos + 1;
			}
		}
		for (j = i - 1; j > endPos; j--)  //�����������λ
		{
			Element[j + 1] = Element[j];
		}
		Element[j+1] = tmp;  //��������
	}
}

/**
  @Func: ϣ������
  @Para: Element--��������ڴ棬szElem--������ڴ��С��tspan----��ʾ�ʼ�ķ�������
  @Note: ˼��-----������������ݽ��ж�η��飬�������ڿ��Խ���ֱ�Ӳ�������Ҳ������������
		      ÿ�η���ĵ���������d(i+1)<di��Ϊ�˷���������� d(i+1) = di/2��
			  ֱ�� di=1 ����ʾ�������ݶ�����������
  @Exp:  ��Ϊ������ʵ��ʹ�õ��Ǻ������ã������ռ�úܶ����Դ
*/
template<typename elemType>void usrShellSort(elemType Element[], const int szElem,const int tspan)
{
	int span = tspan;
	int *dist = new int[szElem]();  //����ռ䲢��ʼ��Ϊ0
	int begin = 0, end = 0,cnt = 0;
	while (span >= 1)
	{
		//װ��Ԫ�ص� d ��
		for (int i = 0; i < span; i++)
		{
			begin = cnt;
			for (int j = i; j < szElem; j+=span)
			{
				dist[cnt++] = Element[j];
			}
			end = cnt-1;
			//�����ڽ���ֱ�Ӳ�������
			usrInsertSort(dist, szElem, begin, end);
		}
		//���¼��
		span = span / 2;
		cnt = 0;  //���¼�����
		//��������
		for (int cnt = 0; cnt < szElem; cnt++)
			Element[cnt] = dist[cnt];
	}
	delete[]dist; dist = nullptr;
}

/**
  @Func: ð������
  @Para: Element--��������ڴ棬szElem--������ڴ��С
  @Note: ˼��-----
  @Exp:  
*/
template<typename elemType>void usrBubSort(elemType Element[], const int szElem)
{

}



/** �����㷨ʵ��-------------------------------------------------------------------------------------*/

/**
  @Func�����ַ������㷨
  @Para: Element--���������ݵ��ڴ棬szElem--�ڴ��С��tdat--���ҵ�����
  @Ret : ���ز��ҵ������꣬�������ڣ����� -1
  @Note: ����������е�����---����ʹ�õݹ鷨��д
*/
template<typename elemType>int usrBinSearch(const elemType Element[],const int szElem,const elemType tDat)
{
	int curIndex = 0, retPos = -1;
	int startPos = 0, endPos = szElem-1;
	for(int i=startPos;i<=endPos;i++)
	{
		curIndex = (startPos + endPos )/ 2;
		if (Element[i] == tDat)
		{
			retPos = i; break;
		}
		if (Element[curIndex] > tDat)
		{
			//��ǰ����
			endPos = curIndex-1;
		}
		else if (Element[curIndex] < tDat)
		{
			//������
			startPos = curIndex + 1;
		}
		else
		{
			retPos = curIndex; break;
		}
	}
	return retPos;
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif //EN_NMSPACE_USR_DATASTRUCTURE

#endif //__USRALGORITHM_H__
