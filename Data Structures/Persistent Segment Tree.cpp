struct PSTNode { 
        int val; 
        PSTNode *lef, *rig; 
        PSTNode (int val) { 
                this->val = val; 
                lef = rig = nullptr; 
        }
        PSTNode (PSTNode *lef, PSTNode *rig) { 
                this->lef = lef; 
                this->rig = rig; 
                val = 0; 
                if (lef) val += lef->val; 
                if (rig) val += rig->val; 
        }
        PSTNode (PSTNode *p) { 
                this->lef = p->lef; 
                this->rig = p->rig; 
                this->val = p->val; 
        }
};

struct PST { 
        int n, nv; 
        vector<PSTNode*> rt; 
        PST() {}
        PST(int n, int nv, vector<int> vec) { 
                this->n = n; 
                this->nv = nv; 
                rt.resize(nv + 1); 
                rt[0] = build(1, n, vec); 
        }

        PSTNode *build(int l, int r, vector<int> &vec) { 
                if (l == r) { 
                        return new PSTNode(vec[l]); 
                }
                int mi = (l + r) >> 1; 
                return new PSTNode(build(l, mi, vec), build(mi+1, r, vec)); 
        }

        int get(int i, PSTNode *p, int l, int r) { 
                if (l == r) { 
                        return p->val; 
                }
                int mi = (l + r) >> 1; 
                if (i <= mi) return get(i, p->lef, l, mi); 
                else return get(i, p->rig, mi+1, r); 
        }
        int get(int i, int v) { 
                return get(i, rt[v], 1, n); 
        }
        PSTNode *update(int i, int val, PSTNode *p, int l, int r) { 
                if (l == r) { 
                        return new PSTNode(val); 
                }
                int mi = (l + r) >> 1; 
                if (i <= mi) return new PSTNode(update(i, val, p->lef, l, mi), p->rig); 
                else return new PSTNode(p->lef, update(i, val, p->rig, mi+1, r)); 
        }

        void update(int i, int val, int v) { 
                rt[v] = update(i, val, rt[v], 1, n);               
        }

        void copy(int t1, int t2) { 
                rt[t2] = rt[t1]; 
        }
};
