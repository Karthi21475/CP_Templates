#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
    int n;
    vector<vector<int>> tree;

    MergeSortTree(const vector<int>& a) {
        n = (int)a.size();
        tree.resize(4 * n);
        build(a, 1, 0, n - 1);
    }

    void build(const vector<int>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = {a[l]};
            return;
        }

        int mid = (l + r) / 2;

        build(a, node * 2, l, mid);
        build(a, node * 2 + 1, mid + 1, r);

        tree[node].resize(
            tree[node * 2].size() +
            tree[node * 2 + 1].size()
        );

        merge(
            tree[node * 2].begin(),
            tree[node * 2].end(),
            tree[node * 2 + 1].begin(),
            tree[node * 2 + 1].end(),
            tree[node].begin()
        );
    }

    // Count elements <= x in range [ql, qr]
    int query(int node, int l, int r,
              int ql, int qr, int x) {

        // No overlap
        if (qr < l || r < ql)
            return 0;

        // Complete overlap
        if (ql <= l && r <= qr) {
            return upper_bound(
                tree[node].begin(),
                tree[node].end(),
                x
            ) - tree[node].begin();
        }

        int mid = (l + r) / 2;

        return query(node * 2, l, mid, ql, qr, x)
             + query(node * 2 + 1, mid + 1, r, ql, qr, x);
    }

    // Count elements <= x in [l, r]
    int countLE(int l, int r, int x) {
        return query(1, 0, n - 1, l, r, x);
    }

    // Count elements < x in [l, r]
    int countLT(int l, int r, int x) {
        return countLE(l, r, x - 1);
    }

    // Count elements >= x in [l, r]
    int countGE(int l, int r, int x) {
        return (r - l + 1) - countLT(l, r, x);
    }

    // Count elements > x in [l, r]
    int countGT(int l, int r, int x) {
        return (r - l + 1) - countLE(l, r, x);
    }

    // Count elements in [x, y] inside array range [l, r]
    int countInValueRange(int l, int r, int x, int y) {
        return countLE(l, r, y) - countLT(l, r, x);
    }

    // Minimum value >= x in [l, r]
    // Returns INT_MAX if no such value exists.
    int minGE(int node, int l, int r,
              int ql, int qr, int x) {

        if (qr < l || r < ql)
            return INT_MAX;

        if (ql <= l && r <= qr) {
            auto it = lower_bound(
                tree[node].begin(),
                tree[node].end(),
                x
            );

            if (it == tree[node].end())
                return INT_MAX;

            return *it;
        }

        int mid = (l + r) / 2;

        return min(
            minGE(node * 2, l, mid, ql, qr, x),
            minGE(node * 2 + 1, mid + 1, r, ql, qr, x)
        );
    }

    int minGE(int l, int r, int x) {
        return minGE(1, 0, n - 1, l, r, x);
    }

    // Maximum value <= x in [l, r]
    // Returns INT_MIN if no such value exists.
    int maxLE(int node, int l, int r,
              int ql, int qr, int x) {

        if (qr < l || r < ql)
            return INT_MIN;

        if (ql <= l && r <= qr) {
            auto it = upper_bound(
                tree[node].begin(),
                tree[node].end(),
                x
            );

            if (it == tree[node].begin())
                return INT_MIN;

            --it;
            return *it;
        }

        int mid = (l + r) / 2;

        return max(
            maxLE(node * 2, l, mid, ql, qr, x),
            maxLE(node * 2 + 1, mid + 1, r, ql, qr, x)
        );
    }

    int maxLE(int l, int r, int x) {
        return maxLE(1, 0, n - 1, l, r, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);

    for (int &x : a)
        cin >> x;

    MergeSortTree mst(a);

    int q;
    cin >> q;

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;

        // Example:
        // Count elements <= x in [l, r]
        cout << mst.countLE(l, r, x) << '\n';
    }

    return 0;
}
/*
mst.countLE(l, r, x);          // <= x
mst.countLT(l, r, x);          // < x
mst.countGE(l, r, x);          // >= x
mst.countGT(l, r, x);          // > x
mst.countInValueRange(l,r,x,y);// x <= a[i] <= y

mst.minGE(l, r, x);             // minimum >= x
mst.maxLE(l, r, x);             // maximum <= x
*/