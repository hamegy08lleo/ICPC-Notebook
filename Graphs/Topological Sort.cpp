void kahn(int u) { 
	din[u] = -1; 
	topo.push_back(u); 
	for (int v : aa[u]) { 
		din[v]--; 
		if (din[v] == 0) kahn(v); 
	}
}

