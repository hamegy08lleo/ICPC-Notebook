struct wavelet { 
	wavelet *lc, *rc; 
	vector<int> pf; 
	int lo, hi;
 
	wavelet(vector<int> a): wavelet(1 + all(a), *min_element(1 + all(a)), *max_element(1 + all(a))){}
	wavelet(vector<int>::iterator l, vector<int>::iterator r, int lo, int hi): lo(lo), hi(hi) {
		if (lo == hi || l >= r) return;
		int mi = lo + (hi - lo)/2; 
		pf.reserve(r - l + 1); 
		pf.push_back(0LL);
		for (auto it = l; it != r; it++) { 
			pf.push_back(pf.back() + (*it <= mi));
		}
		auto m = stable_partition(l, r, [&](int num) { return num <= mi; });
		lc = new wavelet(l, m, lo, mi); 
		rc = new wavelet(m, r, mi+1, hi); 
	}
	// tim so nho thu k trong doan (l, r); 
	int kth(int l, int r, int k) { 
		if (l > r) return 0;
		if (lo == hi) { 
			return lo; 
		}
		int lef = pf[r] - pf[l-1]; 
		if (lef >= k) return lc->kth(pf[l-1] + 1, pf[r], k); 
		else return rc->kth(l - pf[l-1], r - pf[r], k - lef); 
	}
	// dem so > k trong doan (l r)
	int count(int l, int r, int num) { 
		if (l > r || hi <= num) return 0LL; 
		if (lo > num) { 
			return (r - l + 1); 
		}
		return lc->count(pf[l-1] + 1, pf[r], num) + rc->count(l - pf[l-1], r - pf[r], num);
	}
}; 
