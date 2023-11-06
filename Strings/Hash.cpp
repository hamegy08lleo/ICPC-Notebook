int base = 311;
int const MOD = 1000000007;
int hashS[MAX];
int POW[MAX];
int gethash(int i, int j, int hashS[MAX]){
    return (hashS[j] - hashS[i - 1] * POW[j - i + 1] + MODMOD) % MOD;
}
void setHash(){
    string s;
    n = s.length();
    POW[0] = 1;
    s = " " + s;
    t = " " + t;
    for (int i = 1; i <= n; i++)
        POW[i] = (base POW[i - 1])%MOD;
    for (int i = 1; i <= n; i++){
        hashS[i] = (hashS[i - 1] * base + s[i]) % MOD;
    }
    for (int i = 1; i <= m; i++)
        hashT[i] = (hashT[i - 1] * base + t[i]) % MOD;
}
