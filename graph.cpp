const int LOG = 20;

int kth_ancestor(int u, int k, const vector<vector<int>>& up) {
    for (int i = 0; i < LOG; i++) {
        if (k & (1 << i)) {
            u = up[u][i];
            if (u == -1) break;
        }
    }
    return u;
}
void dfs(int v, int p, vector<vector<int>> &adj, vector<vector<int>> &up,
         vector<int> &depth) {
  up[v][0] = p;
  for (int i = 1; i < LOG; i++) {
    if (up[v][i - 1] == -1) break;
    up[v][i] = up[up[v][i - 1]][i - 1];
  }

  for (int u : adj[v]) {
    if (u != p) {
      depth[u] = depth[v] + 1;
      dfs(u, v, adj, up, depth);
    }
  }
}

int lca(int u, int v, const vector<vector<int>> &up, const vector<int> &depth) {
  if (depth[u] < depth[v]) swap(u, v);
  for (int i = LOG - 1; i >= 0; i--)
    if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
  if (u == v) return u;
  for (int i = LOG - 1; i >= 0; i--)
    if (up[u][i] != up[v][i]) {
      u = up[u][i];
      v = up[v][i];
    }
  return up[u][0];
}
bool bipart(int node,vi&color,vector<vi> &adj,int &black,int &red){
    if(color[node]) red++;
    else black++;
    for(auto child:adj[node]){
        if(color[child]==-1){
            color[child]=1^color[node];
            if(!bipart(child,color,adj,black,red)){
                return false;
            }
        }
        if(color[node]==color[child]){
            return false;
        }
    }
    return true;
}
void dijkstra(vector<vector<pair<int,int>>> &adj,int src,vi &dist) {

    priority_queue<pair<int,int>, vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,src});

    while(!pq.empty()){
        auto top=pq.top();pq.pop();
        int w=top.F;
        int u=top.S;
        if(w > dist[u]) continue;
        for(auto &child:adj[u]){
            int v=child.F;
            int w=child.S; 
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
}
