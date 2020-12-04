#ifndef GRAPH__ADJACENCY_LIST_H_
#define GRAPH__ADJACENCY_LIST_H_

#include "iterator.h"
#include <vector>
#include <unordered_set>
#include <list>
#include <ostream>

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

	Iterator<AdjacencyList, Traversal::BreadthFirst> begin() const {
		return Iterator<AdjacencyList, Traversal::BreadthFirst>(*this);
	}

	Iterator<AdjacencyList, Traversal::BreadthFirst> end() const {
		return Iterator<AdjacencyList, Traversal::BreadthFirst>::end();
	}

	Iterator<AdjacencyList, Traversal::DepthFirst> begin_depth_iter() const {
		return Iterator<AdjacencyList, Traversal::DepthFirst>(*this);
	}

	Iterator<AdjacencyList, Traversal::DepthFirst> end_depth_iter() const {
		return Iterator<AdjacencyList, Traversal::DepthFirst>::end();
	}

	friend std::ostream& operator<<(std::ostream& os, const AdjacencyList& matrix) {
		os << "{ ";

		Iterator iter = matrix.begin();
		if (iter != matrix.end()) {
			os << "(" << std::get<0>(*iter) << ", " << std::get<1>(*iter) << ')';
			++iter;
		}

		for (; iter != matrix.end(); ++iter) {
			os << ", (" << std::get<0>(*iter) << ", " << std::get<1>(*iter) << ')';
		}
		return os << " }";
	}

private:
	std::vector<std::unordered_set<size_t>> _list;
};

#endif //GRAPH__ADJACENCY_LIST_H_
