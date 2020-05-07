#include "StdAfx.h"
#include "Simplex.h"

using namespace std;

#define SIMPLEX_DEBUG 

CSimplex::CSimplex(void)
{
	size.x=0;
	size.y=0;
	size_small.x=0;
	size_small.y=0;
}

CSimplex::~CSimplex(void)
{
}

//--��������� ������--//
void CSimplex::SetSize(int nRows, int nCols) //�����/������ �������
{
	size.y=nRows+2;
	size.x=nCols+nRows;
	size_small.x=nCols;
	size_small.y=nRows;

	//------���������-�������-�����-----//
	horzX=new var[nCols-1];				//��������� ������
	vertX=new var[nRows];				//��������� ������

	for(int i=0; i<nCols-1; i++)
	{
		horzX[i].num=i+1;					//����� ����������
		horzX[i].type=FALSE;			//��������� ����������
		horzX[i].is_used=TRUE;			//������������
	}

	for(int i=0; i<nRows; i++)
	{
		vertX[i].num=nCols+i;			//����� ����������
		vertX[i].type=TRUE;				//�������� ����������
		vertX[i].is_used=TRUE;			//������������
	}
	//------���������-�������-�����-----//

	g_x=new float[nCols];

	for(int i=0; i<nCols; i++)
	{
		g_x[i]=0;
	}

	matrix=new float*[size.y];
	is_matrix=new float*[size.y];

	for(int i=0; i<size.y; i++)
	{
		matrix[i]=new float[size.x];
		is_matrix[i]=new float[size.x];
	}

	for(int i=0; i<size.y; i++)
	{
		for(int j=0; j<size.x; j++)
		{
			matrix[i][j]=0;
			is_matrix[i][j]=0;
		}
	}

	int c=0;

	for(int i=(nCols-1); i<(nCols+nRows-1); i++)
	{
		matrix[c][i]=1;
		is_matrix[c][i]=1;
		c++;
	}

}

void CSimplex::CalculateL_x()
{
	for(int i=0; i<(size.y-2); i++)
	{
		for(int j=0; j<(size.x-size.y+1); j++)
		{
			//is_matrix[i][j]=-is_matrix[i][j];
		}
	}

	for(int i=0; i<(size.y-2); i++)
	{
		for(int j=0; j<(size.x-size.y+1); j++)
		{
			is_matrix[size.y-1][j]-=matrix[i][j];

		}
		is_matrix[size.y-1][size.x-1]+=matrix[i][size.x-1];
	}

	/*for(int i=0; i<size.y; i++)
	{
		matrix[i][size.x-1]=is_matrix[i][size.x-1];
	}*/

}

void CSimplex::Copy_g_x_to_Matrix()
{
	for(int i=0; i<(size_small.x-1); i++)
	{
		matrix[size.y-2][i]=g_x[i];
	}

	matrix[size.y-2][size.x-1]=g_x[size_small.x-1];
}

void CSimplex::Copy_L_x_to_Matrix()
{
	for(int i=0; i<size.x-size.y +1;i++)
	{
		matrix[size.y-1][i]=is_matrix[size.y-1][i];
	}

	matrix[size.y-1][size.x-1]=is_matrix[size.y-1][size.x-1];
}

