#include <iostream>
#include <vector>
#include <algorithm>

int n, m;

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> reversed_graph;

std::vector<bool> visited;
std::vector<int> order;
std::vector<int> component;

void dfs1(int node)
{
    visited[node] = true;

    for (int next : graph[node])
    {
        if (!visited[next])
        {
            dfs1(next);
        }
    }

    // node is finished, push into order
    order.push_back(node);
}

void dfs2(int node, int component_id)
{
    component[node] = component_id;

    for (int next : reversed_graph[node])
    {
        if (component[next] == -1)
        {
            dfs2(next, component_id);
        }
    }
}

int main()
{
    std::cin >> n;
    std::cin >> m;

    graph.assign(n + 1, {});
    reversed_graph.assign(n + 1, {});

    for (int i = 0; i < m; i++)
    {
        int a, b;
        std::cin >> a >> b;

        graph[a].push_back(b);
        reversed_graph[b].push_back(a);
    }

    // First pass:
    // run DFS on original graph
    // and store nodes by finishing time
    visited.assign(n + 1, false);

    for (int node = 1; node <= n; node++)
    {
        if (!visited[node])
        {
            dfs1(node);
        }
    }

    // Second pass:
    // run DFS on reversed graph
    // in reverse finishing order
    component.assign(n + 1, -1);

    int component_count = 0;

    std::reverse(order.begin(), order.end());

    for (int node : order)
    {
        if (component[node] == -1)
        {
            dfs2(node, component_count);
            component_count++;
        }
    }

    // component[v] = SCC id of vertex v
    // component_count = total number of SCCs

    std::vector<int> outdegree(component_count, 0);
    std::vector<int> representative(component_count, -1);

    for (int node = 1; node <= n; node++)
    {
        representative[component[node]] = node;
    }

    // Build condensation graph outdegree
    for (int from = 1; from <= n; from++)
    {
        for (int to : graph[from])
        {
            int comp_from = component[from];
            int comp_to = component[to];

            if (comp_from != comp_to)
            {
                outdegree[comp_from]++;
            }
        }
    }

    // Sink SCCs have outdegree 0
    std::vector<int> stations;

    for (int comp = 0; comp < component_count; comp++)
    {
        if (outdegree[comp] == 0)
        {
            stations.push_back(representative[comp]);
        }
    }

    std::cout << stations.size() << '\n';

    for (int station : stations)
    {
        std::cout << station << '\n';
    }

    std::cout << '\n';

    return 0;
}