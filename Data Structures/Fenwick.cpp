template<typename T> 
struct fenwick { 
	vector<T> f; 
	int n; 
	fenwick(int n): n(n) { 
		f.resize(n + 1); 
	}
	void add(int i, T v) { 
		dbg(i); 
		for (; i <= n; i += i & -i) {
			f[i] += v; 
			dbg(i, v); 
		}
	}
	T get(int i) { 
		T ans = 0; 
		for (; i >= 1; i -= i & -i) ans += f[i]; 
		return ans; 
	}
	T find(T k) {
		T sum = 0;
		int pos = 0;
		for (int i = __lg(n); i >= 0; i--)
		{
			if (pos + (1 << i) < n && sum + f[pos + (1 << i)] < k)
			{
				sum += f[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return pos + 1;
	}
};
