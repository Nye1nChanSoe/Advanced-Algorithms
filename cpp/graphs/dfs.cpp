#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

// TODO: topological sorting
// TODO: cycle detection in directed graph

// TODO: Bridges in the graph to get connected components by removing the specific edge
// TODO: Articulation point - the nodes
// TODO: Graph Condensation

std::unordered_map<char, std::vector<char>> graph;
std::unordered_map<char, bool> visited;

unsigned int n_components = 1;

// detect cycles
// connected components
// topological sorting -> DAGs
void dfs(char node)
{
    visited[node] = true;

    std::cout << "Visit: " << node << '\n';

    for (char neighbour : graph[node])
    {
        if (!visited[neighbour])
        {
            std::cout << "Going from " << node << " -> " << neighbour << '\n';

            dfs(neighbour);
            n_components += 1;

            std::cout << "<-- Backtracking to " << node << " from " << neighbour << "\n";
        }
    }
}

int main()
{
    // adjacency list
    graph['A'] = {'B', 'G'};
    graph['B'] = {'A', 'C', 'G'};
    graph['C'] = {'B'};
    graph['D'] = {'J', 'K'};
    graph['E'] = {'G', 'J', 'K'};
    graph['F'] = {'J'};
    graph['G'] = {'A', 'B', 'E'};
    graph['J'] = {'D', 'E', 'F'};
    graph['K'] = {'D', 'E'};

    std::cout << "Graph\n";
    for (auto &[node, neighbours] : graph)
    {
        std::cout << node << ": ";
        for (auto &item : neighbours)
        {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    dfs('A');
    std::cout << "Total components: " << n_components << std::endl;

    return 0;
}