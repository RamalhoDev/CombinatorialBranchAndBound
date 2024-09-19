#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include <list>
#include <memory>
#include <vector>

#include "Data.h"
#include "Node.hpp"
#include "hungarian.h"

using namespace std;

class BranchAndBound {
	Data* data;
	shared_ptr<RelaxationSolver> solver;

   public:
	BranchAndBound(Data* data, shared_ptr<RelaxationSolver> solver);
	shared_ptr<vector<pair<int,int>>> solve(bool useDFS = true);
};

#endif  // !BRANCHANDBOUND_H
