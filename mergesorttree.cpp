struct segment
{
    int n;

    // Normal segment tree
    vector<int> tree;

    // Merge Sort Tree
    vector<vector<int>> seg;

    segment(int n)
    {
        this->n = n;
        tree.resize(4 * n);
        seg.resize(4 * n);
    }

    // ============================================================
    // NORMAL SEGMENT TREE
    // ============================================================

    int merge(int a, int b){
        return a + b; //the operation you want to do
    }

    void build(vector<int> &arr, int node, int start, int end)
    {
        if (start == end){
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) >> 1;

        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, int val)
    {
        if (start == end)
        {
            tree[node] = val;
            return;
        }

        int mid = (start + end) >> 1;

        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r)
    {
        if (r < start || end < l)
            return 0; // the default value that needs to be returned

        if (l <= start && end <= r)
            return tree[node];

        int mid = (start + end) >> 1;

        int q1 = query(2 * node, start, mid, l, r);
        int q2 = query(2 * node + 1, mid + 1, end, l, r);

        return merge(q1, q2);
    }

    int rangequery(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }

    void update(int pos, int val)
    {
        update(1, 0, n - 1, pos, val);
    }

    // ============================================================
    // MERGE SORT TREE
    // ============================================================

    void buildMST(vector<int> &a, int node, int l, int r)
    {

        if (l == r){
            seg[node].push_back(a[l]);
            return;
        }

        int mid = (l + r) >> 1;

        buildMST(a, node * 2, l, mid);
        buildMST(a, node * 2 + 1, mid + 1, r);

        merge(seg[node * 2].begin(),seg[node * 2].end(),seg[node * 2 + 1].begin(),seg[node * 2 + 1].end(),back_inserter(seg[node]));
    }

    int queryMST(int node, int l, int r, int lx, int rx, int x)
    {

        // completely outside
        if (l > rx || r < lx)
            return 0;

        // completely inside
        if (lx <= l && r <= rx)
        {

            // number of elements < x
            return lower_bound(seg[node].begin(), seg[node].end(), x) - seg[node].begin();
        }

        int mid = (l + r) >> 1;

        return queryMST(node * 2, l, mid, lx, rx, x) + queryMST(node * 2 + 1, mid + 1, r, lx, rx, x);
    }

    int rangeQueryMST(int l, int r, int x)
    {
        return queryMST(1, 0, n - 1, l, r, x);
    }
};



//reference
void build(vector<int>& a, int node, int l, int r) {

    if (l == r) {
        seg[node].push_back(a[l]);
        return;
    }

    int mid = (l + r) / 2;

    build(a, node * 2, l, mid);
    build(a, node * 2 + 1, mid + 1, r);

    // Merge the actual segments conceptually.
    // But we only keep prefix maximums.

    int mx = -1;

    for (int x : seg[node * 2]) {
        mx = max(mx, x);

        if (seg[node].empty() || seg[node].back() != mx)
            seg[node].push_back(mx);
    }

    for (int x : seg[node * 2 + 1]) {
        mx = max(mx, x);

        if (seg[node].back() != mx)
            seg[node].push_back(mx);
    }
}