#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <list>
#include <utility>
#include <vector>

#include "Data.h"
#include "hungarian.h"
using namespace std;

class Node {
	bool feasible;
	double lowerBound;
	vector<vector<int>> subtours;
	vector<pair<int, int>> forbiddenArcs;
	Data data;
	hungarian_problem_t* ap;
	bool isFeasible;

	void getSubtours();

   public:
	Node(Data* data, vector<pair<int, int>> forbiddenArcs, double lowerBound = 0);
	~Node();
	void solve();
	vector<Node> getSubProblems();
	bool getIsFeasible() { return isFeasible; }
	double getLowerBound() { return lowerBound; }
	vector<int> getSubtour(int idx) { return subtours[idx]; }
	void printSubProblems() {
		for (auto&& forbArc : forbiddenArcs) {
			cout << "(" << forbArc.first << "," << forbArc.second << "),";
		}
		cout << "\n";
	}
	void freeHungarian() { hungarian_free(ap); }
};

#endif  // !NODE_H