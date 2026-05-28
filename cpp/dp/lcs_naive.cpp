#include <iostream>

// substring = sequence must be continuous
// subsequence = can skip characters: order must be same

// unlike substrings, subsequences are not required to
// occupy consecutive positions within the original sequences.

// Find the Longest Common Subsequence

void generateSubsequences(
    const std::string &s,
    int index,
    std::string current,
    std::vector<std::string> &subsequences)
{
    if (index == s.size())
    {
        subsequences.push_back(current);
        return;
    }

    // binary decisions: take or skip
    generateSubsequences(s, index + 1, current + s[index], subsequences);
    generateSubsequences(s, index + 1, current, subsequences);
}

bool isSubsequence(const std::string &small, const std::string &big)
{
    int i = 0;
    for (char c : big)
    {
        if (i < small.size() && small[i] == c)
            i++;
    }
    return i == small.size();
}

int main()
{
    std::string a = "ABCBDAB", b = "BDCAB";
    std::vector<std::string> subsequences;

    generateSubsequences(a, 0, "", subsequences);
    // 2^7 = 128 : binary tree with depth 7 of subsequences
    std::cout << "Total subsequences: " << subsequences.size() << "\n";

    // naviely loop and take the longest one
    std::string longest = "";
    for (const std::string &seq : subsequences)
    {
        if (isSubsequence(seq, b) && seq.size() > longest.size())
        {
            longest = seq;
        }
    }

    std::cout << "Longest Common Subsequence: " << longest << "\n";

    return 0;
}