struct FakeFenwick { 
        vector<vector<int>> fw, val; 
        int n;
        FakeFenwick() {}
        FakeFenwick(int n): n(n), val(n + 1, vector<int>()), fw(n + 1) {} 
        bool iscc = 0; 
        void fakeU(int x, int y) { 
                iscc = 0; 
                for (; x <= n; x += x & -x) val[x].push_back(y); 
        }
        void cc() { 
                if (iscc) return; 
                for (int x = 1; x <= n; x++) { 
                        sort(all(val[x])); 
                        val[x].erase(unique(all(val[x])), val[x].end()); 
                        fw[x].resize(val[x].size() + 1); 
                }
                iscc = 1; 
        }
        void update(int x, int y, int v) { 
                assert(iscc); 
                for (; x <= n; x += x & -x) { 
                        int yy = upper_bound(all(val[x]), y) - val[x].begin(); 
                        for (; yy <= val[x].size(); yy += yy & -yy) { 
                                fw[x][yy] += v; 
                        }
                         
                }
        }
        int get(int x, int y) { 
                assert(iscc); 
                int res = 0; 
                for (; x; x -= x & -x) { 
                        int yy = upper_bound(all(val[x]), y) - val[x].begin(); 
                        for (; yy; yy -= yy & -yy) { 
                                res += fw[x][yy]; 
                        }
                }
                return res; 
        }
};