int CSimplex::iteration()
{
	//������������ ��������:
	//1 - ������� �������
	//-1 - ������� ���
	//0 - �������� ����������� �������

	int o_Col=-1;	//������� �������
	int o_Row=-1;	//������� ������
	float o_Col_temp=0;	//��������������� ����������
	float o_Row_temp=-1;	//��������������� ����������

	//������� ������� �������
	for(int i=0; i<(size_small.x-1); i++)
	{
		if(!horzX[i].is_used) continue;			//���� ������� ���������� ������, ����������

		if(	(matrix[size.y-1][i]<0) &&			//������� ������ ����
			(matrix[size.y-1][i]<o_Col_temp))	//������� ������ o_Col_temp
		{
			o_Col_temp=matrix[size.y-1][i];		//o_Col_temp ����� �������� ��������
			o_Col=i;							//������ �������� ����� �������� �����
		}
	}


	if(o_Col==-1) return 1; //���� ������������� ��������� ���, ������� �������

	BOOL is_positive=FALSE;	//���� �� ������������� �������� � ������� ��������

	//---���� ������������� �������� � ������� ��������---
		for(int i=0; i<size_small.y; i++)
		{
			if(matrix[i][o_Col]>0)
			{
				is_positive=TRUE;
				o_Row_temp=matrix[i][size.x-1]/matrix[i][o_Col];
				o_Row=i;
				break;
			}
		}

		if(!is_positive)	return -1;	//������������� �������� ���


	//������� ������� �������
	for(int i=0; i<size_small.y; i++)
	{
		if(matrix[i][o_Col]>0)
		{
			is_positive=TRUE;	

			if((matrix[i][size.x-1]/matrix[i][o_Col])<o_Row_temp)
			{
				o_Row_temp=(matrix[i][size.x-1]/matrix[i][o_Col]);
				o_Row=i;
			}
		}
	}

	if(o_Row==-1) return -1; //���� ������������� ��������� ���, ������� ���

	//�������� bi � �������������� ����� ������� matrix

	for(int i=0; i<size.y; i++)
	{
		matrix[i][size_small.x-1]=matrix[i][size.x-1];
	}

	//������� ����� �������

	float ** chart=new float*[size.y];

	for(int i=0; i<size.y; i++)
	{
		chart[i]=new float[size_small.x];
	}

	//��������� ����� �������

	for(int i=0; i<size.y; i++)
	{
		for(int j=0; j<size_small.x; j++)
		{
			if(i==o_Row && j==o_Col)		//������� �������
			{
				chart[i][j]=1/matrix[o_Row][o_Col];
				continue;
			}

			if(i==o_Row)					//������� ������
			{
				chart[i][j]=matrix[i][j]/matrix[o_Row][o_Col];
				continue;
			}

			if(j==o_Col)					//������� �������
			{
				chart[i][j]=-matrix[i][j]/matrix[o_Row][o_Col];
				//chart[i][j]=0;
				continue;
			}
			//� ��������� ������� ��������� �������� �������� �� �������
			chart[i][j]= ((matrix[i][j]*matrix[o_Row][o_Col]) - (matrix[i][o_Col]*matrix[o_Row][j]))/matrix[o_Row][o_Col];

		}
	}

	//����� ��� �������� �� �������

	for(int i=0; i<size.y; i++)
	{
		for(int j=0; j<size_small.x; j++)
		{
			//chart[i][j]=chart[i][j]/matrix[o_Row][o_Col];

			//matrix[i][j]=chart[i][j];			//�������� �������� ������� � matrix
			if(j==size_small.x-1)
			{
				//matrix[i][size.x-1]=chart[i][j];//�������� bi � ��������� ������� matrix
			}
		}
	}

		//�������� chart ������� � matrix
		for(int i=0; i<size.y; i++)
	{

		for(int j=0; j<size_small.x; j++)
		{
			matrix[i][j]=chart[i][j];

			if(j==size_small.x-1)
			{
				matrix[i][size.x-1]=chart[i][j];//�������� bi � ��������� ������� matrix
			}
		}
	}

	//������ ������ ����������

	var temp;

	temp.num=horzX[o_Col].num;
	temp.is_used=horzX[o_Col].is_used;
	temp.type=horzX[o_Col].type;

	horzX[o_Col].num=vertX[o_Row].num;
	horzX[o_Col].is_used=vertX[o_Row].is_used;
	horzX[o_Col].type=vertX[o_Row].type;

	vertX[o_Row].num=temp.num;
	vertX[o_Row].is_used=temp.is_used;
	vertX[o_Row].type=temp.type;

	//--------?--------//
	if(horzX[o_Col].type==TRUE) horzX[o_Col].is_used=FALSE;
	//--------?--------//

	//������ ������

	delete[] chart;
	

	//�������� ����������� �������. ���������� 0
	return 0;
}

