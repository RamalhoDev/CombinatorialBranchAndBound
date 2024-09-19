#ifndef COMBINATORIALRELAXATION_HPP
#define COMBINATORIALRELAXATION_HPP

#include <algorithm>

#include "RelaxationSolver.hpp"
#include "hungarian.h"

class CombinatorialRelaxation : public RelaxationSolver {
	// hungarian_problem_t* ap;

	pair<bool, vector<int>> getSubtour(hungarian_problem_t* ap);
	shared_ptr<vector<int>> solution;
	pair<bool, vector<int>> subtourResult;

   public:
	static const int counter = 0;
	CombinatorialRelaxation();
	double solve(Data* data);
	shared_ptr<vector<pair<int, int>>> getForbiddenArcs();
	shared_ptr<vector<pair<int,int>>> getSolution() { 
		auto edges = make_shared<vector<pair<int,int>>>();
		for (size_t i = 1; i < solution->size(); i++){
			edges->push_back(make_pair(solution->at(i-1), solution->at(i)));
		}
		return edges;
	 }
};

#endif  // !COMBINATORIALRELAXATION_HPP