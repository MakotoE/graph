#ifndef GRAPH__ADJACENCY_MATRIX_H_
#define GRAPH__ADJACENCY_MATRIX_H_

#include "visited.h"
#include <vector>
#include <cmath>
#include <list>
#include <unordered_set>
#include <ostream>

class AdjacencyMatrix {
public:
	class Iterator {
	public:
		static Iterator end() {
			Iterator result({});
			result._queue = {};
			result._curr = {-1, -1};
			return result;
		}

		Iterator(const AdjacencyMatrix& matrix)
			: _graph(matrix)
			  , _queue({0}) {
			operator++();
		}

		Iterator& operator++() {
			while (!_queue.empty()) {
				size_t node_a = _queue.front();
				for (size_t i = 0; i < _graph.node_count() - std::get<1>(_curr); ++i) {
					size_t node_b = i + std::get<1>(_curr);
					if (_graph.contains_edge(node_a, node_b)
						// Edge has not been visited
						&& _visited.insert(Visited{node_a, node_b}).second
					) {
						_queue.push_back(node_b);
						_curr = {node_a, node_b};
						return *this;
					}

					if (_graph.contains_edge(node_b, node_a)
						&& _visited.insert(Visited{node_b, node_a}).second
						) {
						_curr = {node_b, node_a};
						return *this;
					}
				}
				_queue.pop_front();
			}
			_curr = {-1, -1};
			return *this;
		}

		std::tuple<size_t, size_t> operator*() {
			return _curr;
		}

		bool operator==(const Iterator& rhs) const {
			return std::tie(_queue, _curr) == std::tie(rhs._queue, rhs._curr);
		}

		bool operator!=(const Iterator& rhs) const {
			return !(rhs == *this);
		}

	private:
		const AdjacencyMatrix& _graph;
		std::list<size_t> _queue;
		std::unordered_set<Visited> _visited;
		std::tuple<size_t, size_t> _curr;
	};

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
		return std::sqrt(_matrix.size());
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

	Iterator begin() const {
		return {*this};
	}

	Iterator end() const {
		return Iterator::end();
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
