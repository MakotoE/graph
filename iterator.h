#ifndef GRAPH__ITERATOR_H_
#define GRAPH__ITERATOR_H_

#include <tuple>
#include <list>
#include <unordered_set>

class Visited {
public:
	size_t a;
	size_t b;

	bool operator==(const Visited& rhs) const {
		return std::tie(a, b) == std::tie(rhs.a, rhs.b);
	}
};

namespace std {
template<>
struct [[maybe_unused]] hash<Visited> {
	std::size_t operator()(const Visited& key) const {
		return key.a * 31 + key.b;
	}
};
}

template <class Graph>
class Iterator {
public:
	static Iterator end() {
		Iterator result({});
		result._queue = {};
		result._curr = {-1, -1};
		return result;
	}

	explicit Iterator(const Graph& matrix)
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
	const Graph& _graph;
	std::list<size_t> _queue;
	std::unordered_set<Visited> _visited;
	std::tuple<size_t, size_t> _curr;
};

#endif //GRAPH__ITERATOR_H_
