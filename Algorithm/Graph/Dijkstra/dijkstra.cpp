#include <vector>
#include <algorithm>

using namespace std;

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

        d[k-1] = 0;
        for (int i = 0; i < n-1; i++) {
            int u = -1;
            int du = inf;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && d[j] < du) {
                    u = j;
                    du = d[j];
                }
            }

            if (u == -1) { break; }
            visited[u] = true;

            for (const auto &p: g[u]) {
                int v = p.first;
                int w = p.second;
                d[v] = min(d[v], du + w);
            }
        }

        int ans = *max_element(d.begin(), d.end());
        return ans == inf?-1:ans;
    }
};