#include "../include/Data.h"

// Inicializador
Data::Data(int qtParam, char *instance) {
	if (qtParam < 2) {
		cout << "Missing parameters\n";
		cout << " ./exeLaRP [Instance]" << endl;
		exit(1);
	}

	if (qtParam > 4) {
		cout << "Too many parameters\n";
		cout << " ./exeLaRP [Instance] [Upper Bound] [Search method]" << endl;
		exit(1);
	}

	instaceName = instance;
	dimension = -1;
	explicitCoord = false;
}

Data::Data(Data *data) {
	this->distMatrix = data->getMatrixCost();
	this->dimension = data->getDimension();
}

void Data::updateClosest() {
	auto indexCostDepot = vector<int>(dimension);
	iota(indexCostDepot.begin(), indexCostDepot.end(), 0);
	sort(indexCostDepot.begin(), indexCostDepot.end(), [this](const int &a, int &b) { return getDistance(0, a) < getDistance(0, b); });
	this->firstClosest = indexCostDepot[0];
	sort(indexCostDepot.begin(), indexCostDepot.end(), [this](const int &a, int &b) { return getDistance(0, a) < getDistance(0, b); });
	this->secondClosest = indexCostDepot[1];
}

Data::~Data() {}

void Data::read() {
	ifstream inTSP(instaceName, ios::in);

	if (!inTSP) {
		cout << "File not found" << endl;
		exit(1);
	}

	string file, typeProblem;  // They are used into the reader

	while (file.compare("DIMENSION:") != 0 && file.compare("DIMENSION") != 0) {
		inTSP >> file;
	}

	if (file.compare("DIMENSION") == 0) inTSP >> file;

	inTSP >> dimension;  // valor depois do string "DIMENSION:" é a dimensão do problema

	while (file.compare("EDGE_WEIGHT_TYPE:") != 0 && file.compare("EDGE_WEIGHT_TYPE") != 0) {
		inTSP >> file;
	}
	if (file.compare("EDGE_WEIGHT_TYPE") == 0) inTSP >> file;

	inTSP >> typeProblem;  // EDGE_WEIGHT_TYPE

	xCoord = vector<double>(dimension);  // coord x
	yCoord = vector<double>(dimension);  // coord y

	// Alocar matriz 2D
	distMatrix = vector<vector<double>>(dimension, vector<double>(dimension, INFINITE));  // memoria dinâmica (matrix 2D)

	if (typeProblem == "EXPLICIT") {
		while (file.compare("EDGE_WEIGHT_FORMAT:") != 0 && file.compare("EDGE_WEIGHT_FORMAT") != 0) {
			inTSP >> file;
		}

		string ewf;

		if (file.compare("EDGE_WEIGHT_FORMAT") == 0) inTSP >> file;
		inTSP >> ewf;

		if (ewf == "FUNCTION") {
			cout << "FUNCTION - Nao suportado!" << endl;
		}

		else if (ewf == "FULL_MATRIX") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int i = 0; i < dimension; i++) {
				for (int j = 0; j < dimension; j++) {
					inTSP >> distMatrix[i][j];
					if (i == j) {
						distMatrix[i][j] = INFINITE;
					}
				}
			}
		}

		else if (ewf == "UPPER_ROW") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int i = 0; i < dimension; i++) {
				for (int j = i + 1; j < dimension; j++) {
					inTSP >> distMatrix[i][j];
					distMatrix[j][i] = distMatrix[i][j];
				}
			}

			for (int i = 0; i < dimension; i++) {
				//                distMatrix[i][i] = 0;
				distMatrix[i][i] = INFINITE;
			}
		}

		else if (ewf == "LOWER_ROW") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int i = 1; i < dimension; i++) {
				for (int j = 0; j < i; j++) {
					inTSP >> distMatrix[i][j];
					distMatrix[j][i] = distMatrix[i][j];
				}
			}

			for (int i = 0; i < dimension; i++) {
				//                distMatrix[i][i] = 0;
				distMatrix[i][i] = INFINITE;
			}
		}

		else if (ewf == "UPPER_DIAG_ROW") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int i = 0; i < dimension; i++) {
				for (int j = i; j < dimension; j++) {
					inTSP >> distMatrix[i][j];
					distMatrix[j][i] = distMatrix[i][j];

					if (i == j) {
						distMatrix[i][j] = INFINITE;
					}
				}
			}
		}

		else if (ewf == "LOWER_DIAG_ROW") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int i = 0; i < dimension; i++) {
				for (int j = 0; j <= i; j++) {
					inTSP >> distMatrix[i][j];
					distMatrix[j][i] = distMatrix[i][j];

					if (i == j) {
						distMatrix[i][j] = INFINITE;
					}
				}
			}
		}

		else if (ewf == "UPPER_COL") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int j = 1; j < dimension; j++) {
				for (int i = 0; i < j; i++) {
					inTSP >> distMatrix[i][j];
					distMatrix[j][i] = distMatrix[i][j];
				}
			}

			for (int i = 0; i < dimension; i++) {
				//                distMatrix[i][i] = 0;
				distMatrix[i][i] = INFINITE;
			}

		}

		else if (ewf == "LOWER_COL") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int j = 0; j < dimension; j++) {
				for (int i = j + 1; i < dimension; i++) {
					inTSP >> distMatrix[i][j];
					distMatrix[j][i] = distMatrix[i][j];
				}
			}

			for (int i = 0; i < dimension; i++) {
				//                distMatrix[i][i] = 0;
				distMatrix[i][i] = INFINITE;
			}

		}

		else if (ewf == "UPPER_DIAG_COL") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int j = 0; j < dimension; j++) {
				for (int i = 0; i <= j; i++) {
					inTSP >> distMatrix[i][j];
					distMatrix[j][i] = distMatrix[i][j];
					if (i == j) {
						distMatrix[i][j] = INFINITE;
					}
				}
			}
		}

		else if (ewf == "LOWER_DIAG_COL") {
			while (file.compare("EDGE_WEIGHT_SECTION") != 0) {
				inTSP >> file;
			}

			// Preencher Matriz Distancia
			for (int j = 0; j < dimension; j++) {
				for (int i = j; i < dimension; j++) {
					inTSP >> distMatrix[i][j];
					distMatrix[j][i] = distMatrix[i][j];

					if (i == j) {
						distMatrix[i][j] = INFINITE;
					}
				}
			}
		}

		//      cout << ewf << endl;
	}

	else if (typeProblem == "EUC_2D") {
		explicitCoord = true;

		while (file.compare("NODE_COORD_SECTION") != 0) {
			inTSP >> file;
		}
		// ler coordenadas
		int tempCity;
		for (int i = 0; i < dimension; i++) {
			inTSP >> tempCity >> xCoord[i] >> yCoord[i];
		}

		// Calcular Matriz Distancia (Euclidiana)
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				distMatrix[i][j] = floor(CalcDistEuc(&xCoord, &yCoord, i, j) + 0.5);

				if (i == j) {
					distMatrix[i][j] = INFINITE;
				}
			}
		}
	}

	else if (typeProblem == "EUD_3D") {
		cout << "EUC_3D - Nao suportado!" << endl;
	}

	else if (typeProblem == "MAX_2D") {
		cout << "MAX_2D - Nao suportado!" << endl;
	}

	else if (typeProblem == "MAX_3D") {
		cout << "MAX_3D - Nao Suportado!" << endl;
	}

	else if (typeProblem == "MAN_2D") {
		cout << "MAN_2D - Nao suportado!" << endl;
	}

	else if (typeProblem == "MAN_3D") {
		cout << "MAN_3D - Nao Suportado!" << endl;
	}

	else if (typeProblem == "CEIL_2D") {
		explicitCoord = true;
		while (file.compare("NODE_COORD_SECTION") != 0) {
			inTSP >> file;
		}
		// ler coordenadas
		int tempCity;
		for (int i = 0; i < dimension; i++) {
			inTSP >> tempCity >> xCoord[i] >> yCoord[i];
		}

		// Calcular Matriz Distancia (Euclidiana)
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				distMatrix[i][j] = ceil(CalcDistEuc(&xCoord, &yCoord, i, j));

				if (i == j) {
					distMatrix[i][j] = INFINITE;
				}
			}
		}
	}

	else if (typeProblem == "GEO") {
		explicitCoord = true;

		while (file.compare("NODE_COORD_SECTION") != 0) {  // enquanto nao achar o string "NODE_COORD_SECTION" faça
			inTSP >> file;
		}
		// ler coordenadas
		int tempCity;  // numero da cidade
		for (int i = 0; i < dimension; i++) {
			inTSP >> tempCity >> xCoord[i] >> yCoord[i];
		}

		vector<double> latitude = vector<double>(dimension);
		vector<double> longitude = vector<double>(dimension);

		CalcLatLong(&xCoord, &yCoord, dimension, &latitude, &longitude);

		// Calcular Matriz Distancia
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				distMatrix[i][j] = CalcDistGeo(&latitude, &longitude, i, j);

				if (i == j) {
					distMatrix[i][j] = INFINITE;
				}
			}
		}
	}

	else if (typeProblem == "ATT") {
		explicitCoord = true;

		while (file.compare("NODE_COORD_SECTION") != 0) {
			inTSP >> file;
		}

		// ler coordenadas
		int tempCity;
		int *tempX = new int[dimension];
		int *tempY = new int[dimension];

		for (int i = 0; i < dimension; i++) {
			inTSP >> tempCity >> tempX[i] >> tempY[i];
			xCoord[i] = tempX[i];
			yCoord[i] = tempY[i];
		}

		// Calcular Matriz Distancia (Pesudo-Euclidiana)
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				distMatrix[i][j] = CalcDistAtt(&xCoord, &yCoord, i, j);

				if (i == j) {
					distMatrix[i][j] = INFINITE;
				}
			}
		}

		delete[] tempX;
		delete[] tempY;

	}

	else if (typeProblem == "XRAY1") {
		cout << "XRAY1 - Nao suportado!" << endl;
	}

	else if (typeProblem == "XRAY2") {
		cout << "XRAY2 - Nao suportado!" << endl;
	}

	else if (typeProblem == "SPECIAL") {
		cout << "SPECIAL - Nao suportado!" << endl;
	}

	firstClosest = -1;
	secondClosest = -1;
	auto costDepot = distMatrix[0];
	auto indexCostDepot = vector<int>(distMatrix.size());
	iota(indexCostDepot.begin(), indexCostDepot.end(), 0);
	sort(indexCostDepot.begin(), indexCostDepot.end(), [costDepot](const int &a, int &b) { return costDepot[a] < costDepot[b]; });
	firstClosest = indexCostDepot[0];
	secondClosest = indexCostDepot[1];
}

