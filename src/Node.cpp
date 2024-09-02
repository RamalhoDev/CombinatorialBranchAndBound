#include "../include/Node.hpp"

Node::Node(Data *data, vector<pair<int, int>> forbiddenArcs, double lowerBound) : data(Data(data)) {
	this->forbiddenArcs = forbiddenArcs;
	this->lowerBound = lowerBound;
	for (pair<int, int> arc : forbiddenArcs) {
		this->data.forbidArc(arc.first, arc.second);
	}
	this->isFeasible = false;
}

void Node::solve() {
	this->ap = new hungarian_problem_t();
	hungarian_init(ap, data.getMatrixCost(), data.getDimension(), data.getDimension(), HUNGARIAN_MODE_MINIMIZE_COST);
	this->lowerBound = hungarian_solve(ap);
	getSubtours();
	freeHungarian();
}

Node::~Node() {
	// cout << ap->num_cols << " " << ap->num_rows << " " << ap->cost << " " << ap->assignment << "\n";
	// freeHungarian();
	// delete data;
}

vector<Node> Node::getSubProblems() {
	vector<Node> nodes = vector<Node>();

	this->isFeasible = subtours.size() < 2 ? true : false;
	if (!isFeasible) {
		std::sort(subtours.begin(), subtours.end(), [](const vector<int> &a, const vector<int> &b) { return a.size() < b.size(); });

		for (size_t i = 0; i < subtours[0].size() - 1; i++) {
			auto updatedForbidenArcs = forbiddenArcs;
			updatedForbidenArcs.push_back(make_pair(subtours[0][i], subtours[0][i + 1]));
			nodes.push_back(Node(&this->data, updatedForbidenArcs));
		}
	}

	return nodes;
}

void Node::getSubtours() {
	this->subtours = vector<vector<int>>();
	vector<int> visited = vector<int>(ap->num_cols, 0);
	int count = 0;
	while (count < ap->num_rows) {
		if (!visited[count]) {
			int nextV = count;
			vector<int> tour = {nextV};
			while (!visited[nextV]) {
				visited[nextV] = 1;
				for (size_t i = 0; i < ap->num_rows; i++) {
					if (ap->assignment[nextV][i]) {
						nextV = i;
						tour.push_back(i);
						break;
					}
				}
			}
			this->subtours.push_back(tour);
		}
		count++;
	}
}