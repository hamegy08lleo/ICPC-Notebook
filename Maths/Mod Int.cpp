/**
 * Description: Modular arithmetic. Assumes $MOD$ is prime.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 * Usage: mi a = MOD+5; inv(a); // 400000003
 */

template<int MOD> struct mint {
	static const int mod = MOD;
	int v; 
	explicit operator int() const { return v; } 
	mint():v(0) {}
	mint(int _v):v((int)(_v%MOD)) { v += (v<0)*MOD; }
	mint& operator+=(mint o) { 
		if ((v += o.v) >= MOD) v -= MOD; 
		return *this; }
	mint& operator-=(mint o) { 
		if ((v -= o.v) < 0) v += MOD; 
		return *this; }
	mint& operator*=(mint o) { 
		v = (int)((int)v*o.v%MOD); return *this; }
	friend mint binpow(mint a, int p) { assert(p >= 0);
		return p==0?1:binpow(a*a,p/2)*(p&1?a:1); }
	friend mint inv(mint a) { assert(a.v != 0); return binpow(a,MOD-2); }
	friend mint operator+(mint a, mint b) { return a += b; }
	friend mint operator-(mint a, mint b) { return a -= b; }
	friend mint operator*(mint a, mint b) { return a *= b; }
	friend mint operator/(mint a, mint b) { return a *= inv(b); }
	friend ostream & operator << (ostream & out, mint a) { return (out << a.v); }
};

int const md = 1e9 + 7; 
using mi = mint<md>;


