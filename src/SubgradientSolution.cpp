#include "../include/SubgradientSolution.hpp"

SubgradientSolution::SubgradientSolution(double lb, vector<pair<int, int>> edges, int dimension) {
	this->edges = edges;
	this->lb = lb;

	this->feasible = true;
	int degree = 0;

	vector<vector<pair<int, int>>> adjacencyList = vector<vector<pair<int, int>>>(dimension, vector<pair<int, int>>());
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
}

shared_ptr<vector<pair<int, int>>> SubgradientSolution::getForbiddenArcs() {
	return make_shared<vector<pair<int, int>>>(this->adjacencyList[higherDegreeVertex]);
}