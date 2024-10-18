/**
 * Description: Modular arithmetic. Assumes $MOD$ is prime.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 * Usage: mi a = MOD+5; inv(a); // 400000003
 */

template<int MOD> struct M {
	static const int mod = MOD;
	int v; 
	explicit operator int() const { return v; } 
	M():v(0) {}
	M(int _v):v((int)(_v%MOD)) { v += (v<0)*MOD; }
	M& operator+=(M o) { 
		if ((v += o.v) >= MOD) v -= MOD; 
		return *this; }
	M& operator-=(M o) { 
		if ((v -= o.v) < 0) v += MOD; 
		return *this; }
	M& operator*=(M o) { 
		v = (int)((int)v*o.v%MOD); return *this; }
	friend M binpow(M a, int p) { assert(p >= 0);
		return p==0?1:binpow(a*a,p/2)*(p&1?a:1); }
	friend M inv(M a) { assert(a.v != 0); return binpow(a,MOD-2); }
	friend M operator+(M a, M b) { return a += b; }
	friend M operator-(M a, M b) { return a -= b; }
	friend M operator*(M a, M b) { return a *= b; }
	friend M operator/(M a, M b) { return a *= inv(b); }
	friend ostream & operator << (ostream & out, M a) { return (out << a.v); }
};

int const md = 1e9 + 7; 
using mint = M<md>;
