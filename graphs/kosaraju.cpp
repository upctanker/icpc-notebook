// Kosaraju - SCC O(V+E)
vi adj[N], adjt[N];
int ord[N], ordn, scc[N], sccn, vis[N];

void dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) if (!vis[v]) dfs(v);
  ord[ordn++] = u;
}

void dfst(int u) {
  vis[u] = 0;
  for (int v : adjt[u]) if (vis[v]) dfst(v);
  scc[u] = sccn;
}

// in main
sccn = ordn = 1;
for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
for (int i = n; i > 0; --i) if (vis[ord[i]]) dfst(ord[i]), sccn++;
