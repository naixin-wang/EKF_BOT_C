#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	int row;		//row为行
	int col;		//col为列
	double* data;
}Matrix;

Matrix* IMatrix(int n);//初始化n阶单位矩阵
Matrix* InitMatrix(int row, int col);//初始化矩阵
void ValueMatrix(Matrix* matrix, double* array);//给一个矩阵赋值
int SizeMatrix(Matrix* matrix);//获得一个矩阵的大小
void FreeMatrix(Matrix* matrix);//释放一个矩阵
Matrix* CopyMatrix(Matrix* matrix);//复制一个矩阵的值
void PrintMatrix(Matrix* matrix);//打印一个矩阵
//矩阵的基本运算
Matrix* AddMatrix(Matrix* matrix_A, Matrix* matrix_B);	//矩阵的加法
Matrix* MulMatrix(Matrix* matrix_A, Matrix* matrix_B);	//矩阵的乘法
Matrix* TransMatrix(Matrix* matrix);//矩阵转置
void switchRowMatrix(Matrix* matrix, int row1, int row2);//调换row1和row2位置
void kRowMatrix(Matrix* matrix, double k, int row);//矩阵指定行乘以k
void AddRowMatrix(Matrix* matrix, int row, int row1, double k);//将row1行乘以k加到row上
Matrix* InvertMatrix(Matrix* matrix);//矩阵求逆
#endif