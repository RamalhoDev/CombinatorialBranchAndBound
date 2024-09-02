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

   public:
	BranchAndBound(Data* data);
	vector<int> solve(bool useDFS = true);
};

#endif  // !BRANCHANDBOUND_H
