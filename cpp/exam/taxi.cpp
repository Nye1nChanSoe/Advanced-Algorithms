#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Order
{
    int start_time; // minutes
    int from_x;
    int from_y;
    int to_x;
    int to_y;
};

int toMinutes(const std::string &time)
{
    int hour = std::stoi(time.substr(0, 2));
    int minute = std::stoi(time.substr(3, 2));

    return hour * 60 + minute;
}

int distance(int ax, int ay, int bx, int by)
{
    // |a-c| + |b-d|
    return std::abs(ax - bx) + std::abs(ay - by);
}

int finishTime(const Order &order)
{
    return order.start_time + distance(order.from_x, order.from_y, order.to_x, order.to_y);
}

bool canDoAfter(const Order &first, const Order &second)
{
    // first order finish time
    int first_finish_time = finishTime(first);

    // travel time from first drop-off point to second pick-up point
    int travel_to_next = distance(first.to_x, first.to_y, second.from_x, second.from_y);

    // taxi must arrive at least 1 minute before second order starts
    return first_finish_time + travel_to_next < second.start_time;
}

// Kuhn algorithm
bool tryMatch(
    int order,
    const std::vector<std::vector<int>> &graph,
    std::vector<int> &matched_right,
    std::vector<bool> &visited)
{
    for (int next_order : graph[order])
    {
        if (visited[next_order])
            continue;

        visited[next_order] = true;

        // if next_order is free
        // or we can reassign its current matched order
        if (matched_right[next_order] == -1 ||
            tryMatch(matched_right[next_order], graph, matched_right, visited))
        {
            matched_right[next_order] = order;
            return true;
        }
    }

    return false;
}

int main()
{
    // M: number of taxi orders
    int M;
    std::cin >> M;

    std::vector<Order> orders(M);

    for (int i = 0; i < M; i++)
    {
        std::string time;
        std::cin >> time;

        // 08:05 -> covert to minutes -> 485
        orders[i].start_time = toMinutes(time);

        // (a, b) and (c, d)
        std::cin >> orders[i].from_x >> orders[i].from_y;
        std::cin >> orders[i].to_x >> orders[i].to_y;
    }

    // graph[i] contains all orders that can be done after order i
    std::vector<std::vector<int>> graph(M);
    for (int i = 0; i < M; i++)
    {
        for (int j = i + 1; j < M; j++)
        {
            if (canDoAfter(orders[i], orders[j]))
            {
                graph[i].push_back(j);
            }
        }
    }

    // bipartite matching:
    // left side = orders as previous orders
    // right side = orders as next orders
    std::vector<int> matched_right(M, -1);

    int maximum_matching = 0;

    for (int i = 0; i < M; i++)
    {
        std::vector<bool> visited(M, false);

        if (tryMatch(i, graph, matched_right, visited))
        {
            maximum_matching++;
        }
    }

    // Minimum path cover in DAG = number of nodes - maximum matching
    int minimum_taxis = M - maximum_matching;

    std::cout << minimum_taxis << std::endl;

    return 0;
}