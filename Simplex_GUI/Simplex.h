#pragma once

#ifndef __SIMPLEX_H__
#define __SIMPLEX_H__

#include <windows.h>
#include "Structures.h"

class CSimplex
{
public:
	CSimplex(void);
	~CSimplex(void);

	float ** matrix;	//���������� �������
	float ** is_matrix; //������� ��� ��������� L(x)
	var * vertX;		//������ ����� �� ���������
	var * horzX;		//������ ����� �� �����������
	float** chart;		//�������
	POINT size;			//������ �������
	POINT size_small;
	float* g_x;			//������� g(x)

	void SetSize(int x, int y);	//���������� ������ �������( ��������� ������)
	void CalculateL_x();		//��������� ����������� L(x)
	void CreateChartFromMatrix(); //������� �������������� �������
	void Copy_g_x_to_Matrix();
	void Copy_L_x_to_Matrix();
	int iteration();			//��������� �������� - ������ ����
	int iteration_small();		//��������� �������� ��� L(x) - ������ ����( ����� ������������ �������)

};

#endif // !__SIMPLEX_H__