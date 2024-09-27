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
	virtual double solve(Data* data, shared_ptr<vector<double>> lambda) {}
	virtual shared_ptr<vector<pair<int, int>>> getForbiddenArcs() {}
	virtual shared_ptr<vector<pair<int, int>>> getSolution() {}
	virtual shared_ptr<vector<double>> getLambdas() { return make_shared<vector<double>>(); }
	virtual ~RelaxationSolver() {}
};

#endif  // !RELAXATIONSOLVER_HPP