class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = 12345;

        // build graph
        vector<vector<pair<int, int>>> g(n);
        for (const auto &e: times) {
            g[e[0] - 1].push_back({e[1] - 1, e[2]});
        }

        vector<int> d(n, inf);
        vector<bool> visited(n, false);
        // first == dist[k][u], second = u
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        d[k-1] = 0;
        pq.push({0, k-1});
        while (!pq.empty()) {
            auto du_and_u = pq.top();
            pq.pop();
            int du = du_and_u.first;
            int u = du_and_u.second;

            if (visited[u]) { continue; }
            visited[u] = true;

            for (const auto p: g[u]) {
                int v = p.first;
                int w = p.second;
                if (visited[v] || d[v] <= du + w) { continue; }

                d[v] = du + w;
                pq.push({d[v], v});
            }
        }

        int ans = *max_element(d.begin(), d.end());
        return ans == inf?-1:ans;
    }
};