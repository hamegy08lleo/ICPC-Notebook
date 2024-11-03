struct TSS {
        int nvar, nvrt;
        vector<vector<int>> adj;
        vector<bool> res;
        TSS(int nvar): nvar(nvar), nvrt(nvar * 2), adj(nvrt + 1), res(nvar + 1) {}
        int conj(int u) {
                if (u > nvar) return u - nvar;
                return u + nvar;
        }
        int operator[](int i) { return res[i]; }
        void add(int u, bool nu, int v, bool nv) {
                if (nu) u = conj(u);
                if (nv) v = conj(v);
                adj[u].push_back(v);
        }
        bool solve() {
                vector<int> in(nvrt + 1), low(nvrt + 1), id(nvrt + 1);
                stack<int> st;
                int curdfs = 0, curidx = 2 * nvrt + 1;
                auto tarjan = [&](auto&& f, int u) -> void {
                        in[u] = low[u] = ++curdfs;
                        st.push(u);
                        for (int v : adj[u]) {
                                if (!in[v]) {
                                        f(f, v);
                                        low[u] = min(low[u], low[v]);
                                } else if (!id[v]) {
                                        low[u] = min(low[u], in[v]);
                                }
                        }
                        if (low[u] == in[u]) {
                                int v;
                                do {
                                        v = st.top();
                                        st.pop();
                                        id[v] = curidx;
                                } while (v != u);
                                --curidx;
                        }
                };
                for (int i = 1; i <= nvrt; i++)
                        if (!in[i]) tarjan(tarjan, i);
                for (int i = 1; i <= nvar; i++) {
                        if (id[i] == id[conj(i)]) return false;
                        res[i] = id[i] > id[conj(i)];
                }
                return true;
        }
};
