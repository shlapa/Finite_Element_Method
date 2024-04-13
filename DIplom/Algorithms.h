// Copyright 2021 Old Shlapa

#ifndef DIPLOM_INCLUDE_ALGORITHMS_H_
#define DIPLOM_INCLUDE_ALGORITHMS_H_

#include "Gmatrix.h"
#include "LocalElem.h"
#include "MultMatrix.h"
#include "GaussMethod.h"
#include "windows.h"

// compile with: /openmp
#include <omp.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using vector3d = vector<vector<vector<double>>>;

class Algorithms
{
public:
	Gmatrix gmatrix; // Обьект кдасса глобальной матрицы
	LocalElem localelem; // Обект класса локального элемента
	MultMatrix multmatrix; // Обект класса операций с матрицами
	GaussMethod gaussmethod; // Обект класса метода гаусса
	vector<vector<int>> coords; // Координатый вершин элементов порядковая
	vector<LocalElem> Matrix_object; // Матрицы елементов
	vector<vector<double>> Matrix_elements; // Массив по вершинам элементов
	int N, M, K, num_values_nodes, num_values_elem; // Кол-во элементов по сторонах XYZ + кол-во элементов + кол-вл элементов

	Algorithms() { // Конструктор по умолчанию
		N = localelem.X;
		M = localelem.Y;
		K = localelem.Z;
		num_values_elem = N * M * K; // Функцию нахождение кол-ва элементов
		num_values_nodes = (N + 1) * (M + 1) * (K + 1);
		coords.resize(num_values_elem, vector<int>(8));
		for (int i = 0; i < num_values_elem; i++) {
			Matrix_object.push_back(LocalElem());
				Matrix_elements.push_back(Matrix_object[i].GetMatrixnum());
		}
	};
#pragma region SHOW
	void ShowMatrixCoords() { // Вывод матрицы координат
		cout << "\n\tMATRIX_COORDS:\n";
		for (int i = 0; i < coords.size(); ++i) {
			for (int j = 0; j < coords[i].size(); ++j) {
				cout << " [" << i << "][" << j << "]:" << coords[i][j] << " ";
			}
			cout << "\n";
		}
	};

	void ShowMatrixObjects() { // Вывод матрицы елементов
		cout << "\n\tMATRIX_OF_OBJECTS:\n";
		for (int i = 0; i < num_values_elem; i++) {
			for (int j = 0; j < 8; j++) {
				cout << Matrix_elements[i][j] << " ";
			}
			cout << "\n";
		}
	};

	void ShowMatrix3D(vector3d matrix) { // Вывод трехмерной матрицы
		cout << "\n\tMATRIX_IN_LOCAL_NUMBERS:\n";
		for (int i = 0, size = matrix.size(); i < size; ++i) {
			for (int j = 0, size = matrix[i].size(); j < size; ++j) {
				for (int k = 0, size = matrix[i][j].size(); k < size; ++k) {
					cout << " [" << i << "][" << j << "][" << k << "]:" << matrix[i][j][k] << "\n";
				}
			}
		}
	};

	void ShowMatrix2D(vector<vector<double>> matrix) { // Вывод двумерной матрицы
		cout << "\n\tMATRIX_THERMAL_CONDUCTIVITY:\n";
		for (int i = 0; i < matrix.size(); ++i) {
			cout << i<<"\t";
			for (int j = 0; j < matrix[i].size(); ++j) {
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	};

	void ShowMatrix1D(vector<double>matrix) { // Вывод одномерной матрицы
		cout << "\n\tMATRIX_IN_GLOBAL_NUMBERS:\n";
		int count = 0;
		for (auto i = matrix.begin(); i != matrix.end(); ++i) {
			cout << " [" << count + 1 << "]: " << (*i) << "\n";
			count++;
		}
	};
#pragma endregion
	int NFormula(int i, int j, int k, int N, int M) { // Формула #4
		int result = 0;
		result = i + j * (N + 1) + k * (N + 1) * (M + 1);
		return result;
	};

	void PushCoordsLocalElem() { // Заполнение массива координатами вершин элементов в трех-индексовой нумирации
		int num = 0;
		double START, END;
		START = omp_get_wtime();
#pragma omp parallel for
		for (int k = 0; k < K; k++) {
			for (int j = 0; j < M; j++) {
				for (int i = 0; i < N; i++) {
					num = NFormula(i, j, k, N - 1, M - 1);
					vector<vector<double>> MatrixB = { {(float)i,(float)j,(float)k}, {(float)(1+i),(float)j,(float)k}, {(float)(1+i),(float)(1+j),(float)k}, {(float)i,(float)(1+j),(float)k}, {(float)i,(float)j,(float)(1+k)}, {(float)(1+i),(float)j,(float)(1+k)}, {(float)(1+i),(float)(1+j),(float)(1+k)}, {(float)i,(float)(1+j),(float)(1+k)} };
					Matrix_object[num].MatrixJacobi(MatrixB);
				}
			}
		}
		Sleep(5000);
		END = omp_get_wtime();
		cout << "\n\t" << START <<" "<< END << " " << END - START << " seconds\n";
	};

	void NodeCoords() { // Заполнение массива координатами вершин элементов в порядковой нумерации
		int num = 0;
		for (int k = 0; k < K; k++) {
			for (int j = 0; j < M; j++) {
				for (int i = 0; i < N; i++) {
					num = NFormula(i, j, k, N - 1, M - 1);
					coords[num][0] = NFormula(i, j, k, N, M);
					coords[num][1] = NFormula(1 + i, j, k, N, M);
					coords[num][2] = NFormula(1 + i, 1 + j, k, N, M);
					coords[num][3] = NFormula(i, 1 + j, k, N, M);
					coords[num][4] = NFormula(i, j, 1 + k, N, M);
					coords[num][5] = NFormula(1 + i, j, 1 + k, N, M);
					coords[num][6] = NFormula(1 + i, 1 + j, 1 + k, N, M);
					coords[num][7] = NFormula(i, 1 + j, 1 + k, N, M);
				}
			}
		}		
	};

	vector<vector<double>> FormationMatrix() { // Заполнение матрицы теплопроводности
		int num, nfrst, nsec;
		for (int k = 0; k < K; k++) {
			for (int j = 0; j < M; j++) {
				for (int i = 0; i < N; i++) {
					num = NFormula(i, j, k, N - 1, M - 1);
					for (int im = 0; im < num_values_elem; im++) {
						nfrst = coords[num][im];
						for (int jm = 0; jm < 8; jm++) {
							nsec = coords[num][jm];
							gmatrix.Matrix_con[nfrst][nsec] += Matrix_object[num].Matrix_five[im][jm];
						}
					}
				}
			}
		}
		ShowMatrix2D(gmatrix.Matrix_con);
		return gmatrix.Matrix_con;
	};

};

#endif  // DIPLOM_INCLUDE_ALGORITHMS_H_