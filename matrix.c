#include"matrix.h"

Matrix* IMatrix(int n) {
	Matrix* Imatrix = InitMatrix(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				Imatrix->data[i * n + j] = 1;
			}
			else {
				Imatrix->data[i * n + j] = 0;
			}
		}
	}
	return Imatrix;
}
Matrix* InitMatrix(int row, int col)				//初始化一个矩阵
{
	if (row > 0 && col > 0)
	{
		Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
		matrix->row = row;
		matrix->col = col;
		matrix->data = (double*)malloc(sizeof(double) * row * col);
		return matrix;
	}
	else
		return NULL;
}

void ValueMatrix(Matrix* matrix, double* array) 		//给矩阵赋值
{
	if (matrix->data != NULL)
	{
		matrix->data = array;
		//memcpy(matrix->data, array, matrix->row * matrix->col * sizeof(double));
	}
}

int SizeMatrix(Matrix* matrix)
{
	return matrix->row * matrix->col;
}

void FreeMatrix(Matrix* matrix)
{
	free(matrix->data);		//释放掉矩阵的data存储区
	matrix->data = NULL;
	free(matrix);
	matrix = NULL;
	if (matrix == NULL) {
		printf("释放成功\n");
	}
	else {
		printf("释放失败\n");
	}
}

void PrintMatrix(Matrix* matrix)
{
	for (int i = 0;i < SizeMatrix(matrix);i++)
	{
		printf("%lf\t", matrix->data[i]);
		if ((i + 1) % matrix->col == 0)
			printf("\n");
	}

}

Matrix* CopyMatrix(Matrix* matrix_A)
{
	Matrix* matrix_B = InitMatrix(matrix_A->row, matrix_A->col);
	memcpy(matrix_B->data, matrix_A->data, SizeMatrix(matrix_A) * sizeof(double));
	return matrix_B;
}


//加法
Matrix* AddMatrix(Matrix* matrix_A, Matrix* matrix_B)
{
	if (matrix_A->row == matrix_B->row && matrix_A->col == matrix_B->col)
	{
		Matrix* matrix_C = InitMatrix(matrix_A->row, matrix_A->col);
		for (int i = 0;i < matrix_A->col;i++)
		{
			for (int j = 0;j < matrix_A->row;j++)
			{
				matrix_C->data[i * matrix_C->row + j] = \
					matrix_A->data[i * matrix_A->row + j] + matrix_B->data[i * matrix_A->row + j];
			}
		}
		return matrix_C;
	}
	else
	{
		printf("不可相加\n");
		return NULL;
	}
}


//乘法
Matrix* MulMatrix(Matrix* matrix_A, Matrix* matrix_B)
{
	if (matrix_A->col == matrix_B->row)		//列==行
	{
		Matrix* matrix_C = InitMatrix(matrix_A->row, matrix_B->col);
		//matrix_C->row = matrix_A->row;		//A行
		// matrix_C->col = matrix_B->col;			//B列
		for (int i = 0;i < matrix_A->row;i++)
		{
			for (int j = 0;j < matrix_B->col;j++)
			{
				matrix_C->data[i * matrix_C->col + j] = 0;
				for (int k = 0;k < matrix_A->col;k++)
				{
					matrix_C->data[i * matrix_C->col + j] += \
						matrix_A->data[i * matrix_A->col + k] * matrix_B->data[k * matrix_B->col + j];
				}
			}
		}
		return matrix_C;
	}
	else
	{
		printf("不可相乘\n");
		return NULL;
	}
}


//矩阵转置
Matrix* TransMatrix(Matrix* matrix)	
{
		Matrix* matrixTran = InitMatrix(matrix->col, matrix->row);
		for (int i = 0;i < matrixTran->row;i++)
		{
			for (int j = 0;j < matrixTran->col;j++)
			{
				matrixTran->data[i * matrixTran->col + j] = matrix->data[j * matrix->col + i];
			}
		}
}

void switchRowMatrix(Matrix* matrix, int row1, int row2) {
	int col = matrix->col;
	double rowTemp;// = (double*)malloc(sizeof(double) * col);
	for (int i = 0; i < col; i++) {
		rowTemp = matrix->data[row1 * col + i];
		matrix->data[row1 * col + i] = matrix->data[row2 * col + i];
		matrix->data[row2 * col + i] = rowTemp;
	}
}

void kRowMatrix(Matrix* matrix, double k, int row) {
	for (int j = 0; j < matrix->col;j++) {
		matrix->data[row * matrix->col + j] *= k;
	}
}

void AddRowMatrix(Matrix* matrix, int row, int row1, double k) {
	for (int j = 0; j < matrix->col;j++) {
		matrix->data[row * matrix->col + j] += k*matrix->data[row1 * matrix->col + j];
	}
}

Matrix* InvertMatrix(Matrix* matrix) {
	if (matrix->row == matrix->col) {
		int n = matrix->row;
		Matrix* matrixInvert = IMatrix(n);//单位矩阵
		for (int i = 0; i <n; i++) {
			int r;
			if (matrix->data[i * n + i] == 0.0) {
				//如果对角元素为0，则在列中寻找不为零元素，如果均为零则不可逆
				
				for (r = i+1; r < n; r++) {
					if (matrix->data[r * n + i] != 0.0) {
						break;
					}
				}
				if (r == n || r > n) {
					printf("不可逆\n");
					return NULL;
				}
				switchRowMatrix(matrix, r, i);
				switchRowMatrix(matrixInvert, r, i);
			}
			double scalar = 1.0 / matrix->data[i * n + i];
			kRowMatrix(matrix, scalar, i);
			kRowMatrix(matrixInvert, scalar, i);
			printf("*************************%lf \n", scalar);
			PrintMatrix(matrix);
			//将该列其他元素化为零
			for (int j = 0; j < n; j++) {
				if (i == j || matrix->data[j * n + i] == 0.0) {
					continue;
				}
				double shear_needed = -matrix->data[j * n + i];
				AddRowMatrix(matrix, j, i, shear_needed);
				AddRowMatrix(matrixInvert, j, i, shear_needed);
			}
			
		}
		return matrixInvert;
	}
	else {
		printf("必须为方阵\n");
		return NULL;
	}
}


