struct fenwick { 
        vector<int> f; 
        int n; 
        fenwick(int n): n(n) { 
                f.resize(n + 1); 
        }
        void add(int i, int v) { 
                for (; i <= n; i += i & -i) f[i] += v; 
        }
        int get(int i) { 
                int ans = 0; 
                for (; i >= 1; i -= i & -i) ans += f[i]; 
                return ans; 
        }
        int range(int u, int v) { 
                return get(v) - get(u-1); 
        }
};

