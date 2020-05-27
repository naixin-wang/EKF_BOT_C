#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	int row;		//rowΪ��
	int col;		//colΪ��
	double* data;
}Matrix;

Matrix* IMatrix(int n);//��ʼ��n�׵�λ����
Matrix* InitMatrix(int row, int col);//��ʼ������
void ValueMatrix(Matrix* matrix, double* array);//��һ������ֵ
int SizeMatrix(Matrix* matrix);//���һ������Ĵ�С
void FreeMatrix(Matrix* matrix);//�ͷ�һ������
Matrix* CopyMatrix(Matrix* matrix);//����һ�������ֵ
void PrintMatrix(Matrix* matrix);//��ӡһ������
//����Ļ�������
Matrix* AddMatrix(Matrix* matrix_A, Matrix* matrix_B);	//����ļӷ�
Matrix* MulMatrix(Matrix* matrix_A, Matrix* matrix_B);	//����ĳ˷�
Matrix* TransMatrix(Matrix* matrix);//����ת��
void switchRowMatrix(Matrix* matrix, int row1, int row2);//����row1��row2λ��
void kRowMatrix(Matrix* matrix, double k, int row);//����ָ���г���k
void AddRowMatrix(Matrix* matrix, int row, int row1, double k);//��row1�г���k�ӵ�row��
Matrix* InvertMatrix(Matrix* matrix);//��������
#endif