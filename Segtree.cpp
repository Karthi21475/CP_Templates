struct segment{
     int n;
     vector<int> tree;
     // segmentst(n);
     // st.build(arr, 1, 0, n - 1);
     segment(int n) {
         this->n = n;
         tree.resize(4 * n);
     }
     // merge ko change karna hei
     // query wala pe defualt value change karna hei
     int merge(int a, int b) {return (a+b);}

    void build(vector<int>& arr,int node,int start,int end) {
         if (start==end) {
             tree[node] = arr[start];
         } else {
             int mid=(start+end)>>1;
             build(arr,2 * node,start,mid);
             build(arr,2 * node + 1,mid + 1,end);
             tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
         }
     }

     void update(int node, int start, int end, int idx, int val) {
         if (start==end) {
             tree[node]=val;
         } else {
             int mid=(start + end)>>1;
             if(idx<=mid)
                 update(2 * node,start, mid,idx,val);
             else
                 update(2 * node + 1, mid + 1, end,idx,val);
             tree[node]=merge(tree[2 * node], tree[2 * node + 1]);
         }
     }

     int query(int node, int start, int end, int l, int r) {
         if (r < start || end < l) return 0;   // defualt value ko return kar
         if (l <= start && end <= r) return tree[node];
         int mid = (start + end) / 2;
         int q1 = query(2 * node, start, mid, l, r);
         int q2 = query(2 * node + 1, mid + 1, end, l, r);
         return merge(q1, q2);
     }
    int rangequery(int l , int r) {
         return query(1,0,n-1,l,r);
     }
    void update(int pos, int val) {
         update(1,0,n-1,pos,val);
     }

 };