struct RMQ { 
        int n, lg;
        vector<int> v; 
        vector<vector<int>> st; 
        RMQ(vector<int> & v): v(v), n(v.size() - 1) { 
                lg = __lg(n) + 1; 
                st.resize(n + 1, vector<int> (lg + 1)); 
                for (int i = 1; i <= n; i++) { 
                        st[i][0] = v[i]; 
                }
                for (int i = 1; i <= lg; i++) { 
                        for (int j = 1; j + (1LL << i) - 1 <= n; j++) { 
                                st[j][i] = min(st[j][i - 1], st[j + (1LL << (i - 1))][i - 1]); 
                        }
                }
        }
        int get(int l, int r) { 
                int len = __lg(r - l + 1); 
                return min(st[l][len], st[r - (1 << len) + 1][len]); 
        }
}; 
