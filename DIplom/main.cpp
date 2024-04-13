#include "Gmatrix.h"
#include "Algorithms.h"
#include "GaussMethod.h"
#include "MultMatrix.h"
#include "LocalElem.h"

#include <iostream>
#include <vector>

using namespace std;
using vector3d = vector<vector<vector<double>>>;

int main() {
	vector<vector<double>> thermalmatrix;
	Gmatrix gmatrix;
	LocalElem localelem;
	Algorithms algorithm;
	GaussMethod gaussmethod;

	MultMatrix multmatrix;

	/*algorithm.ShowMatrix1D(gmatrix.Matrix_num);
	algorithm.ShowMatrix2D(gmatrix.Matrix_con);
	algorithm.ShowMatrix3D(gmatrix.Matrix_3D);
	algorithm.ShowMatrixObjects();
	algorithm.ShowMatrixCoords();*/
	//algorithm.ShowMatrix2D(thermalmatrix);

//#pragma omp parallel for
	/*vector<vector<double>> MatrixB = { {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1} };
	localelem.MatrixJacobi(MatrixB);
	algorithm.ShowMatrix2D(localelem.Matrix_STR);
	algorithm.ShowMatrix2D(MatrixB);
	*/
	algorithm.NodeCoords();
	algorithm.PushCoordsLocalElem();
	thermalmatrix = algorithm.FormationMatrix();
	//algorithm.ShowMatrix2D(algorithm.gmatrix.Matrix_con);
	//algorithm.ShowMatrix2D(thermalmatrix);
	vector < vector < double >>  s1{ {0,0,0},{1,1,1} };
	gaussmethod.Result(thermalmatrix);
}
