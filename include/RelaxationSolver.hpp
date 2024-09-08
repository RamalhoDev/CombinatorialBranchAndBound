#ifndef RELAXATIONSOLVER_HPP
#define RELAXATIONSOLVER_HPP

#include <memory>
#include <vector>

#include "Data.h"

using namespace std;

class RelaxationSolver {
   protected:
	shared_ptr<Data> data;

   public:
	RelaxationSolver() {}
	virtual double solve(Data* data) {}
	virtual shared_ptr<vector<pair<int, int>>> getForbiddenArcs() {}
	virtual shared_ptr<vector<int>> getSolution() {}
	virtual ~RelaxationSolver() {}
};

#endif  // !RELAXATIONSOLVER_HPP