struct M {
    int MOD;
    int v;
    explicit operator int() const { return v; }
    M(int MOD) : v(0), MOD(MOD) {}
    M(int _v, int MOD) : MOD(MOD), v((int)(_v % MOD)) { v += (v < 0) * MOD; }
    M& operator+=(M o) {
        if ((v += o.v) >= MOD) v -= MOD;
        return *this;
    }
    M& operator-=(M o) {
        if ((v -= o.v) < 0) v += MOD;
        return *this;
    }
    M& operator*=(M o) {
        v = (int)((int)v * o.v % MOD);
        return *this;
    }
    friend M binpow(M a, int p) {
        assert(p >= 0);
        return p == 0 ? 1 : binpow(a * a, p / 2) * (p & 1 ? a : 1);
    }
    friend M inv(M a) {
        assert(a.v != 0);
        return binpow(a, a.MOD - 2);
    }
    friend M operator+(M a, M b) { return a += b; }
    friend M operator-(M a, M b) { return a -= b; }
    friend M operator*(M a, M b) { return a *= b; }
    friend M operator/(M a, M b) { return a *= inv(b); }
    friend ostream& operator<<(ostream& out, M a) { return (out << a.v); }
};

template<int... MODS> 
struct bigM : vector<M> {
    static const vector<int> mods;
    bigM(){
        for (auto i : mods) push_back(M(i));
    }
    bigM(int _v) {
        for (auto i : mods) push_back(M(_v, i));
    }
    bigM& operator+=(bigM o) {
        for (int i = 0; i < size(); i++) (*this)[i] += o[i];
        return *this; 
    }
    bigM& operator-=(bigM o) {
        for (int i = 0; i < size(); i++) (*this)[i] += o[i];
        return *this; 
    }
    bigM& operator*=(bigM o) {
        for (int i = 0; i < size(); i++) (*this)[i] *= o[i];
        return *this; 
    }
    bigM& operator/=(bigM o) {
        for (int i = 0; i < size(); i++) (*this)[i] /= o[i];
        return *this; 
    }
    friend bigM binpow(bigM a, int p) {
        assert(p >= 0);
        return p == 0 ? bigM(1) :  binpow(a * a, p / 2) * (p & 1 ? a : bigM(1)); 
    }
    friend bigM inv(bigM a) {
        return binpow(a, a.MOD - 2);
    }
    friend bool operator==(bigM a, bigM b) { 
        for (int i = 0; i < a.size(); i++) { 
            assert(a[i].MOD == b[i].MOD);
            if (a[i].v != b[i].v) return false; 
        }
        return true; 
    }
    friend bool operator!=(bigM a, bigM b) { 
        return !(a == b); 
    }
    friend bigM operator+(bigM a, bigM b) { return a += b; }
    friend bigM operator-(bigM a, bigM b) { return a -= b; }
    friend bigM operator*(bigM a, bigM b) { return a *= b; }
    friend bigM operator/(bigM a, bigM b) { return a *= inv(b); }
};

template<int... MODS>
const vector<int> bigM<MODS...>::mods = {MODS...};

using MM = bigM<1035972859, 1704760909, 1234567891>;
