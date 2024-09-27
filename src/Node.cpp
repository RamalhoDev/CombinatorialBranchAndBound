#include "../include/Node.hpp"

Node::Node(Data *data, shared_ptr<RelaxationSolver> solver, vector<pair<int, int>> forbiddenArcs, double lowerBound,
           shared_ptr<vector<double>> lambda)
    : data(Data(data)) {
	this->forbiddenArcs = forbiddenArcs;
	this->lowerBound = lowerBound;
	for (pair<int, int> arc : forbiddenArcs) {
		this->data.forbidArc(arc.first, arc.second);
		this->data.forbidArc(arc.second, arc.first);
	}
	this->data.updateClosest();
	this->isFeasible = false;
	this->solver = solver;
	this->bestLambdas = lambda;
	if (lambda == NULL) this->bestLambdas = make_shared<vector<double>>(data->getDimension(), 0);
}

void Node::solve() { this->lowerBound = solver->solve(&data, this->bestLambdas); }

Node::~Node() {}

vector<Node> Node::getSubProblems() {
	vector<Node> nodes = vector<Node>();

	auto edgesForbidden = solver->getForbiddenArcs();
	auto bestLambdas = solver->getLambdas();
	for (auto edge : *edgesForbidden) {
		auto updatedForbidenArcs = forbiddenArcs;
		updatedForbidenArcs.push_back(edge);
		nodes.push_back(Node(&this->data, this->solver, updatedForbidenArcs, 0, bestLambdas));
	}
	if (!nodes.size()) this->isFeasible = true;
	return nodes;
}
