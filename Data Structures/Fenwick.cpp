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
	int find(int k) {
		int sum = 0, pos = 0;
		for (int i = __lg(n); i >= 0; i--)
		{
			if (pos + (1 << i) < n && sum + bit[pos + (1 << i)] < k)
			{
				sum += bit[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return pos + 1;
	}
};

