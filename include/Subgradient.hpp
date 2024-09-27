#ifndef SUBGRADIENT_H
#define SUBGRADIENT_H

#include <list>
#include <unordered_map>

#include "Kruskal.h"
#include "RelaxationSolver.hpp"
#include "SubgradientSolution.hpp"

class Subgradient : public RelaxationSolver {
	int kMax;
	double ub;
	shared_ptr<SubgradientSolution> bestSolution;
	shared_ptr<SubgradientSolution> getOneTree(Data* data, shared_ptr<Kruskal> kruskal, shared_ptr<vector<double>> lambda);
	void updateLambda(shared_ptr<vector<double>> lambda, double u, vector<int> penalizer);
	shared_ptr<vector<double>> bestLambdas;

   public:
	Subgradient(int kMax, double ub) {
		this->kMax = kMax;
		this->ub = ub;
	}

	double solve(Data* data, shared_ptr<vector<double>> previousLambdas);
	shared_ptr<vector<pair<int, int>>> getForbiddenArcs();
	shared_ptr<vector<pair<int, int>>> getSolution() { return make_shared<vector<pair<int, int>>>(bestSolution->getEdges()); }
	shared_ptr<vector<double>> getLambdas() { return bestLambdas; }
};

#endif  // !SUBGRADIENT_H