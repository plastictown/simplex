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

	float ** matrix;	//Собственно матрица
	float ** is_matrix; //Матрица для выражения L(x)
	var * vertX;		//Номера иксов по вертикали
	var * horzX;		//Номера иксов по горизонтали
	float** chart;		//Таблица
	POINT size;			//Размер матрицы
	POINT size_small;
	float* g_x;			//Функция g(x)

	void SetSize(int x, int y);	//Установить размер матрицы( выделение памяти)
	void CalculateL_x();		//Вычислить коэфициэнты L(x)
	void CreateChartFromMatrix(); //Создать первоначальную таблицу
	void Copy_g_x_to_Matrix();
	void Copy_L_x_to_Matrix();
	int iteration();			//Выполнить итерацию - первый этап
	int iteration_small();		//Выполнить итерацию без L(x) - второй этап( поиск оптимального решения)

};

#endif // !__SIMPLEX_H__