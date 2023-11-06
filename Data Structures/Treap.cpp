
struct Treap { 
	Treap *lef, *rig; 
	int num; 
	int prio; 
	int sz; 
	Treap(int num):
	num(num), 
	prio(rnd()),
	sz(1),
	lef(nullptr),
	rig(nullptr) {}
};
 
int sz(Treap *p) { 
	return (p ? p->sz : 0); 
}
 
void pull(Treap *p) { 
	if (!p) return; 
	p->sz = sz(p->lef) + 1 + sz(p->rig); 
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
 
void split(Treap *p, Treap *&lef, Treap *&rig, int k) { 
	if (!p) { 
		lef = rig = nullptr; 
		return; 
	}
	if (sz(p->lef) < k) { 
		split(p->rig, p->rig, rig, k - 1 - sz(p->lef)); 
		lef = p; 
	}
	else { 
		split(p->lef, lef, p->lef, k); 
		rig = p; 
	}
	pull(p); 
}
