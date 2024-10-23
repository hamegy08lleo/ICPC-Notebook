struct Info { 
	int val; 
	bool empty = 1; 
	Info() { 
		empty = 1; 
	}
	Info(int val): val(val) { 
		empty = 0; 
	}
	friend Info operator + (Info lef, Info rig) { 
		if (lef.empty || rig.empty) { 
			return lef.empty ? rig : lef; 
		}
		Info res; 
		res.empty = 0;
		res.val = max(lef.val, rig.val); 
		return res; 
	}
}; 

struct Segtree { 
	vector<Info> st; 
	int n;
#define lc id << 1 
#define rc id << 1 | 1 
#define mi ((l + r) >> 1) 
	Segtree() {}
	Segtree(int n): n(n), st(n << 2) {
	}
	void update(int i, int x, int id, int l, int r) { 
		if (l == r) { 
			st[id] = Info(x); 
			return; 
		}
		if (i <= mi) update(i, x, lc, l, mi); 
		else update(i, x, rc, mi+1, r); 
		st[id] = st[lc] + st[rc]; 
	}
	Info get(int u, int v, int id, int l, int r) { 
		if (u > r || l > v) { 
			return Info(); 
		}
		if (u <= l && r <= v) { 
			return st[id]; 
		}
		return get(u, v, lc, l, mi) + get(u, v, rc, mi+1, r); 
	}
}; 
