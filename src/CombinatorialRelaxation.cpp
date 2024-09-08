#include "../include/CombinatorialRelaxation.hpp"

CombinatorialRelaxation::CombinatorialRelaxation() {}

double CombinatorialRelaxation::solve(Data *data) {
	auto ap = hungarian_problem_t();
	hungarian_init(&ap, data->getMatrixCostPointer(), data->getDimension(), data->getDimension(), HUNGARIAN_MODE_MINIMIZE_COST);
	auto lb = hungarian_solve(&ap);
	subtourResult = getSubtour(&ap);
	hungarian_free(&ap);
	return lb;
}

shared_ptr<vector<pair<int, int>>> CombinatorialRelaxation::getForbiddenArcs() {
	auto edges = make_shared<vector<pair<int, int>>>();
	if (!subtourResult.first) {
		auto subtour = &subtourResult.second;

		for (size_t i = 0; i < subtour->size() - 1; i++) {
			edges->push_back(make_pair(subtour->at(i), subtour->at(i + 1)));
		}
	} else
		this->solution = make_shared<vector<int>>(subtourResult.second);

	return edges;
}

pair<bool, vector<int>> CombinatorialRelaxation::getSubtour(hungarian_problem_t *ap) {
	auto subtours = vector<vector<int>>();
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
			subtours.push_back(tour);
		}
		count++;
	}
	bool feasible = subtours.size() < 2 ? true : false;
	if (!feasible) sort(subtours.begin(), subtours.end(), [](const vector<int> &a, const vector<int> &b) { return a.size() < b.size(); });
	return make_pair(feasible, subtours[0]);
}