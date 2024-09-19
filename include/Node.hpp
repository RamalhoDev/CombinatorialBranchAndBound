#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <list>
#include <utility>
#include <vector>

#include "Data.h"
#include "RelaxationSolver.hpp"

using namespace std;

class Node {
	double lowerBound;
	vector<vector<int>> subtours;
	vector<pair<int, int>> forbiddenArcs;
	Data data;
	shared_ptr<RelaxationSolver> solver;

	bool isFeasible;

   public:
	Node(Data* data, shared_ptr<RelaxationSolver> solver, vector<pair<int, int>> forbiddenArcs, double lowerBound = 0);
	~Node();
	void solve();
	vector<Node> getSubProblems();
	bool getIsFeasible() { return isFeasible; }
	double getLowerBound() { return lowerBound; }
	shared_ptr<vector<pair<int,int>>> getSolution() { return solver->getSolution(); }
	void printSubProblems() {
		for (auto&& forbArc : forbiddenArcs) {
			cout << "(" << forbArc.first << "," << forbArc.second << "),";
		}
		cout << "\n";
	}
};

#endif  // !NODE_H