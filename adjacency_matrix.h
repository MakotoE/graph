#ifndef GRAPH__ADJACENCY_MATRIX_H_
#define GRAPH__ADJACENCY_MATRIX_H_

#include "iterator.h"
#include <vector>
#include <cmath>
#include <list>
#include <unordered_set>
#include <ostream>

class AdjacencyMatrix {
public:
	AdjacencyMatrix() = default;

	AdjacencyMatrix(const std::initializer_list<std::tuple<size_t, size_t>>& list)
		: AdjacencyMatrix() {
		for (auto& edge : list) {
			insert_edge(std::get<0>(edge), std::get<1>(edge));
		}
	}

	void insert_edge(size_t node_a, size_t node_b) {
		reserve(std::max(node_a, node_b) + 1);
		_matrix[node_a * node_count() + node_b] = true;
	}

	size_t node_count() const {
		return static_cast<size_t>(std::sqrt(_matrix.size()));
	}

	bool contains_edge(size_t node_a, size_t node_b) const {
		if (node_a >= node_count() || node_b >= node_count()) {
			return false;
		}

		return _matrix[node_count() * node_a + node_b];
	}

	void reserve(size_t new_node_count) {
		if (new_node_count < node_count()) {
			return;
		}

		std::vector<bool> new_matrix(new_node_count * new_node_count);
		for (size_t row = 0; row < node_count(); ++row) {
			for (size_t col = 0; col < node_count(); ++col) {
				new_matrix[new_node_count * row + col] = _matrix[node_count() * row + col];
			}
		}
		_matrix = std::move(new_matrix);
	}

	Iterator<AdjacencyMatrix, Traversal::BreadthFirst> begin() const {
		return Iterator<AdjacencyMatrix, Traversal::BreadthFirst>(*this);
	}

	Iterator<AdjacencyMatrix, Traversal::BreadthFirst> end() const {
		return Iterator<AdjacencyMatrix, Traversal::BreadthFirst>::end();
	}

	Iterator<AdjacencyMatrix, Traversal::DepthFirst> begin_depth_iter() const {
		return Iterator<AdjacencyMatrix, Traversal::DepthFirst>(*this);
	}

	Iterator<AdjacencyMatrix, Traversal::DepthFirst> end_depth_iter() const {
		return Iterator<AdjacencyMatrix, Traversal::DepthFirst>::end();
	}

	friend std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& matrix) {
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
	std::vector<bool> _matrix;
};

#endif //GRAPH__ADJACENCY_MATRIX_H_
