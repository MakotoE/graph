#ifndef GRAPH__VISITED_H_
#define GRAPH__VISITED_H_

#include <tuple>

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
struct hash<Visited> {
	std::size_t operator()(const Visited& key) const {
		return key.a * 31 + key.b;
	}
};
}

#endif //GRAPH__VISITED_H_
