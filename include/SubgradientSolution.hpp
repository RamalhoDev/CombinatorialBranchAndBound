#ifndef SUBGRADIENTSOLUTION_HPP
#define SUBGRADIENTSOLUTION_HPP

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class SubgradientSolution {
	double lb;
	bool feasible;
	vector<pair<int, int>> edges;
	vector<vector<pair<int, int>>> adjacencyList;
	int higherDegreeVertex;
	vector<int> penalizer;
	int penalizerCost;

   public:
	SubgradientSolution(double lb, vector<pair<int, int>> edges, int dimension);
	shared_ptr<vector<pair<int, int>>> getForbiddenArcs();
	vector<pair<int, int>> getEdges() { return edges; }
	double getLowerBound() { return lb; }
	vector<int> getPenalizer() { return penalizer; }
	bool isSolutionFeasible(shared_ptr<vector<double>> lambda);
	int getPenalizerCost() { return (penalizerCost == 0) ? 1 : penalizerCost; }
};

#endif  // !SUBGRADIENTSOLUTION_HPP