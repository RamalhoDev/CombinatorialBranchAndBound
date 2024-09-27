#ifndef SUBGRADIENTSOLUTION_HPP
#define SUBGRADIENTSOLUTION_HPP

#include <memory>
#include <vector>
using namespace std;

class SubgradientSolution {
	double lb;
	bool feasible;
	vector<pair<int, int>> edges;
	vector<vector<pair<int, int>>> adjacencyList;
	int higherDegreeVertex;
	vector<double> penalizer;
	double penalizerCost;

   public:
	SubgradientSolution(double lb, vector<pair<int, int>> edges, int dimension);
	shared_ptr<vector<pair<int, int>>> getForbiddenArcs();
	vector<pair<int, int>> getEdges() { return edges; }
	double getLowerBound() { return lb; }
	vector<double> getPenalizer() { return penalizer; }
	bool isSolutionFeasible(shared_ptr<vector<double>> lambda);
	double getPenalizerCost() { return penalizerCost; }
};

#endif  // !SUBGRADIENTSOLUTION_HPP