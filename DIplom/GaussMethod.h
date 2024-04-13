// Copyright 2021 Old Shlapa

#ifndef DIPLOM_INCLUDE_GAUSSMETHOD_H_
#define DIPLOM_INCLUDE_GAUSSMETHOD_H_

#define T1 100.0
#define T2 30.0

#include <iostream>
#include <vector>

using namespace std;

class GaussMethod
{
public:

    GaussMethod() {};

    void ShowSystemEquations(vector<vector<double>>a, vector<double> y, int n)
    {
        cout << "\n---------------------------------------------------------------------------------------------\n\t";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << a[i][j] << "*x" << j;
                if (j < n - 1)
                    cout << " + ";
            }
            cout << " = " << y[i] << endl;
        }
        return;
    };

    vector<double> GaussMethodForSystemEquations(vector<vector<double>> a, vector<double> y, int n)
    {
        vector<double> x;
        double max;
        int k, index;
        const double eps = 0.00001;
        x.resize(n);
        k = 0;
        while (k < n)
        {
            max = abs(a[k][k]);
            index = k;
            for (int i = k + 1; i < n; i++)
            {
                if (abs(a[i][k]) > max)
                {
                    max = abs(a[i][k]);
                    index = i;
                }
            }
            if (max < eps)
            {
                cout << "ERROR_ZERO_COLUM";
                cout << index << "MATRIX_A" << endl;
                return x;
            }
            for (int j = 0; j < n; j++)
            {
                double temp = a[k][j];
                a[k][j] = a[index][j];
                a[index][j] = temp;
            }
            double temp = y[k];
            y[k] = y[index];
            y[index] = temp;
            for (int i = k; i < n; i++)
            {
                double temp = a[i][k];
                if (abs(temp) < eps) continue;
                for (int j = 0; j < n; j++)
                    a[i][j] = a[i][j] / temp;
                y[i] = y[i] / temp;
                if (i == k)  continue;
                for (int j = 0; j < n; j++)
                    a[i][j] = a[i][j] - a[k][j];
                y[i] = y[i] - y[k];
            }
            k++;
        }
        for (k = n - 1; k >= 0; k--)
        {
            x[k] = y[k];
            for (int i = 0; i < k; i++)
                y[i] = y[i] - a[i][k] * x[k];
        }
        return x;
    }
    int Result(vector<vector<double>>matrix)
    {
        vector<vector<double>>a;
        vector<int> sto{ 0,1,2,9,10,11,18,19,20 };
        vector <int> tri{ 3,6,12,15,21,24 };
        vector<double> y, x;
        int size = matrix.size();
        y.resize(size);
        a.resize(size);
        for (int i = 0; i < a.size(); i++) {
            a[i].resize(size);
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if ((i == 0) || (i == 1) || (i == 2) || (i == 9) || (i == 10) || (i == 11) || (i == 18) || (i == 19) || (i == 20) || (i == 21) || (i == 3) || (i == 6) || (i == 12) || (i == 15) || (i == 24)) {
                    for (int k = 0; k < matrix[i].size(); k++) {
                        a[i][k] = 0.0;
                    }
                    a[i][i] = 1.0;
                }
                else {
                    a[i][j] = matrix[i][j];
                }
            }
        }
        for (int i = 0; i < size; i++)
        {
            if ((i == 0) || (i == 1) || (i == 2) || (i == 9) || (i == 10) || (i == 11) || (i == 18) || (i == 19) || (i == 20)) {
                y[i] = T1;
            }
            else if ((i == 3) || (i == 6) || (i == 12) || (i == 15) || (i == 21) || (i == 24)) {
                y[i] = T2;
            }
            else
                y[i] = 0;
        }
        ShowSystemEquations(a, y, size);
        x = GaussMethodForSystemEquations(a, y, size);
        for (int i = 0; i < size; i++)
            cout << "x[" << i << "]=" << x[i] << endl;
        cout << "\n---------------------------------------------------------------------------------------------\n";
        cout << endl;
        return 0;
    }
};

#endif  // DIPLOM_INCLUDE_GAUSSMETHOD_H_