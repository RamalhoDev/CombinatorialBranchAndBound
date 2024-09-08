#include "../include/Node.hpp"

Node::Node(Data *data, shared_ptr<RelaxationSolver> solver, vector<pair<int, int>> forbiddenArcs, double lowerBound) : data(Data(data)) {
	this->forbiddenArcs = forbiddenArcs;
	this->lowerBound = lowerBound;
	for (pair<int, int> arc : forbiddenArcs) {
		this->data.forbidArc(arc.first, arc.second);
	}
	this->isFeasible = false;
	this->solver = solver;
}

void Node::solve() { this->lowerBound = solver->solve(&data); }

Node::~Node() {}

vector<Node> Node::getSubProblems() {
	vector<Node> nodes = vector<Node>();

	auto edgesForbidden = solver->getForbiddenArcs();
	for (auto edge : *edgesForbidden) {
		auto updatedForbidenArcs = forbiddenArcs;
		updatedForbidenArcs.push_back(edge);
		nodes.push_back(Node(&this->data, this->solver, updatedForbidenArcs));
	}
	if (!nodes.size()) this->isFeasible = true;
	return nodes;
}
