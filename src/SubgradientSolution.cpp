#include "../include/SubgradientSolution.hpp"

SubgradientSolution::SubgradientSolution(double lb, vector<pair<int, int>> edges, int dimension) {
	this->edges = edges;
	this->lb = lb;

	this->feasible = true;
	int degree = 0;

	adjacencyList = vector<vector<pair<int, int>>>(dimension, vector<pair<int, int>>());
	for (size_t i = 0; i < edges.size(); i++) {
		adjacencyList[edges[i].first].push_back(edges[i]);
		adjacencyList[edges[i].second].push_back(edges[i]);
		if ((adjacencyList[edges[i].first].size() > 2) || (adjacencyList[edges[i].second].size() > 2)) feasible = false;

		if (adjacencyList[edges[i].first].size() > degree) {
			degree = adjacencyList[edges[i].first].size();
			higherDegreeVertex = edges[i].first;
		}
		if (adjacencyList[edges[i].second].size() > degree) {
			degree = adjacencyList[edges[i].second].size();
			higherDegreeVertex = edges[i].second;
		}
	}

	this->penalizer = vector<double>(dimension, 0);
	this->penalizerCost = 0;
	for (size_t i = 0; i < adjacencyList.size(); i++) {
		int degree = adjacencyList[i].size();
		int aux = (2 - degree);
		this->penalizer[i] = aux;
		this->penalizerCost += aux * aux;
	}
}

shared_ptr<vector<pair<int, int>>> SubgradientSolution::getForbiddenArcs() {
	auto forbiddenArcs = make_shared<vector<pair<int, int>>>();
	for (auto edge : adjacencyList[higherDegreeVertex]) {
		// if (!edge.first || !edge.second) continue;
		forbiddenArcs->push_back(edge);
	}
	return forbiddenArcs;
}

bool SubgradientSolution::isSolutionFeasible(shared_ptr<vector<double>> lambda) {
	bool _feasible = feasible;
	if (feasible) {
		for (size_t i = 0; i < adjacencyList.size(); i++) {
			if (lambda->at(i) * (2 - adjacencyList[i].size()) != 0.0000001) {
				return false;
			}
		}
	}
	return _feasible;
}