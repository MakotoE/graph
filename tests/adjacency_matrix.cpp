#include <gtest/gtest.h>
#include "../adjacency_matrix.h"

TEST(AdjacencyMatrix, contains_edge) {
	struct Test {
		std::initializer_list<std::tuple<size_t, size_t>> edges;
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
			{{0, 2}},
			0,
			1,
			false,
		},
		{
			{{1, 2}},
			1,
			2,
			true,
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
		AdjacencyMatrix graph(tests[i].edges);
		EXPECT_EQ(graph.contains_edge(tests[i].node_a, tests[i].node_b), tests[i].expected) << i;
	}
}

TEST(AdjacencyMatrix, iterator) {
	{
		AdjacencyMatrix graph;
		EXPECT_EQ(graph.begin(), graph.end());
	}
	{
		AdjacencyMatrix graph({
		  {0, 1},
		  {1, 2},
		  {0, 2},
		  {1, 0},
		  {2, 3},
		  {3, 0},
		});
		std::vector<std::tuple<size_t, size_t>> expected{
			{0, 1},
			{0, 2},
			{0, 3},
			{2, 3},
			{1, 2},
		};
		size_t i = 0;
		for (auto edge : graph) {
			EXPECT_EQ(edge, expected[i]) << i;
			++i;
		}
	}
}