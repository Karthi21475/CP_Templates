class Dsu {
    vector<int> size, parent;

public:
    Dsu(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(int a, int b) {
        int root1 = find_set(a);
        int root2 = find_set(b);
        if (root1 != root2) {
            if (size[root1] < size[root2])
                swap(root1, root2);
            parent[root2] = root1;
            size[root1] += size[root2];
        }
    }
};