double Data::CalcDistEuc(vector<double> *X, vector<double> *Y, int I, int J) {
	return sqrt(pow(X->at(I) - X->at(J), 2) + pow(Y->at(I) - Y->at(J), 2));
}

double Data::CalcDistAtt(vector<double> *X, vector<double> *Y, int I, int J) {
	// Calcula Pseudo Distancia Euclidiana
	double rij, tij, dij;

	rij = sqrt((pow(X->at(I) - X->at(J), 2) + pow(Y->at(I) - Y->at(J), 2)) / 10);
	tij = floor(rij + 0.5);

	if (tij < rij)
		dij = tij + 1;
	else
		dij = tij;

	return dij;
}

void Data::CalcLatLong(vector<double> *X, vector<double> *Y, int n, vector<double> *latit, vector<double> *longit) {
	double PI = 3.141592, min;
	int deg;

	for (int i = 0; i < n; i++) {
		deg = (int)X->at(i);
		min = X->at(i) - deg;
		latit->at(i) = PI * (deg + 5.0 * min / 3.0) / 180.0;
	}

	for (int i = 0; i < n; i++) {
		deg = (int)Y->at(i);
		min = Y->at(i) - deg;
		longit->at(i) = PI * (deg + 5.0 * min / 3.0) / 180.0;
	}
}

double Data::CalcDistGeo(vector<double> *latit, vector<double> *longit, int I, int J) {
	double q1, q2, q3, RRR = 6378.388;

	q1 = cos(longit->at(I) - longit->at(J));
	q2 = cos(latit->at(I) - latit->at(J));
	q3 = cos(latit->at(I) + latit->at(J));

	return (int)(RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
}

string Data::getInstanceName() {  // Get the name of instance

	string::size_type loc = instaceName.find_last_of(".", instaceName.size());
	string::size_type loc2 = instaceName.find_last_of("/", instaceName.size());

	string instance;

	if (loc != string::npos) {
		instance.append(instaceName, loc2 + 1, loc - loc2 - 1);
	} else {
		instance.append(instaceName, loc2 + 1, instance.size());
	}

	return instance;
}

void Data::printMatrixDist() {
	for (int i = 0; i < getDimension(); i++) {
		for (int j = 0; j < getDimension(); j++) {
			cout << getDistance(i, j) << " ";
		}
		cout << endl;
	}
}
