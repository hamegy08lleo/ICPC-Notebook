struct Node { 
        int val; 
        Node *lef, *rig; 
        Node (int val) { 
                this->val = val; 
                lef = rig = nullptr; 
        }
        Node (Node *lef, Node *rig) { 
                this->lef = lef; 
                this->rig = rig; 
                val = 0; 
                if (lef) val += lef->val; 
                if (rig) val += rig->val; 
        }
        Node (Node *p) { 
                this->lef = p->lef; 
                this->rig = p->rig; 
                this->val = p->val; 
        }
};

struct PSegtree { 
        int n, nv; 
        vector<Node*> rt; 
        PSegtree() {}
        PSegtree(int n, int nv, vector<int> vec) { 
                this->n = n; 
                this->nv = nv; 
                rt.resize(nv + 1); 
                rt[0] = build(1, n, vec); 
        }

        Node *build(int l, int r, vector<int> &vec) { 
                if (l == r) { 
                        return new Node(vec[l]); 
                }
                int mi = (l + r) >> 1; 
                return new Node(build(l, mi, vec), build(mi+1, r, vec)); 
        }

        int get(int i, Node *p, int l, int r) { 
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
        Node *update(int i, int val, Node *p, int l, int r) { 
                if (l == r) { 
                        return new Node(val); 
                }
                int mi = (l + r) >> 1; 
                if (i <= mi) return new Node(update(i, val, p->lef, l, mi), p->rig); 
                else return new Node(p->lef, update(i, val, p->rig, mi+1, r)); 
        }

        void update(int i, int val, int v) { 
                rt[v] = update(i, val, rt[v], 1, n);               
        }

        void copy(int t1, int t2) { 
                rt[t2] = rt[t1]; 
        }
};
