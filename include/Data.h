#ifndef DATA_H
#define DATA_H

#define INFINITE 99999999

#include <math.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Data {
   public:
	Data(int, char *);
	Data(Data *data);
	~Data();

	void read();
	void printMatrixDist();
	inline int getDimension() { return dimension; };
	inline double getDistance(int i, int j) { return distMatrix[i][j]; };

	inline vector<vector<double>> getMatrixCost() { return distMatrix; }
	inline vector<vector<double>> *getMatrixCostPointer() { return &distMatrix; }
	inline bool getExplicitCoord() { return explicitCoord; };
	void forbidArc(int i, int j) { this->distMatrix[i][j] = INFINITE; }

	string getInstanceName();  // Get instance's name

   private:
	string instaceName;

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
