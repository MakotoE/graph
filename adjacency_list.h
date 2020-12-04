#ifndef GRAPH__ADJACENCY_LIST_H_
#define GRAPH__ADJACENCY_LIST_H_

#include <vector>
#include <unordered_set>

class AdjacencyList {
public:
	AdjacencyList() = default;

	AdjacencyList(const std::initializer_list<std::tuple<size_t, size_t>>& list) : AdjacencyList() {
		for (auto& node : list) {
			insert_edge(std::get<0>(node), std::get<1>(node));
		}
	}

	void insert_edge(size_t node_a, size_t node_b) {
		reserve(node_a + 1);
		_list[node_a].insert(node_b);
	}

	size_t node_count() const {
		return _list.size();
	}

	bool contains_edge(size_t node_a, size_t node_b) const {
		if (node_a >= _list.size()) {
			return false;
		}
		return _list[node_a].find(node_b) != _list[node_a].end();
	}

	void reserve(size_t new_node_count) {
		_list.resize(std::max(_list.size(), new_node_count));
	}
private:
	std::vector<std::unordered_set<size_t>> _list;
};

#endif //GRAPH__ADJACENCY_LIST_H_
