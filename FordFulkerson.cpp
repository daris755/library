struct Edge {
    // rev: toからみたfromのインデックス
    int to, cap, rev;
};

struct FordFulkerson {
    vector<vector<Edge>> G;
    vector<bool> seen;
    int size;

    void init(int n) {
        G.resize(n);
        seen.resize(n);
        size = n;
    }

    FordFulkerson(int n) { init(n); }

    void add_edge(int u, int v, int weight) {
        int u_see_v = G[u].size();
        int v_see_u = G[v].size();
        G[u].emplace_back(Edge{v, weight, v_see_u});
        G[v].emplace_back(Edge{u, 0, u_see_v});
    }

    int dfs(int cur_pos, int goal, int cur_flow) {
        if (cur_pos == goal) return cur_flow;
        seen[cur_pos] = true;

        for (auto& edge : G[cur_pos]) {
            if (edge.cap == 0 || seen[edge.to]) continue;

            int can_flow = dfs(edge.to, goal, min(cur_flow, edge.cap));
            if (can_flow > 0) {
                edge.cap -= can_flow;
                G[edge.to][edge.rev].cap += can_flow;
                return can_flow;
            }
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int total_flow = 0;
        int INF = 1 << 30;
        while (true) {
            seen = vector<bool>(size);
            int can_flow = dfs(s, t, INF);
            if (can_flow == 0) break;
            total_flow += can_flow;
        }
        return total_flow;
    }
};