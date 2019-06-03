/**@file:     ��������ʵ���ļ�
  *@Author��  T.H.
  *@function:
  *@Version�� V1.0
  *@Note:     None
*/

/** �����ļ�----------------------------------------------------------------------*/
#include "bagSolver.h"
#include <iomanip>

/** ����ʵ��----------------------------------------------------------------------*/
//��ӡ����Ľ��
void printResult(usrStack<StackType>&t_Stack, const ElementType element[])
{
	usrStack<StackType>l_Stack;  //������ת����
	StackType stackTmp;
	int l_key = 0;
	cout << "number" << setw(10) << "name" << setw(10) \
		<< "place" << setw(10) << "weight" << endl;
	//��ת��ջ
	while (!t_Stack.isEmpty())
	{
		t_Stack.pop(stackTmp);
		l_key = stackTmp.index;
		cout << element[l_key].number\
			<< setw(10) << element[l_key].name\
			<< setw(10) << element[l_key].place\
			<< setw(10) << element[l_key].weight << endl;
		l_Stack.push(stackTmp);
	}
	//����������ѹ���ջ��
	while (!l_Stack.isEmpty())
	{
		l_Stack.pop(stackTmp);
		t_Stack.push(stackTmp);
	}
}
//��⺯��
//szElem �� 1��ʼ���㣬��ʾelement���������
void knapSack(const ElementType element[],const int szElem,const int t_totalWeight)
{
	usrStack<StackType>l_Stack;  //��������
	StackType stackTmp;
	int l_key = 0, //��������
		l_RemainW = t_totalWeight; //���ڱ��汳��ʣ������ 
	do 
	{
		while (l_RemainW>0 && l_key < szElem)
		{
			if (element[l_key].weight <= l_RemainW)
			{
				stackTmp.index = l_key;
				l_Stack.push(stackTmp);
				l_RemainW -= element[l_key].weight;
			}
			l_key++;
		}
		if (l_RemainW == 0) //�ҵ�һ����
			printResult(l_Stack, element);
		l_Stack.pop(stackTmp);//������һ������
		//�ָ���ǰ����ֵ--->
		//ע�����һ��Ҫʹ�øñ����лָ�
		//�������ⶨ��һ�������洢���������ֵ
		//����ָ�������ֵ����
		l_key = stackTmp.index;  
		l_RemainW += element[l_key].weight;//��������
		l_key++;
	} while (!l_Stack.isEmpty() || l_key < szElem);  
}

