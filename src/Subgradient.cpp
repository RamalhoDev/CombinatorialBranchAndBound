#include "../include/Subgradient.hpp"

double Subgradient::solve(Data *data, shared_ptr<vector<double>> previousLambdas) {
	double e = 1, bestCost = 0;
	int k = 0;
	auto lambda = make_shared<vector<double>>(*previousLambdas);

	while (1) {
		auto kruskal = make_shared<Kruskal>(data->getMatrixCostPointer(), lambda);
		auto solution = getOneTree(data, kruskal, lambda);
		double cost = solution->getLowerBound();

		if (solution->isSolutionFeasible(lambda) && !bestSolution->isSolutionFeasible(bestLambdas)) {
			ub = cost;
		}

		if (cost > bestCost || solution->isSolutionFeasible(lambda) && !bestSolution->isSolutionFeasible(bestLambdas)) {
			bestCost = cost;
			bestSolution = solution;
			bestLambdas = lambda;
			k = 0;
		} else {
			k = k + 1;
			if (k > kMax) {
				k = 0;
				e = e / 2;
			}
		}

		// cout << (solution->isSolutionFeasible(lambda)) << "\n";
		auto penalizer = solution->getPenalizer();
		double u = e * (ub - cost) / solution->getPenalizerCost();
		updateLambda(lambda, u, penalizer);
		// for (size_t i = 0; i < lambda->size(); i++) {
		// 	cout << lambda->at(i) << " ";
		// }
		// cout << "\n";
		if (e < 0.000001 || cost > ub || (solution->isSolutionFeasible(lambda))) break;
	}

	return bestCost;
}

shared_ptr<vector<pair<int, int>>> Subgradient::getForbiddenArcs() { return this->bestSolution->getForbiddenArcs(); }

shared_ptr<SubgradientSolution> Subgradient::getOneTree(Data *data, shared_ptr<Kruskal> kruskal, shared_ptr<vector<double>> lambda) {
	int dimension = data->getDimension();
	// evaluate cost
	auto lb = kruskal->MST(dimension);
	lb += data->getDistance(0, data->getFirstClosest()) + data->getDistance(0, data->getSecondClosest()) - lambda->at(data->getFirstClosest()) -
	      lambda->at(data->getSecondClosest());
	for (size_t i = 1; i < lambda->size(); i++) {
		lb += 2 * lambda->at(i);
	}

	// get solution edges
	auto solutionEdges = kruskal->getEdges();
	bool feasible = true;
	vector<vector<pair<int, int>>> adjacencyList = vector<vector<pair<int, int>>>(data->getDimension(), vector<pair<int, int>>());
	for (size_t i = 0; i < solutionEdges.size(); i++) {
		adjacencyList[solutionEdges[i].first].push_back(solutionEdges[i]);
		adjacencyList[solutionEdges[i].second].push_back(solutionEdges[i]);
		if ((adjacencyList[solutionEdges[i].first].size() > 2) || (adjacencyList[solutionEdges[i].second].size() > 2)) feasible = false;
	}

	auto indexCostDepot = vector<int>(dimension);
	iota(indexCostDepot.begin(), indexCostDepot.end(), 0);
	sort(indexCostDepot.begin(), indexCostDepot.end(),
	     [data, lambda](const int &a, int &b) { return data->getDistance(0, a) - lambda->at(a) < data->getDistance(0, b) - lambda->at(b); });
	int firstClosest = indexCostDepot[0];
	int secondClosest = indexCostDepot[1];
	// sort(indexCostDepot.begin(), indexCostDepot.end(), [this](const int &a, int &b) { return getDistance(0, a) < getDistance(0, b); });

	solutionEdges.push_back(make_pair(0, firstClosest));
	solutionEdges.push_back(make_pair(secondClosest, 0));

	return make_shared<SubgradientSolution>(lb, solutionEdges, dimension);
}

void Subgradient::updateLambda(shared_ptr<vector<double>> lambda, double u, vector<int> penalizer) {
	for (size_t i = 0; i < lambda->size(); i++) {
		lambda->at(i) += u * penalizer[i];
	}
}