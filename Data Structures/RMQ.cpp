// 0-indexed
template<typename T>
struct RMQ { 
        int n, lg;
        vector<T> v; 
        vector<vector<T>> st; 
        function<T(T, T)> f; 
        RMQ(vector<T> & v, function<T(T, T)> f = [](T i, T j) { return min(i, j); }): v(v), n(v.size()), f(f) { 
                lg = __lg(n) + 1; 
                st.resize(n, vector<int> (lg + 1)); 
                for (int i = 0; i < n; i++) { 
                        st[i][0] = v[i]; 
                }
                for (int i = 1; i <= lg; i++) { 
                        for (int j = 0; j + (1LL << i) - 1 < n; j++) { 
                                st[j][i] = f(st[j][i - 1], st[j + (1LL << (i - 1))][i - 1]); 
                        }
                }
        }
        int get(int l, int r) { 
                int len = __lg(r - l + 1); 
                return f(st[l][len], st[r - (1 << len) + 1][len]); 
        }
}; 
