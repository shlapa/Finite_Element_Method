// Copyright 2021 Old Shlapa

#ifndef DIPLOM_INCLUDE_LOCALELEM_H_
#define DIPLOM_INCLUDE_LOCALELEM_H_

#define DEFAULT_XYZ 2
#define DEFAULT_LOCAL_VALUE 1.0
#define DEFAULT_THERMAL_CONDUCTIVITY -1.0

#include "MultMatrix.h"

#include <iostream>
#include <vector>

using namespace std;
using vector3d = vector<vector<vector<double>>>;

class LocalElem
{
public:
	MultMatrix multmatrix;
    vector3d Matrix_3D; // ’ранение матрицы по i, j, k
	vector <double>::const_iterator iterator;
    vector<double> Matrix_num, Vector_value; // ’ранени€ матрицы дл€ представлени€ глобальной нумерации по i
	vector<vector<double>> Matrix_con, Matrix_Jacobi, Inverse_Matrix_Jacobi, Matrix_five, Matrix_six; // ’ранение матрицы дл€ св€зей узлов по i, j
	vector<vector<double>> Matrix_STR = { {-1,1,1,-1,-1,1,1,-1}, {-1,-1,1,1,-1,-1,1,1}, {-1,-1,-1,-1,1,1,1,1} }; // Mатрица локальных натуральных координат узлов элемента (s,t,r)
	int X, Y, Z, value, columns, strings;
	double determinant, thermal_conductivity;
#pragma region CONSTRUCTOR
    LocalElem() { //  онструктор по умолчанию
        X = Y = Z = DEFAULT_XYZ;
        value = DEFAULT_LOCAL_VALUE;
		thermal_conductivity = DEFAULT_THERMAL_CONDUCTIVITY;
		columns = strings = X * Y * Z;
		CreateMatrix3D();
		CreateMatrixNumbering();
		CreateMatrixConnections();
    };

    LocalElem(int x, int y, int z, double tc, double val) { //  онструткор с параметрами
		thermal_conductivity = tc;
        this->X = x;
        this->Y = y;
        this->Z = z;
        this->value = val;
		columns = strings = X * Y * Z;
        CreateMatrix3D();
        CreateMatrixNumbering();
		CreateMatrixConnections();
    };

	LocalElem(int x, int y, int z, double val, double tc, vector<double> value) { //  онструткор с вектором значений
		thermal_conductivity = tc;
		this->X = x;
		this->Y = y;
		this->Z = z;
		this->value = val;
		Vector_value.assign(value.begin(), value.end());
		iterator = Vector_value.begin();
		columns = strings = X * Y * Z;
		CreateMatrix3D();
		CreateMatrixNumbering();
		CreateMatrixConnections();
	};
#pragma endregion
	double GetValue() {
		if (Vector_value.empty()) {
			return value;
		}
		else if (iterator != Vector_value.end()) {
			return *iterator;
		}
		else return value;
	};

	vector <double> GetMatrixnum() {
		return Matrix_num;
	};

	void MatrixJacobi(vector<vector<double>> matrix) {
		Matrix_STR = multmatrix.MultiplicationOnNum(Matrix_STR, 0.125);
		Matrix_Jacobi = multmatrix.MultiplicationOnMatrix(Matrix_STR, matrix);
		determinant = multmatrix.DeterminantMatrix(Matrix_Jacobi,3);
		Inverse_Matrix_Jacobi = multmatrix.InverseMatrix(Matrix_Jacobi, determinant);
		Matrix_five = multmatrix.MultiplicationOnMatrix(Inverse_Matrix_Jacobi, Matrix_STR);
		Matrix_six = multmatrix.TranspositionMatrix(Matrix_STR);
		Matrix_five = multmatrix.MultiplicationOnMatrix(Matrix_six, Matrix_five);
		double coof = thermal_conductivity * 8 * determinant;
		Matrix_five = multmatrix.MultiplicationOnNum(Matrix_five, coof);
	};

	void CreateMatrix3D() { // —оздание и заполнение трех-мерной матрицы
		Matrix_3D.resize(X, vector<vector<double>>(Y, vector<double>(Z, 0)));
		for (int i = 0; i < X; ++i) {
			for (int j = 0; j < Y; ++j) {
				for (int k = 0; k < Z; ++k) {
					Matrix_3D[i][j][k] = GetValue();
				}
			}
		}
	};

	void CreateMatrixConnections() { // —оздание и заполнение локальной матрицы св€зей
		Matrix_con.resize(columns, vector<double>(strings));
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < strings; j++) {
				Matrix_con[i][j] = GetValue();
			}
		}
	};

	void CreateMatrixNumbering() { // —оздание и заполнение матрицы локальной нумерации
		for (int i = 0; i < X; ++i) {
			for (int j = 0; j < Y; ++j) {
				for (int k = 0; k < Z; ++k) {
					Matrix_num.push_back(Matrix_3D[i][j][k]);
				}
			}
		}
	};

};

#endif  // DIPLOM_INCLUDE_LOCALELEM_H_