// Copyright 2021 Old Shlapa

#ifndef DIPLOM_INCLUDE_MULTMATRIX_H_
#define DIPLOM_INCLUDE_MULTMATRIX_H_

#include <iostream>
#include <vector>

using namespace std;

class MultMatrix
{
public:
    MultMatrix() {};

    bool IsCanMultMatrix(int fcol, int srow) {
        return fcol == srow; 
    };

    double DeterminantMatrix(vector<vector<double>> matrix, int N) {
            vector<vector<double>> Result_matrix;
            double det = 0.0;
            if (N == 1)
                return matrix[0][0];
            else if (N == 2)
                return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
            else {
                for (int k = 0; k < N; k++) {
                    Result_matrix.resize(N - 1);
                    for (int i = 0; i < N - 1; i++) {
                        Result_matrix[i].resize(N - 1);
                    }
                    for (int i = 1; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            if (j == k)
                                continue;
                            else if (j < k)
                                Result_matrix[i - 1][j] = matrix[i][j];
                            else
                                Result_matrix[i - 1][j - 1] = matrix[i][j];
                        }
                    }
                    det += pow(-1, k + 2) * matrix[0][k] * DeterminantMatrix(Result_matrix, N - 1);
                }
                //cout << "\n" << det << "\n"; // Удалить
                return det;
            }
    };

    vector<vector<double>>InverseMatrix(vector<vector<double>> matrix, double det) {
        vector<vector<double>> Result_matrix;
        int row = matrix.size();
        int col = matrix[0].size();
        Result_matrix.resize(row);
        for (int i = 0; i < Result_matrix.size(); i++) {
            Result_matrix[i].resize(col);
        }
        Result_matrix[0][0] = ((matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1])) / det;
        Result_matrix[0][1] = ((-matrix[0][1] * matrix[2][2]) + (matrix[0][2] * matrix[2][1])) / det;
        Result_matrix[0][2] = ((matrix[0][1] * matrix[1][2]) - (matrix[0][2] * matrix[1][1])) / det;
        Result_matrix[1][0] = ((-matrix[1][0] * matrix[2][2]) + (matrix[1][2] * matrix[2][1])) / det; 
        Result_matrix[1][1] = ((matrix[0][0] * matrix[2][2]) - (matrix[0][2] * matrix[2][0])) / det;
        Result_matrix[1][2] = ((-matrix[0][0] * matrix[1][2]) + (matrix[0][2] * matrix[1][0])) / det;
        Result_matrix[2][0] = ((matrix[1][0] * matrix[2][1]) - (matrix[1][1] * matrix[2][0])) / det;
        Result_matrix[2][1] = ((-matrix[0][0] * matrix[2][1]) + (matrix[0][1] * matrix[2][0])) / det;
        Result_matrix[2][2] = ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0])) / det;
        return Result_matrix;
    };

    vector<vector<double>> TranspositionMatrix(vector<vector<double>> matrix) {
        vector<vector<double>> Result_matrix;
        int row = matrix.size();
        int col = matrix[0].size();
        Result_matrix.resize(col);
        for (int i = 0; i < col; i++) {
            Result_matrix[i].resize(row);
        }
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                Result_matrix[i][j] = matrix[j][i];
                }
        } 
#pragma region TEST
      /*  cout << "\n\t TRANSPOSITION_MATRIX \n";
        for (int i = 0; i < Result_matrix.size(); i++) {
            for (int j = 0; j < Result_matrix[i].size(); j++) {
                cout << "["<<i<<"]["<<j<<"]:"<< Result_matrix[i][j] << " ";
            }
            cout << endl;
        }*/
#pragma endregion
            return Result_matrix;
    };

    vector<vector<double>> MultiplicationOnNum(vector<vector<double>> first_matrix, double num) {
        for (int i = 0; i < first_matrix.size(); ++i) {
            for (int j = 0; j < first_matrix[i].size(); ++j) {
                first_matrix[i][j] *= num;
            }
        }
        return first_matrix;
    };

    vector<vector<double>> MultiplicationOnMatrix(vector<vector<double>> first_matrix, vector<vector<double>> second_matrix) {
        vector<vector<double>> Result_matrix;
        int frow = first_matrix.size();
        int scol = second_matrix[0].size();
        int srow = second_matrix.size();
        int fcol = first_matrix[0].size();
        if (!IsCanMultMatrix(fcol, srow)) {
            cout << fcol << " " << srow;
        } else {
            Result_matrix.resize(frow);
            for (int i = 0; i < frow; i++)
            {
                Result_matrix[i].resize(scol);
                for (int j = 0; j < scol; j++)
                {
                    Result_matrix[i][j] = 0;
                    for (int k = 0; k < fcol; k++)
                        Result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
                }
            }
            return Result_matrix;
        }
    };

};

#endif  // DIPLOM_INCLUDE_MULTMATRIX_H_