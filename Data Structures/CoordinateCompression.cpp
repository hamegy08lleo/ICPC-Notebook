template<typename T>
struct CC { 
	vector<T> val; 
	bool ckcc = 1; 
	void insert(T num) { val.push_back(num); ckcc = 0; }
	void cc() { sort(all(val)), val.erase(unique(all(val)), val.end()), ckcc = 1;}
	int idx(T num) { assert(ckcc); return lower_bound(all(val), num) - val.begin() + 1; }
};
