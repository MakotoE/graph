#ifndef GRAPH__ADJACENCY_LIST_H_
#define GRAPH__ADJACENCY_LIST_H_

#include "visited.h"
#include <vector>
#include <unordered_set>
#include <list>
#include <ostream>

class AdjacencyList {
public:
	class Iterator {
	public:
		static Iterator end() {
			Iterator result({});
			result._queue = {};
			result._curr = {-1, -1};
			return result;
		}

		Iterator(const AdjacencyList& matrix)
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
		const AdjacencyList& _graph;
		std::list<size_t> _queue;
		std::unordered_set<Visited> _visited;
		std::tuple<size_t, size_t> _curr;
	};

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

	Iterator begin() const {
		return {*this};
	}

	Iterator end() const {
		return Iterator::end();
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
