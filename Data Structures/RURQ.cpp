struct Tag { 
	int add; 
	Tag(): add(0) {}
	Tag(int add): add(add) {}
}; 

struct Info { 
	int val; 
	bool empty = 1; 
	Info(): val(0) { 
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
		res.val = lef.val + rig.val; 
		return res; 
	}
}; 

struct Segtree { 
	vector<Info> st; 
	vector<Tag> lz; 
	int n;
#define lc id << 1 
#define rc id << 1 | 1 
#define mi ((l + r) >> 1) 
	Segtree() {}
	Segtree(int n): n(n), st(n << 2, Info(0)), lz(n << 2, Tag()) {
	}
	void push(int id, int l, int r) { 
		if (lz[id].add == 0) return; 
		int x = lz[id].add; 
		lz[id].add = 0; 
		update(l, mi, x, lc, l, mi); 
		update(mi+1, r, x, rc, mi+1, r); 
	}
	void update(int u, int v, int x, int id, int l, int r) { 
		if (u > r || l > v) { 
			return; 
		}
		if (u <= l && r <= v) { 
			st[id].val += x * (r - l + 1); 
			lz[id].add += x; 
			return; 
		}
		push(id, l, r); 
		update(u, v, x, lc, l, mi); 
		update(u, v, x, rc, mi+1, r); 
		st[id] = st[lc] + st[rc]; 
	}
	Info get(int u, int v, int id, int l, int r) { 
		if (u > r || l > v) { 
			return Info(); 
		}
		if (u <= l && r <= v) { 
			return st[id]; 
		}
		push(id, l, r); 
		return get(u, v, lc, l, mi) + get(u, v, rc, mi+1, r); 
	}
#undef lc
#undef rc 
#undef mi
}; 
