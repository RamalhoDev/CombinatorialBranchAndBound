#include "../include/Subgradient.hpp"

double Subgradient::solve(Data *data) {
	this->kruskal = make_shared<Kruskal>(data->getMatrixCostPointer());
	getOneTree(data->getDimension());
	double bestCost = 0;
	double e = 1;
	int k = 0;
	double ub = INFINITE;
	double bestCost = INFINITE;
	vector<int> lambda = vector<int>(data->getDimension(), 0);
	vector<int> bestLambda;
	while (1) {
		auto solution = getOneTree(data->getDimension());
		double cost = solution->getLowerBound();
		double u = e * (ub - cost);

		if (cost > bestCost) {
			bestCost = cost;
			bestSolution = solution;
			bestLambda = lambda;
			continue;
		}

		k = k + 1;
		if (k > kMax) {
			k = 0;
			e = e / 2;
		}

		if (e < 0.001) break;
	}

	return bestCost;
}
shared_ptr<vector<pair<int, int>>> Subgradient::getForbiddenArcs() { return this->bestSolution->getForbiddenArcs(); }

shared_ptr<SubgradientSolution> Subgradient::getOneTree(int dimension) {
	auto lb = kruskal->MST(dimension - 1);
	auto solutionEdges = kruskal->getEdges();

	return make_shared<SubgradientSolution>(lb, solutionEdges, dimension);
}

// Resolver o mst
// Criar lista de adjacências ok
// Criar flag para identificar uma solução inviável na hora de construir lista de adjacências ok
// Ordenar listas pela quantidade de arcos ok
// Retornar arcos a serem excluídos, se for inviável ok
// Se for viável, salvar arcos para reconstruir solução

// Retornar lista de lambdas para execução do nó filho
// Resolver multiplicação de matrizes
// Calcular custo da solução penalizada: preciso dos lambdas