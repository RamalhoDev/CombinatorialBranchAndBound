#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<vector<double>> vvi;
typedef vector<ii> vii;

class Kruskal {
   public:
	Kruskal(vvi *dist, shared_ptr<vector<double>> lambda);

	double MST(int nodes);
	vii getEdges();

   private:
	priority_queue<pair<double, ii>> graph;
	vector<int> pset;
	vii edges;

	void initDisjoint(int n);
	int findSet(int i);
	void unionSet(int i, int j);
	bool isSameSet(int i, int j);
};

#endif