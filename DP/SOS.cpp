// sum over subsets
for (int i = 0; i < (1LL << n); i++) { 
        sos[i] = cnt[i]; 
}
for (int i = 0; i < n; i++) { 
        for (int mask = 0; mask < (1LL << n); mask++) { 
                if (mask & (1 << i)) { 
                        sos[mask] += sos[mask ^ (1LL << i)];
                }
        }
}
// list all over subsets
for (int i = 0; i < (1 << n); i++) {
	for (int j = (i - 1) & i; j >= 0; j = (j - 1) & i) { sos[i] += a[j]; }

}
