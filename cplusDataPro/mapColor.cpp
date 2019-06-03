/**@file:     ��ͼ��Ⱦɫ����ʵ���ļ�
  *@Author��  T.H.
  *@function:
  *@Version�� V1.0
  *@Note:     None
*/

/** �����ļ�----------------------------------------------------------------------*/
#include "mapColor.h"

/** ����ʵ��----------------------------------------------------------------------*/
////���հ׵�ͼ���������ɫ������Ⱦɫ��ϴ�ӡ����
void printSolver(mapElementType tmap[], usrStack<mapStackType>&stkMap)
{
	usrStack<mapStackType>l_stk;
	mapStackType t_stk_dat;
	//if (stkMap.isEmpty())   //�ж�Ⱦɫ���Ƿ����ɹ�
	//	return;
	cout << "map colored--->\n";
	while (!stkMap.isEmpty())
	{
		stkMap.pop(t_stk_dat);
		l_stk.push(t_stk_dat);
		//��ͼȾɫ
		tmap[t_stk_dat.areaIndex].colorIndex = t_stk_dat.colorIndex;
		//��ʾ����
		cout <<setw(10) << "Index = " << t_stk_dat.areaIndex\
			<< setw(10) << "name = " << tmap[t_stk_dat.areaIndex].areaName\
			<< setw(10) << "color = " << tmap[t_stk_dat.areaIndex].colorIndex\
			<< endl;
	}
	//�ָ���ջ����
	while (!l_stk.isEmpty())
	{
		l_stk.pop(t_stk_dat);
		stkMap.push(t_stk_dat);
	}
}
//�ж����������Ƿ�����ظ�Ⱦɫ
//return: ��������ظ��򷵻� true������Ϊ false
bool judgeOverlapColor(const int areaRelate[AREANUMBER][AREANUMBER], \
	usrStack<mapStackType>&stkMap,const int t_areaIndex,const int t_colorIndex)
{
	usrStack<mapStackType>l_stk;
	mapStackType t_stk_dat;
	bool l_flag=false;
	while (!stkMap.isEmpty() && !l_flag)
	{
		stkMap.pop(t_stk_dat);
		l_stk.push(t_stk_dat);
		if (t_stk_dat.colorIndex == t_colorIndex &&\
			areaRelate[t_stk_dat.areaIndex][t_areaIndex])
			l_flag = true;
	}
	while (!l_stk.isEmpty())
	{
		l_stk.pop(t_stk_dat);
		stkMap.push(t_stk_dat);
	}
	return l_flag;
}

//��ͼȾɫ������⺯�����ҵ���������ͽ���
//AREANUMBER---����ҪȾɫ�������Ŀ
//parameter----��ͼ������������0��ʼ����
//areaRelate---��ʾ�����Ƿ����ڵľ����������Ϊ 1 ������Ϊ0
//return-------�ɹ����Ϊ true ������Ϊ false
bool mapSolver(const int areaRelate[AREANUMBER][AREANUMBER], usrStack<mapStackType>&stkMap)
{
	int curColor = 1, curArea = 0;   //��0��ʼ����
	mapStackType curdat;
	curdat.areaIndex = curArea;
	curdat.colorIndex = curColor;
	stkMap.push(curdat);
	curArea += 1; curColor += 1;
	while (curArea < AREANUMBER)
	{
		while (judgeOverlapColor(areaRelate,stkMap,curArea,curColor))  //�ж��Ƿ�����ظ���ɫ
		{
			curColor += 1;
			//��������ظ���ɫ������ɫ���ӣ�
			//���ﵽ�����ɫ���򵯳����ݣ��������бȶ�
			while (curColor > MAXCOLORNUM)   //��ʾ�Ѿ�����ȫ����ɫ
			{
				if (stkMap.isEmpty())
					return false;
				stkMap.pop(curdat);
				curArea = curdat.areaIndex;
				curColor = curdat.colorIndex+1;
			}
		}
		curdat.areaIndex = curArea;
		curdat.colorIndex = curColor;
		stkMap.push(curdat);
		curArea += 1;   //��һ������
		curColor = 1;   //�ӵ�һ����ɫ��ʼ����
	}
	if (stkMap.isEmpty())
		return false;
	return true;
}

bool mapSolver(const int areaRelate[AREANUMBER][AREANUMBER],\
	usrStack<mapStackType>&stkMap, mapElementType tmap[])
{
	int curColor = 1, curArea = 0;   //��0��ʼ����
	bool fullFlag = false;
	mapStackType curdat;
	curdat.areaIndex = curArea;
	curdat.colorIndex = curColor;
	stkMap.push(curdat);
	curArea += 1; curColor += 1;
	while(1) //(curArea < AREANUMBER)
	{
		if (curArea == AREANUMBER)
		{
			printSolver(tmap, stkMap);  //����ͼ
			//����������һȾɫ����
			stkMap.pop(curdat);
			curArea = curdat.areaIndex;
			curColor += 1;
			if (curColor > MAXCOLORNUM)
				goto POP_LABEL;
			fullFlag = true;
		}
		while (judgeOverlapColor(areaRelate, stkMap, curArea, curColor))  //�ж��Ƿ�����ظ���ɫ
		{
			curColor += 1;
			//��������ظ���ɫ������ɫ���ӣ�
			//���ﵽ�����ɫ���򵯳����ݣ��������бȶ�
POP_LABEL:	while (curColor > MAXCOLORNUM)   //��ʾ�Ѿ�����ȫ����ɫ
			{
				if (stkMap.isEmpty())
					return false;
				stkMap.pop(curdat);
				curArea = curdat.areaIndex;
				curColor = curdat.colorIndex + 1;
			}
		}
		curdat.areaIndex = curArea;
		curdat.colorIndex = curColor;
		stkMap.push(curdat);
		curArea += 1;   //��һ������
		if (!fullFlag)
			curColor = 1;   //�ӵ�һ����ɫ��ʼ����
	}
	if (stkMap.isEmpty())
		return false;
	return true;
}
