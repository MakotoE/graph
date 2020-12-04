#include "../adjacency_list.h"
#include <gtest/gtest.h>

TEST(AdjacencyList, contains_edge) {
	struct Test {
		std::initializer_list<std::tuple<size_t, size_t>> nodes;
		size_t node_a;
		size_t node_b;
		bool expected;
	};

	std::vector<Test> tests {
		{
			{},
			0,
			0,
			false,
		},
		{
			{{0, 1}},
			0,
			1,
			true,
		},
		{
			{{0, 0}},
			0,
			0,
			true,
		},
		{
			{{0, 1}},
			0,
			2,
			false,
		},
		{
			{{0, 1}, {1, 2}},
			0,
			2,
			false,
		},
		{
			{{0, 1}, {1, 2}, {0, 2}},
			0,
			2,
			true,
		},
		{
			{{1, 2}, {0, 1}},
			1,
			2,
			true,
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		AdjacencyList graph(tests[i].nodes);
		EXPECT_EQ(graph.contains_edge(tests[i].node_a, tests[i].node_b), tests[i].expected) << i;
	}
}