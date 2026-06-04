#include <iostream>
#include <vector>
#include <utility>

struct Operation
{
    bool type;
    int x;
    int y;
};

struct SegmentTree
{
    int n;
    std::vector<long long> tree;

    SegmentTree(const std::vector<int> &arr)
    {
        n = arr.size() - 1;
        tree.assign(4 * n, 0);
        build(arr, 1, 1, n);
    }

    long long signedValue(int index, int value)
    {
        // index 1 based
        // al - (al+1) + (al+2) - (al+3)
        if (index % 2 == 1)
            return value;
        return -value;
    }

    void build(const std::vector<int> &arr, int node, int left, int right)
    {
        if (left == right)
        {
            tree[node] = signedValue(left, arr[left]);
            return;
        }

        int mid = (left + right) / 2;

        build(arr, node * 2, left, mid);
        build(arr, node * 2 + 1, mid + 1, right);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int index, int value)
    {
        update(1, 1, n, index, value);
    }

    void update(int node, int left, int right, int index, int value)
    {
        if (left == right)
        {
            tree[node] = signedValue(index, value);
            return;
        }

        int mid = (left + right) / 2;

        if (index <= mid)
            update(node * 2, left, mid, index, value);
        else
            update(node * 2 + 1, mid + 1, right, index, value);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    long long query(int ql, int qr)
    {
        return query(1, 1, n, ql, qr);
    }

    long long query(int node, int left, int right, int ql, int qr)
    {
        if (qr < left || right < ql)
            return 0;

        if (ql <= left && right <= qr)
            return tree[node];

        int mid = (left + right) / 2;

        long long leftSum = query(node * 2, left, mid, ql, qr);
        long long rightSum = query(node * 2 + 1, mid + 1, right, ql, qr);

        return leftSum + rightSum;
    }
};

int main()
{
    // n the length of the array
    int n;
    std::cin >> n;

    // initial values of the array
    // index starts at 1 (1 <= i <= n) and (1 <= l <= r <= n)
    std::vector<int> arr(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    // m the number of operations
    int m;
    std::cin >> m;

    // operations of first and second types
    std::vector<Operation> operations(m);

    for (int i = 0; i < m; i++)
    {
        std::cin >> operations[i].type >> operations[i].x >> operations[i].y;
    }

    SegmentTree seg_tree(arr);

    for (int i = 0; i < m; i++)
    {
        if (operations[i].type == 0)
        {
            int index = operations[i].x;
            int value = operations[i].y;

            arr[index] = value;
            seg_tree.update(index, value);
        }
        else
        {
            int l = operations[i].x;
            int r = operations[i].y;

            long long result = seg_tree.query(l, r);

            // The leftmost element of the query must be positive.
            if (l % 2 == 0)
                result = -result;

            std::cout << result << "\n";
        }
    }

    return 0;
}