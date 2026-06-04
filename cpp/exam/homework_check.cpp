#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // N number of students
    // k top-scored students who are absent
    int N, k;
    std::cin >> N >> k;

    // the score of students in order of their ids
    // pair: {score: id}
    std::vector<std::pair<int, int>> scores(N);

    for (int i = 0; i < N; i++)
    {
        std::cin >> scores[i].first;
        scores[i].second = i;
    }

    // sort descending order for score 
    // and ascending order for id
    std::sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    } );

    std::cout << scores[k].second << std::endl;

    return 0;
}