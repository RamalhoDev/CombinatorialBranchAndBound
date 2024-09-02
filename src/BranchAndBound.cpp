#include "../include/BranchAndBound.hpp"

BranchAndBound::BranchAndBound(Data* data) { this->data = data; }

vector<int> BranchAndBound::solve(bool useDFS) {
	vector<int> solution;

	double upperBound = INFINITE;
	auto tree = list<Node>();

	auto root = Node(data, {});
	tree.push_back(root);
	int count = 0;
	while (!tree.empty()) {
		// if (count == 10) break;
		Node currNode = useDFS ? tree.back() : tree.front();
		// currNode.printSubProblems();
		currNode.solve();
		if (useDFS) {
			tree.pop_back();
		} else {
			tree.pop_front();
		}
		// cout << "Custo: " << currNode.getLowerBound() << " UpperBound: " << upperBound << " \n";
		if (currNode.getLowerBound() < upperBound) {
			auto subproblems = currNode.getSubProblems();
			if (!currNode.getIsFeasible()) {
				tree.insert(tree.end(), subproblems.begin(), subproblems.end());
			} else {
				// cout << "Entrei atualizando UB Custo: " << currNode.getLowerBound() << " UpperBound: " << upperBound << " \n";
				upperBound = min(upperBound, currNode.getLowerBound());
				solution = currNode.getSubtour(0);
			}
		}

		// cout << tree.size() << "\n";
		// count++;
	}

	return solution;
}