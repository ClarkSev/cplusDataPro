/**@file:     �㷨���ʵ���ļ�
  *@Author��  T.H.
  *@Version�� V1.0
  *@Note:     �����㷨�����ڻ����������ͣ��㷨������
		1.��������-----------ʱ�临�Ӷ�O(n^2)���ռ临�Ӷ�O(1)���ȶ�����
		2.�۰��������-------ʱ�临�Ӷ�O(nlogn)���ռ临�Ӷ�O(1)���ȶ�
		3.ϣ������-----------ʱ�临�Ӷ�O(n(logn)^2)���ռ临�Ӷ�O(1)�����ȶ�����
		4.ð������-----------ʱ�临�Ӷ�O(n^2)�����ȶ�����
		5.��������-----------ƽ��ʱ�临�Ӷ�O(nlogn)���ռ临�Ӷ�O(n)
							���ȶ�����Ŀǰƽ���ٶ����������㷨֮һ��
		6.ֱ��ѡ������-------��ð����������
		7.������-------------ʹ������������������ʱ�临�Ӷ�O(nlogn)
		8.��·�鲢����-------ʱ�临�Ӷ�O(nlogn)���ռ�O(1)���ȶ�����
		9.��������Ͱ����-ʱ�临�Ӷ�O(2mn)���ռ�O(dn)���ȶ�����
							����mΪ����λ����nΪ��������dΪ���ƣ���Ϊ10���ƣ�

		10.�ⲿ����----------����������--������ѡ�������㷨����

		�����㷨����:
		1.���ֲ���------��Ҫ�ȶ����ݽ�������
		2.�ֿ����------��Ҫ�����ݽ��зֿ飬����������
		3.��̬����------ƽ�������(AVL��--�����ƽ���㷨�ķ��������)���ҡ��������������usrClassifyBT��ʵ�֣���B����B+��
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

	/** �����㷨����һ����---------------------------------------------------------*/
	//��������
	template<typename elemType>void usrInsertSort(elemType Element[],const int szElem, \
		int sortBegin=1, int sortEnd=0);  
	template<typename elemType>void usrBinInsertSort(elemType Element[], const int szElem, \
		int sortBegin=1,int sortEnd=0);
	//ϣ������--tspanΪ������
	template<typename elemType>void usrShellSort(elemType Element[], const int szElem, const int tspan); 
	//ð������
	template<typename elemType>void usrBubSort(elemType Element[], const int szElem);  
	//���ŷ���
	template<typename elemType>int usrQuickSort_Partition(elemType Element[],int low,int high);
	template<typename elemType>void usrQuickSort(elemType Element[],const int sortBegin,const int sortEnd); //��������
	template<typename elemType>void usrQuickSort(elemType Element[], const int szElem);  //��̬---����������û��ӿ�

	//ֱ��ѡ������
	template<typename elemType>void usrSelectSort(elemType Element[], const int szElem);
	//������
	template<typename elemType>void usrHeapSort(elemType Element[], const int szElem);
	template<typename elemType>void usrInitMaxHeap(elemType Element[], const int szElem);
	template<typename elemType>bool usrDelHeapNode(elemType Element[], const int szElem, elemType &ret);

	//�鲢����
	template<typename elemType>void usrMergeSort(elemType Element[], const int szElem);
	//�鲢������������
	template<typename elemType>bool usrBinMerge(elemType Element[], elemType retElem[], const int szSort, const int szElem);

	//��������--�ֳ�Ͱ����
	void usrRadixSort(int Element[], const int szElem, const int bits);

	/** �����㷨����һ����---------------------------------------------------------*/
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
  @Note: ˼��-----ÿ����Ԫ�رȽϴ�С���ϴ�ͽ��н�������������ݽ��������棬
		 ����һ���������һ�����ݾ�������Ԫ�أ�ÿ����һ�Σ��Ϳ���ֻ��ǰn-i�����ݽ�������
		 ֱ�����е�����������ɡ�
  @Exp:  
