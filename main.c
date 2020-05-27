#include"matrix.h" 
#include <math.h>
#define PI 3.14159265



int main() {//Target Track Function

	double sd = 0.05;
	double dt = 0.01;
	double t = 0;
	
	//Generate a trajectory of the target and
	//calculate the angle between the target and the Sensor as input of the Track algo
	
	double xInit[4] = { 0,0,1,0 };//Initial location of the target
	double s[4] = { -1,-2,0.4,0 };//Initial location of the sensor
	Matrix* x = InitMatrix(4, 1);
	Matrix* Sensor = InitMatrix(4, 1);
	ValueMatrix(x, xInit);
	ValueMatrix(Sensor, s);
	
	double a[500] = { 0 }; // acceleration of the target
	double aSensor[500] = { 0 }; // acceleration of the target

	for (int i = 50; i < 100; i++) {//
		a[i] = PI / 2 / 51 / dt + 0.01 * rand() / (RAND_MAX + 1.0);
	}
	for (int i = 200; i < 250; i++) {
		a[i] = PI / 2 / 51 / dt + 0.01 * rand() / (RAND_MAX + 1.0);
	}
	for (int i = 350; i < 400; i++) {
		a[i] = PI / 2 / 51 / dt + 0.01 * rand() / (RAND_MAX + 1.0);
	}

	Matrix* X = InitMatrix(500, 4); //trajectory of the target a list of x
	Matrix* S = InitMatrix(500, 4); //trajectory of the Sensor 
	double* Y = (double*)malloc(500*sizeof(double));//angle correspondent to the trajectory

	for (int i = 0; i < 500; i++) {
		//printf("%lf \n", a[i]);
		double expmFdt[16] = { 1,0,dt,0, 0, 1, 0, dt, 0, 0, 1, a[i] * dt, 0,0,-a[i] * dt, 1 };
		double sensorTrans[16] = { 1,0,dt,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		Matrix* A1 = InitMatrix(4, 4);//Ä¿±ê×´Ì¬×ª»»¾ØÕó
		Matrix* A2 = InitMatrix(4, 4);//Ì½²âÆ÷×´Ì¬×ª»»¾ØÕó
		ValueMatrix(A1, expmFdt);
		ValueMatrix(A2, sensorTrans);

		x = MulMatrix(A1, x);//4*1¾ØÕó

		Sensor = MulMatrix(A2, Sensor);//4*1¾ØÕó

		for (int j = 0; j < 4; j++) {
			X->data[i * 4 + j] = x->data[j];
			S->data[i * 4 + j] = Sensor->data[j];
		}


		Y[i] = atan2((x->data[1] - Sensor->data[1]), (x->data[0] - Sensor->data[0])) + sd * rand() / (RAND_MAX + 1.0);

	}
	//PrintMatrix(X);
	//PrintMatrix(S);
	for (int i = 0;i < 500;i++) {
		printf("*%lf \n", Y[i]*180/PI);
	}

	
	//init EKF
	

	return 0;
}




/*
double value[] = { 1,2,3,4,5,6 };
double value2[] = { 1,2,3 };
double value3[] = { 1,1,0,0,1,1,0,0,1 }; 

int main(int argc, char* argv[])
{
	Matrix* matrix1 = InitMatrix(3, 2);
	Matrix* matrix2 = InitMatrix(2, 3);//m1'
	Matrix* matrix3 = InitMatrix(3, 3);//m1*m2
	Matrix* matrix4 = InitMatrix(2, 2);//m2*m1
	Matrix* matrix5 = InitMatrix(3, 2);//copy of m1
	Matrix* matrix6 = InitMatrix(3, 2);//m1+m5
	Matrix* matrix7 = InitMatrix(3, 1);
	Matrix* matrix8 = InitMatrix(3, 1);//m3*m7
	Matrix* matrix9 = IMatrix(4);//I matrix
	Matrix* matrix10 = InitMatrix(3,3);//I matrix
	ValueMatrix(matrix1, value);
	matrix2 = TransMatrix(matrix1);
	matrix3 = MulMatrix(matrix1, matrix2);
	matrix4 = MulMatrix(matrix2, matrix1);
	matrix5 = CopyMatrix(matrix1);
	matrix6 = AddMatrix(matrix1, matrix5);
	ValueMatrix(matrix7, value2);
	matrix8 = MulMatrix(matrix3, matrix7);
	switchRowMatrix(matrix9, 1, 2);
	ValueMatrix(matrix10, value3);

	//matrix3 = TransMatrix(matrix1);
	//printf("%d\t", SizeMatrix(matrix1));
	printf("M1 \n");
	PrintMatrix(matrix1);
	printf("\n");
	printf("M2 = M1'\n");
	PrintMatrix(matrix2);
	printf("\n");
	printf("M3 = M1*M2\n");
	PrintMatrix(matrix3);
	printf("\n");
	printf("M4 = M2*M1 \n");
	PrintMatrix(matrix4);
	printf("\n");
	printf("M5 = copy of M1\n");
	PrintMatrix(matrix5);
	printf("\n");
	printf("M6 = M1+M5 \n");
	PrintMatrix(matrix6);
	printf("\n");
	printf("M7 \n");
	PrintMatrix(matrix7);
	printf("\n");
	printf("M8 \n");
	PrintMatrix(matrix8);
	AddRowMatrix(matrix8, 0, 1, 0.5);//addrow
	printf("\n");
	printf("M8 after\n");
	PrintMatrix(matrix8);
	printf("\n");
	printf("M9 \n");
	PrintMatrix(matrix9);
	printf("\n");
	printf("M10 before \n");
	PrintMatrix(matrix10);
	matrix10 = InvertMatrix(matrix10);
	printf("\n");
	printf("M10 after\n");
	PrintMatrix(matrix10);
	return 0;
}

*/