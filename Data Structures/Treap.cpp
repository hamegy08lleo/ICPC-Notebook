struct Treap { 
	Treap *lef, *rig; 
	Treap *par; 
	int num; 
	int prio; 
	int sz; 
	Treap(int num):
	num(num), 
	prio(rnd()),
	sz(1),
	par(nullptr), 
	lef(nullptr),
	rig(nullptr) {}
};
 
int getsz(Treap *p) { 
	return (p ? p->sz : 0); 
}

int getnum(Treap *p) { 
	return (p ? p->num : 0); 
}
 
void pull(Treap *p) { 
	if (!p) return; 
	p->sz = getsz(p->lef) + 1 + getsz(p->rig); 
	p->par = nullptr; 
	if (p->lef) p->lef->par = p; 
	if (p->rig) p->rig->par = p; 
}
 
void merge(Treap *&p, Treap *lef, Treap *rig) { 
	if (!lef || !rig) { 
		p = (lef ? lef : rig); 
		return; 
	}
	if (lef->prio > rig->prio) { 
		merge(lef->rig, lef->rig, rig); 
		p = lef; 
	}
	else { 
		merge(rig->lef, lef, rig->lef); 
		p = rig; 
	}
	pull(p); 
}
 
void splitbynum(Treap *p, Treap *&lef, Treap *&rig, int k) { 
        if (p == nullptr) {
                lef = rig = nullptr; 
                return; 
        }
        if (getnum(p) <= k) { 
                splitbynum(p->rig, p->rig, rig, k); 
                lef = p; 
        }
        else { 
                splitbynum(p->lef, lef, p->lef, k); 
                rig = p; 
        }
        pull(p); 
}

void splitbysz(Treap *p, Treap *&lef, Treap *&rig, int k) { 
	if (p == nullptr) { 
		lef = rig = nullptr; 
		return; 
	}
	if (getsz(p->lef) < k) { 
		splitbysz(p->rig, p->rig, rig, k - getsz(p->lef) - 1); 
		lef = p; 
	}
	else { 
		splitbysz(p->lef, lef, p->lef, k); 
		rig = p; 
	}
	pull(p); 
}

int index(Treap *p, Treap *pre = nullptr) { 
	if (!p) return 0LL; 
	if (pre && p->lef == pre) { 
		return index(p->par, p); 
	}
	else { 
		return index(p->par, p) + getsz(p->lef) + 1; 
	}
}
