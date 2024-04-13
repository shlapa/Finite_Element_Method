// Copyright 2021 Old Shlapa

#ifndef DIPLOM_INCLUDE_GMATRIX_H_
#define DIPLOM_INCLUDE_GMATRIX_H_

#define DEFAULT_GLOBAL_VALUE 0.0

#include "LocalElem.h"

#include <iostream>
#include <vector>

using namespace std;
using vector3d = vector<vector<vector<double>>>;

class Gmatrix
{
public:
	double value; // Значение в связи узлов
	vector3d Matrix_3D; // Хранение матрицы по i, j, k
	LocalElem localelem; // Обьект класса элемента 
	vector<double> Matrix_num, Vector_value; // Хранения матрицы для представления глобальной нумерации по i
	int X, Y, Z, columns, strings; // Длина, высота и ширина куба + количество строк и столбцов глобальной матрицы связей
	vector<vector<double>> Matrix_con; // Хранение матрицы для связей узлов по i, j
	vector <double>::const_iterator iterator;
#pragma region GCONSTRUCTOR
	Gmatrix() { // Конструктор по умолчанию
		X = Y = Z = 1 + DEFAULT_XYZ;
		value = DEFAULT_GLOBAL_VALUE;
		columns = strings = X * Y * Z;
		CreateMatrix3D();
		CreateMatrixNumbering();
		CreateMatrixConnections();
	};

	Gmatrix(double val) { // Конструткор с параметрами
		this->value = val;
		this->X = 1 + localelem.X;
		this->Y = 1 + localelem.Y;
		this->Z = 1 + localelem.Z;
		columns = strings = X * Y * Z;
		CreateMatrix3D();
		CreateMatrixNumbering();
		CreateMatrixConnections();
	};

	Gmatrix(double val, vector<double> value) { // Конструткор с параметрами
		this->value = val;
		this->X = 1 + localelem.X;
		this->Y = 1 + localelem.Y;
		this->Z = 1 + localelem.Z;
		columns = strings = X * Y * Z;
		Vector_value.assign(value.begin(), value.end());
		iterator = Vector_value.begin();
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

	void CreateMatrix3D() { // Создание и заполнение трех-мерной матрицы
		Matrix_3D.resize(X, vector<vector<double>>(Y, vector<double>(Z, 0)));
		for (int i = 0; i < X; ++i) {
			for (int j = 0; j < Y; ++j) {
				for (int k = 0; k < Z; ++k) {
					Matrix_3D[i][j][k] = GetValue();
				}
			}
		}
	};

	void CreateMatrixConnections() { // Создание и заполнение глобальной матрицы связей
		Matrix_con.resize(columns, vector<double>(strings)) ;
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < strings; j++) {
				Matrix_con[i][j] = GetValue();
			}
		}
	};

	void CreateMatrixNumbering() { // Создание и заполнение матрицы глобальной нумерации
		for (int i = 0; i < X; ++i) {
			for (int j = 0; j < Y; ++j) {
				for (int k = 0; k < Z; ++k) {
					Matrix_num.push_back(Matrix_3D[i][j][k]);
				}
			}
		}
	};

};

#endif  // DIPLOM_INCLUDE_GMATRIX_H_