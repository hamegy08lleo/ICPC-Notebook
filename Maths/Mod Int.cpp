struct M {
    int MOD;
    int v;
    explicit operator int() const { return v; }
    M() {}
    M(int MOD) : v(0), MOD(MOD) {}
    M(int _v, int MOD) : MOD(MOD), v(_v % MOD) { v += (v < 0) * MOD; }
 
    M& operator+=(M o) {
        if ((v += o.v) >= MOD) v -= MOD;
        return *this;
    }
    M& operator-=(M o) {
        if ((v -= o.v) < 0) v += MOD;
        return *this;
    }
    M& operator*=(M o) {
        v = (int)((long long)v * o.v % MOD); // Use long long to prevent overflow
        return *this;
    }
 
    friend M binpow(M a, int p) {
        assert(p >= 0);
        return p == 0 ? M(1, a.MOD) : binpow(a * a, p / 2) * (p & 1 ? a : M(1, a.MOD));
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
struct bigM {
    static const int size = sizeof...(MODS);
    M v[size];
    static constexpr array<int, size> mods = {MODS...};
    bigM() {
        for (int i = 0; i < size; ++i) {
            v[i] = M(mods[i]);
        }
    }
    bigM(int _v) {
        for (int i = 0; i < size; ++i) {
            v[i] = M(_v, mods[i]);
        }
    }
 
    bigM& operator+=(bigM o) {
        for (int i = 0; i < size; i++) {
            v[i] += o.v[i];
        }
        return *this;
    }
    bigM& operator-=(bigM o) {
        for (int i = 0; i < size; i++) {
            v[i] -= o.v[i];
        }
        return *this;
    }
    bigM& operator*=(bigM o) {
        for (int i = 0; i < size; i++) {
            v[i] *= o.v[i];
        }
        return *this;
    }
    bigM& operator/=(bigM o) {
        for (int i = 0; i < size; i++) {
            v[i] /= o.v[i];
        }
        return *this;
    }
    friend bigM binpow(bigM a, int p) {
        assert(p >= 0);
        return p == 0 ? bigM(1) : binpow(a * a, p / 2) * (p & 1 ? a : bigM(1));
    }
    friend bigM inv(bigM a) {
        bigM res; 
        for (int i = 0; i < size; i++) {
            res.v[i] = inv(a.mods[i]);
        }
        return res;
    }
    friend bool operator==(bigM a, bigM b) {
        for (int i = 0; i < size; i++) {
            if (a.v[i].v != b.v[i].v) return false;
        }
        return true;
    }
    friend bool operator!=(bigM a, bigM b) {
        return !(a == b);
    }
    friend bigM operator+(bigM a, bigM b) { return a += b; }
    friend bigM operator-(bigM a, bigM b) { return a -= b; }
    friend bigM operator*(bigM a, bigM b) { return a *= b; }
    friend bigM operator/(bigM a, bigM b) { return a /= b; }
};
 
using MM = bigM<1035972859, 1704760909, 1234567891>;