*/
template<typename elemType>void usrBubSort(elemType Element[], const int szElem)
{
	bool change = true;  //����Ƿ������ݽ���
	int i = 0, j = szElem;
	elemType tmp;
	while (j > 0&&change)
	{
		change = false;
		for (i = 0; i < j-1; i++)
		{
			if (Element[i] > Element[i + 1])
			{
				tmp = Element[i + 1];
				Element[i + 1] = Element[i];
				Element[i] = tmp;
				change = true;
			}
		}
		j--;
	}
}

/**
  @Func����������
  @Para��Element--��������ڴ棬szElem--������ڴ��С
		 sortBegin--�������ʼ������������ sortEnd----����Ľ���������������

  @Note��˼��-----�ڴ�������Ǹ���¼������ѡȡһ����¼Ri��Ϊ��׼�����������и�����¼��λ�ã�
          ʹ����Riǰ��ļ�¼��С��Ri������Ri����ļ�¼�����ڵ���Ri�����ǰ�������һ�����̳���һ�ο�������
		  ��һ�ο���֮��ȷ����Ri������λ�ã�ͬʱ��ʣ�µļ�¼��Ϊ���������С��������������зֱ���п��ţ�
		  ����ظ���ȥ����ÿ�������еĳ���Ϊ1ʱ��ȫ����¼������ɡ�
*/
template<typename elemType>void usrQuickSort(elemType Element[], const int sortBegin,const int sortEnd)
{
	int local = 0;
	if (sortBegin < sortEnd)
	{
		local = usrQuickSort_Partition(Element, sortBegin, sortEnd);
		usrQuickSort(Element, sortBegin, local - 1);//����ߵĽ�������
		usrQuickSort(Element, local+1, sortEnd);//���ұߵĽ�������
	}
}
template<typename elemType>void usrQuickSort(elemType Element[], const int szElem)
{
	usrQuickSort(Element, 0, szElem - 1);
}
//���ŵķ��麯���������ض�λ��
//���ص�----�����λ���麯��--˼��ܺ�
template<typename elemType>int usrQuickSort_Partition(elemType Element[],int low,int high)
{
	elemType tmp = Element[low];
	while (low<high)
	{
		while (low < high&&Element[high] >= tmp)
			high--;
		if (low < high)
			Element[low++] = Element[high];
		while (low < high&&Element[low] < tmp)  
			low++;
		if (low < high)
			Element[high--] = Element[low];
	}
	Element[low] = tmp;
	return low;
}
/**
  @Func��ֱ��ѡ������
  @Para��Element--��������ڴ棬szElem--������ڴ��С
  @Note��˼��-----��ð�������࣬ð�������ǽ���Ľ��������棬
				������ֱ��ѡ��С�ļ�¼����������ǰ�棬Ȼ��ֻ�Ժ������ݽ�������
*/
template<typename elemType>void usrSelectSort(elemType Element[], const int szElem)
{
	int i = 0, j = 0, minIndex = 0;
	elemType tmp;
	for (i = 0; i < szElem; i++)
	{
		minIndex = i;
		for (j = i + 1; j < szElem; j++)
		{
			if (Element[minIndex] > Element[j])
				minIndex = j;
		}
		//��������
		if (minIndex != i)
		{
			tmp = Element[i];
			Element[i] = Element[minIndex];
			Element[minIndex] = tmp;
		}
	}
}
/**
  @Func��������
  @Para��Element--��������ڴ棬szElem--������ڴ��С
  @Note��˼��-----�Ƚ�������ȫ������(������˳��ṹ)��ʼ��Ϊ������
				Ȼ��Ӹ���㿪ʼɾ���ڵ㣬�ڵ㲢����������ɾ�������ǽ�������ݱ��������
				���������ȫ��ɾ��ʱ�����������

  @Attd����Ҫע�⣬�ڴ��㷨������ʹ�õ���˳��洢�����ṹ����Ϊͨ���������������ĺ��ӻ���˫�׽��ʱ��
		 ʹ�����������˼��㣬�������ݵ� 0 ����ֵ���ã��� 1 ��ʼ���㡣
				
*/
template<typename elemType>void usrHeapSort(elemType Element[], const int szElem)
{
	elemType tmp;
	//����ռ�
	elemType *cache = new elemType[szElem+1]();
	//�����ݴ���ռ���,���ҽ�cache[0]��Ϊ��ʱ�洢�������洢Element����
	memcpy(cache + 1, Element, sizeof(elemType)*szElem);
	//������ת��Ϊ������
	usrInitMaxHeap(cache, szElem + 1);
	for (int i = szElem; i > 0; i--)
	{
		usrDelHeapNode(cache, i + 1, tmp);
		Element[i - 1] = tmp;  //��ɾ���ĸ�������Ԫ�����
	}
	delete[]cache; cache = nullptr;
}
//��ʼ��������
//Element----�ڴ���Element[0]��Ϊ��ʱ�����������洢Element����
//szElem-----������ 0 ������ֵ(0....szElem)
template<typename elemType>void usrInitMaxHeap(elemType Element[], const int szElem)
{
	int szData = szElem - 1;
	for (int parent = szData / 2; parent > 0; parent--)
	{
		Element[0] = Element[parent];
		int son = parent * 2;
		while (son <= szData)
		{
			if (son < szData)  //ѡ������ӽ��
				if (Element[son] < Element[son + 1])
					son++;
			if (Element[0] > Element[son])  //
				 break;
			Element[son / 2] = Element[son]; //���ӽ�������ƣ�Ҳ�����滻�ĸ�ĸ���һֱ�����ƣ�ֱ����������
			son = son * 2;
		}
		Element[son/2] = Element[0];
	}
}
//ɾ�����ڵ㣬�����䱣�������----��ɾ�����߹���Ϊ��ȫ������
//Element----�ڴ���Element[0]��Ϊ��ʱ�����������洢Element����
//szElem-----������ 0 ������ֵ(0...szElem)
//ret--------ɾ���Ľ��Ԫ��
template<typename elemType>bool usrDelHeapNode(elemType Element[], const int szElem, elemType &ret)
{
	//����ռ�
	if (szElem == 0)return false;
	int son = 2,parent=1,
		szCache = szElem - 1;
	ret = Element[1];
	Element[0] = Element[szCache--];  //���浱ǰ���Ҷ�ӵ����ݣ������½����
	while (son<= szCache)
	{
		if(son<szCache)
			if (Element[son] < Element[son + 1])
				son++;
		if (Element[0] > Element[son])
			break;
		Element[parent] = Element[son];  //����ĺ��ӽ�������ƣ���Ƴ��ĸ�ĸ����ȱ
		parent = son;
		son = son * 2;
	}
	Element[parent] = Element[0];
	return true;
}

