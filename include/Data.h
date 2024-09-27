#ifndef DATA_H
#define DATA_H

#define INFINITE 99999999

#include <math.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

class Data {
   public:
	Data(int, char *);
	Data(Data *data);
	Data() {
		distMatrix = {{INFINITE, 30, 26, 50, 40},
		              {30, INFINITE, 24, 40, 50},
		              {26, 24, INFINITE, 24, 26},
		              {50, 40, 24, INFINITE, 30},
		              {40, 50, 26, 30, INFINITE}};
		dimension = 5;
	}
	~Data();

	void read();
	void printMatrixDist();
	inline int getDimension() { return dimension; };
	inline double getDistance(int i, int j) { return distMatrix[i][j]; };

	inline vector<vector<double>> getMatrixCost() { return distMatrix; }
	inline vector<vector<double>> *getMatrixCostPointer() { return &distMatrix; }
	inline bool getExplicitCoord() { return explicitCoord; };
	void forbidArc(int i, int j) { this->distMatrix[i][j] = INFINITE; }
	int getFirstClosest() { return firstClosest; }
	int getSecondClosest() { return secondClosest; }
	void updateClosest();

	string getInstanceName();  // Get instance's name

   private:
	string instaceName;

	int firstClosest;
	int secondClosest;
	int dimension;

	vector<vector<double>> distMatrix;
	vector<double> xCoord, yCoord;

	// Computing Distances
	static double CalcDistEuc(vector<double> *X, vector<double> *Y, int I, int J);
	static double CalcDistAtt(vector<double> *X, vector<double> *Y, int I, int J);
	static void CalcLatLong(vector<double> *X, vector<double> *Y, int n, vector<double> *latit, vector<double> *longit);
	static double CalcDistGeo(vector<double> *latit, vector<double> *longit, int I, int J);
	bool explicitCoord;
};

#endif
