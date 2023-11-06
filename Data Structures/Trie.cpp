struct trie { 
	trie* ch[2]; 
	int sum, cnt, end; 
	trie() { 
		ch[0] = ch[1] = nullptr; 
		sum = cnt = end = 0; 
	}
};
 
int MXVAL = 0; // 2^(MX + 1) - 1

trie *rt = new trie(); 
void add(int num) { 
	auto p = rt; 
	for (int i = 30; i >= 0; i--) { 
		int b = (num >> i) & 1LL; 
		if (p->ch[b] == nullptr) p->ch[b] = new trie(); 
		p = p->ch[b]; 
		p->cnt++; 
		p->sum += num; 
	}
	p->end++; 
}
int find(int num) { 
	auto p = rt; 
	for (int i = 30; i >= 0; i--) { 
		int b = (num >> i) & 1LL; 
		if (p->ch[b] == nullptr) return false; 
		p = p->ch[b]; 
	}
	return p->end; 
}
bool del(trie *p, int num, int i, int d) { 
	if (i >= 0) { 
		int b = (num >> i) & 1LL; 
		if (del(p->ch[b], num, i-1, d)) p->ch[b] = nullptr; 
	}
	else { 
		p->end -= d; 
	}
	if (p != rt) { 
		p->cnt -= d; 
		p->sum -= num * d; 
		if (p->cnt == 0) { 
			delete(p); 
			return true; 
		}
	}
	return false; 
}
void del(int num, int t) { 
	int d = find(num); 
	if (d == 0) return; 
	if (t == 0) del(rt, num, 30, 1); 
	else del(rt, num, 30, d); 
}
int kth(int k) { 
	auto p = rt; 
	int res = 0; 
	for (int i = 30; i >= 0; i--) { 
		for (int b = 0; b < 2; b++) { 
			if (p->ch[b]) { 
				if (p->ch[b]->cnt >= k) { 
					p = p->ch[b]; 
					res += (b << i); 
					break; 
				}
				else { 
					k -= p->ch[b]->cnt; 
				}
			}
		}
	}
	return res; 
}
int sum(int u, int v, trie *p, int l, int r) { 
	if (u > r || l > v || p == nullptr) { 
		return 0; 
	}
	if (u <= l && r <= v) { 
		return p->cnt; 
	}
	int mi = (l + r)/2;
	return sum(u, v, p->ch[0], l, mi) + sum(u, v, p->ch[1], mi+1, r); 
}
int sum(int l, int r) { 
	return sum(l, r, rt, 0, MXVAL); 
}
int xr(int num) { 
	auto p = rt; 
	int res = 0; 
	for (int i = 30; i >= 0; i--) { 
		int b = (num >> i) & 1LL; 
		if (p->ch[1 ^ b] != nullptr) { 
			p = p->ch[1 ^ b];  
			res |= (1 << i); 
		}
		else { 
			p = p->ch[b]; 
		}
	}
	return res;
}