/**
  @Func����·�鲢����
  @Para��Element--��������ڴ棬szElem--������ڴ��С
  @Note��˼��-----����n����¼��ԭʼ���п���n�����������У�ÿ�������еĳ���Ϊ1��
    Ȼ��ӵ�һ�������п�ʼ�������ڵ������������ϲ��õ�n/2������Ϊ2����1 ��������
    ��������Ϊ����ʱ�����һ������ 1 �������У������ǽ����Ϊһ�ι鲢����
    �ٴ��ظ�������ֱ������Ϊ n ��һ��������
*/
template<typename elemType>void usrMergeSort(elemType Element[], const int szElem)
{
	int cnt = 1;
	int *elemCache = new int[szElem]();
	bool state = false;
	while (cnt < szElem)
	{
		if (!usrBinMerge(Element, elemCache, cnt, szElem)) { state = true;break; }
		cnt <<= 1;  //cnt*=2;
		if (!usrBinMerge(elemCache, Element, cnt, szElem)) { state = false;break; }
		cnt <<= 1;
	}
	if (state)
		memcpy_s(Element, szElem * sizeof(elemType), elemCache, szElem * sizeof(elemType));
	delete[]elemCache; elemCache = nullptr;
}
//Func:��Element�е�Ԫ�ط�ΪnGrp=szElem/szSort ���飬�������������һ�ι鲢����Ȼ�����reElem��
//Element---��������     retElem---��������
//szSort----����Ԫ�ظ��� szElem----��Ԫ����Ŀ
template<typename elemType>bool usrBinMerge(elemType Element[],elemType retElem[], const int szSort,const int szElem)
{
	//int nGroup = szElem / szSort;
	int low1 = 0,low2=0, high1 = 0,high2=0, sp = 0;
	if (szSort > szElem)return false;
	while (sp < szElem)
	{
		//��������
		low1 = sp;
		low2 = low1+szSort;
		high2 = low2 + szSort - 1;
		high1 = low2 - 1;
		//sp = low;
		if (high2 >= szElem)high2 = szElem-1;
		if (low2 >= szElem)low2 = szElem - 1;
		//���н�������
		while (low1<=high1&&low2<=high2)
		{
			if (Element[low1] < Element[low2])
				retElem[sp++] = Element[low1++];
			else
				retElem[sp++] = Element[low2++];
		}
		//��û��ƥ�������д��retElem��
		while (low1<=high1&&sp<szElem)   //������1�����ݴ���
			retElem[sp++] = Element[low1++];
		while (low2 <= high2&&sp<szElem) //������1�����ݴ���
			retElem[sp++] = Element[low2++];
	}
	return true;
}

