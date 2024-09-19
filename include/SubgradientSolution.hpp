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

   public:
	SubgradientSolution(double lb, vector<pair<int, int>> edges, int dimension);
	shared_ptr<vector<pair<int, int>>> getForbiddenArcs();
	double getLowerBound() { return lb; }
};

#endif  // !SUBGRADIENTSOLUTION_HPP