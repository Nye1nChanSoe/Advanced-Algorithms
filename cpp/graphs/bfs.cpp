#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

std::unordered_map<char, std::vector<char>> graph;
std::unordered_map<char, bool> visited;
std::unordered_map<char, char> parent;
std::queue<char> q;

void bfs(char node)
{
    visited[node] = true;
    q.push(node);

    while (!q.empty())
    {
        char current = q.front();
        q.pop();

        std::cout << "Visit: " << current << '\n';

        for (char neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                // // remember who discover the neighbour
                // parent[neighbor] = current;

                q.push(neighbor);

                // std::cout << "  Queueing: " << neighbor << '\n';
            }
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

    bfs('A');

    std::cout << "Shortest Path\n";
    for (auto &[neighbour, parent] : parent)
    {
        std::cout << "Parent-" << parent << ": " << neighbour << "\n";
    }
    std::cout << std::endl;

    return 0;
}