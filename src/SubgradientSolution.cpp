#include "../include/SubgradientSolution.hpp"

SubgradientSolution::SubgradientSolution(double lb, vector<pair<int, int>> edges, int dimension) {
	this->edges = edges;
	this->lb = lb;

	this->feasible = true;

	adjacencyList = vector<vector<pair<int, int>>>(dimension, vector<pair<int, int>>());
	for (size_t i = 0; i < edges.size(); i++) {
		adjacencyList[edges[i].first].push_back(edges[i]);
		adjacencyList[edges[i].second].push_back(edges[i]);
		if ((adjacencyList[edges[i].first].size() > 2) || (adjacencyList[edges[i].second].size() > 2)) feasible = false;
	}

	int degree = adjacencyList[1].size();
	higherDegreeVertex = 1;
	for (size_t i = 2; i < adjacencyList.size(); i++) {
		if (adjacencyList[i].size() > degree) {
			degree = adjacencyList[i].size();
			higherDegreeVertex = i;
		}
	}

	this->penalizer = vector<int>(dimension, 0);
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
	if (!feasible) {
		for (auto edge : adjacencyList[higherDegreeVertex]) {
			// if (!edge.first || !edge.second) continue;
			forbiddenArcs->push_back(edge);
			// forbiddenArcs->push_back(make_pair(edge.second, edge.first));
		}
	}
	return forbiddenArcs;
}

bool SubgradientSolution::isSolutionFeasible(shared_ptr<vector<double>> lambda) {
	if (feasible) {
		for (size_t i = 0; i < adjacencyList.size(); i++) {
			cout << lambda->at(i) * (2 - adjacencyList[i].size()) << " ";
			if (lambda->at(i) * (2 - adjacencyList[i].size()) != 0) {
				return false;
			}
		}
	}

	return feasible;
}