#ifndef SUBGRADIENT_H
#define SUBGRADIENT_H

#include <list>
#include <unordered_map>

#include "Kruskal.h"
#include "RelaxationSolver.hpp"
#include "SubgradientSolution.hpp"

class Subgradient : public RelaxationSolver {
	int kMax;
	shared_ptr<Kruskal> kruskal;
	shared_ptr<SubgradientSolution> bestSolution;
	shared_ptr<SubgradientSolution> getOneTree(int dimension);

   public:
	Subgradient(int kMax) { this->kMax = kMax; }

	double solve(Data* data);
	shared_ptr<vector<pair<int, int>>> getForbiddenArcs();
	shared_ptr<vector<int>> getSolution() { return; }
};

#endif  // !SUBGRADIENT_H