int CSimplex::iteration_small()
{
	//������������ ��������:
	//1 - ������� �������
	//-1 - ������� ���
	//0 - �������� ����������� �������

	int o_Col=-1;	//������� �������
	int o_Row=-1;	//������� ������
	float o_Col_temp=0;	//��������������� ����������
	float o_Row_temp=-1;	//��������������� ����������

	//������� ������� �������
	for(int i=0; i<(size_small.x-1); i++)
	{
		if(!horzX[i].is_used) continue;			//���� ������� ���������� ������, ����������

		if(	(matrix[size.y-2][i]<0) &&			//������� ������ ����
			(matrix[size.y-2][i]<o_Col_temp))	//������� ������ o_Col_temp
		{
			o_Col_temp=matrix[size.y-2][i];		//o_Col_temp ����� �������� ��������
			o_Col=i;							//������ �������� ����� �������� �����
		}
	}

	if(o_Col==-1) return 1; //���� ������������� ��������� ���, ������� �������

	BOOL is_positive=FALSE;	//���� �� ������������� �������� � ������� ��������

	//---���� ������������� �������� � ������� ��������---
		for(int i=0; i<size_small.y; i++)
		{
			if(matrix[i][o_Col]>0)
			{
				is_positive=TRUE;
				o_Row_temp=matrix[i][size.x-1]/matrix[i][o_Col];
				o_Row=i;
				break;
			}
		}

		if(!is_positive)	return -1;	//������������� �������� ���


	//������� ������� �������
	for(int i=0; i<size_small.y; i++)
	{
		if(matrix[i][o_Col]>0)
		{
			is_positive=TRUE;	

			if((matrix[i][size.x-1]/matrix[i][o_Col])<o_Row_temp)
			{
				o_Row_temp=(matrix[i][size.x-1]/matrix[i][o_Col]);
				o_Row=i;
			}
		}
	}

	if(o_Row==-1) return -1; //���� ������������� ��������� ���, ������� ���

	//�������� bi � �������������� ����� ������� matrix

	for(int i=0; i<size.y; i++)
	{
		matrix[i][size_small.x-1]=matrix[i][size.x-1];
	}

	//������� ����� �������

	float ** chart=new float*[size.y];

	for(int i=0; i<size.y; i++)
	{
		chart[i]=new float[size_small.x];
	}

	//��������� ����� �������

	for(int i=0; i<size.y; i++)
	{
		for(int j=0; j<size_small.x; j++)
		{
			if(i==o_Row && j==o_Col)		//������� �������
			{
				chart[i][j]=1/matrix[o_Row][o_Col];
				continue;
			}

			if(i==o_Row)					//������� ������
			{
				chart[i][j]=matrix[i][j]/matrix[o_Row][o_Col];
				continue;
			}

			if(j==o_Col)					//������� �������
			{
				chart[i][j]=-matrix[i][j]/matrix[o_Row][o_Col];
				//chart[i][j]=0;
				continue;
			}
			//� ��������� ������� ��������� �������� �������� �� �������
			chart[i][j]= ((matrix[i][j]*matrix[o_Row][o_Col]) - (matrix[i][o_Col]*matrix[o_Row][j]))/matrix[o_Row][o_Col];

		}
	}

	//����� ��� �������� �� �������

	for(int i=0; i<size.y; i++)
	{
		for(int j=0; j<size_small.x; j++)
		{
			//chart[i][j]=chart[i][j]/matrix[o_Row][o_Col];

			//matrix[i][j]=chart[i][j];			//�������� �������� ������� � matrix
			if(j==size_small.x-1)
			{
				//matrix[i][size.x-1]=chart[i][j];//�������� bi � ��������� ������� matrix
			}
		}
	}

		//�������� chart ������� � matrix
		for(int i=0; i<size.y; i++)
	{
		for(int j=0; j<size_small.x; j++)
		{
			matrix[i][j]=chart[i][j];

			if(j==size_small.x-1)
			{
				matrix[i][size.x-1]=chart[i][j];//�������� bi � ��������� ������� matrix
			}
		}
	}

	//������ ������ ����������

	var temp;

	temp.num=horzX[o_Col].num;
	temp.is_used=horzX[o_Col].is_used;
	temp.type=horzX[o_Col].type;

	horzX[o_Col].num=vertX[o_Row].num;
	horzX[o_Col].is_used=vertX[o_Row].is_used;
	horzX[o_Col].type=vertX[o_Row].type;

	vertX[o_Row].num=temp.num;
	vertX[o_Row].is_used=temp.is_used;
	vertX[o_Row].type=temp.type;

	//--------?--------//
	//if(horzX[o_Col].type==TRUE) horzX[o_Col].is_used=FALSE;
	//--------?--------//

	//������ ������

	delete[] chart;
	

	//�������� ����������� �������. ���������� 0
	return 0;
}