/**
	@Func�����������ֳ�Ͱ����---�ǰ��ռ�¼�ؼ�����ɵĸ�λֵ������������һ�з���
	@Para��Element--��������ڴ棬szElem--������ڴ��С
		   radix----�������Ľ��ƣ�bits--�����������λ��
	@Note��˼��----���ؼ��ֵ�ĳһλ��ɷ��ŷ���������ٸ��ݷ��������ÿ���������ʣ������Ŷ�Ӧ�Ĺؼ���
	���䵽��Ӧ��ͬ�֣������м�¼�Ĺؼ��ֶ�����������������ٽ����е�����һ���Ѽ���һ���ٴν�����һ������

	��ϸ���裺����¼�Ĺؼ�����mΪd������������mλ�Ĺټ����ڸ�λ��0�����ڽ��л�������ʱ������d��Ͱ��Ͱ�ĸ�����ؼ���
	�Ľ����йأ��������ŷֱ�Ϊ0��1��...��d-1�����Ƚ������и�����¼������ؼ������λֵ�Ĵ�С���õ���Ӧ��Ͱ�У�
	Ȼ����ǰ����ͬ�ķ����ٴ��ռ���Ͱ�еļ�¼�������µļ�¼����.....����ظ����У�������˶������еĸ�����¼����ؼ���
	�����λֵ���з��ú��ռ�����������m�λ�����������õ��ļ�¼���о���ԭʼ���е���������

	���㷨ֻ���������
*/
void usrRadixSort(int Element[],const int szElem,const int bits)
{
	//����Ͱ--Ͱ��СΪ d*n �Ķ�ά����
	int **pail = new int*[10];
	int cntPail[10] = {0};  //Ͱ������Ԫ�ظ���
	for (int i = 0; i < szElem; i++)
		pail[i] = new int[szElem]();   //��ʼ������
	int num = bits,exp = 1,idx = 0;
	while (num--)  //num���Ѽ������
	{
		//��������
		for (int k = 0; k < szElem; k++)
		{
			int tmp = ( Element[k]%(exp*10) - Element[k]%exp ) /exp;  //��������
			pail[tmp][cntPail[tmp]] = Element[k];
			cntPail[tmp]++;
		}
		//�Ѽ�����
		idx = 0;
		for (int i = 0; i < 10; i++)
		{
			if (cntPail[i] != 0)
			{
				for (int j = 0; j<cntPail[i]; j++)
				{
					Element[idx++] = pail[i][j];
				}
				cntPail[i] = 0;   //���Ͱ�����ݼ�����
			}
		}
		exp *= 10;
	}
	//�ͷſռ�
	for(int i=0;i<szElem;i++)
	{
		delete[]pail[i]; pail[i] = nullptr;
	}
	delete[]pail; pail = nullptr;
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
