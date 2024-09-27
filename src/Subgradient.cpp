#include "../include/Subgradient.hpp"

double Subgradient::solve(Data *data, shared_ptr<vector<double>> previousLambdas) {
	double e = 1;
	int k = 0;

	double bestCost = 0;
	auto lambda = make_shared<vector<double>>(*previousLambdas);

	while (1) {
		auto kruskal = make_shared<Kruskal>(data->getMatrixCostPointer(), lambda);
		auto solution = getOneTree(data, kruskal, lambda);
		double cost = solution->getLowerBound();

		if (cost > bestCost) {
			bestCost = cost;
			bestSolution = solution;
			bestLambdas = lambda;
			// continue;
		} else {
			k = k + 1;
			if (k > kMax) {
				k = 0;
				e = e / 2;
			}
		}

		auto penalizer = solution->getPenalizer();
		double u = e * (ub - cost) / solution->getPenalizerCost();
		updateLambda(lambda, u, penalizer);
		if (e < 0.000001 || cost > ub || (solution->isSolutionFeasible(lambda))) break;
	}

	return bestCost;
}

shared_ptr<vector<pair<int, int>>> Subgradient::getForbiddenArcs() { return this->bestSolution->getForbiddenArcs(); }

shared_ptr<SubgradientSolution> Subgradient::getOneTree(Data *data, shared_ptr<Kruskal> kruskal, shared_ptr<vector<double>> lambda) {
	int dimension = data->getDimension();
	auto lb = kruskal->MST(dimension);
	lb += data->getDistance(0, data->getFirstClosest()) + data->getDistance(0, data->getSecondClosest()) - lambda->at(data->getFirstClosest()) -
	      lambda->at(data->getSecondClosest());
	for (size_t i = 1; i < lambda->size(); i++) {
		lb += 2 * lambda->at(i);
	}

	auto solutionEdges = kruskal->getEdges();

	solutionEdges.push_back(make_pair(0, data->getFirstClosest()));
	solutionEdges.push_back(make_pair(data->getSecondClosest(), 0));

	return make_shared<SubgradientSolution>(lb, solutionEdges, dimension);
}

void Subgradient::updateLambda(shared_ptr<vector<double>> lambda, double u, vector<double> penalizer) {
	for (size_t i = 0; i < lambda->size(); i++) {
		lambda->at(i) = lambda->at(i) + u * penalizer[i];
	}
}