const int mod1 = 1035972859;
const int mod2 = 1704760909;
const int base = ;
struct hashing{
        int mod, n;
        vector<int> h, k, power;
        int binpow(int a, int n){
                if (n == 0)
                        return 1LL;
                int res = binpow(a, n/2);
                if (n % 2)
                        return res * res % mod * a % mod;
                return res * res % mod;
        }
        hashing() {}
        hashing(string s, int mod): mod(mod){
                this->n = s.length();
                power = k = h = vector<int> (n);
                power[0] = 1;
                h[0] = s[0];
                for (int i = 1; i < n; i++){
                        power[i] = power[i - 1] * base % mod;
                        h[i] = (h[i - 1] * base + s[i]) % mod;
                }
                reverse(all(s));
                k[0] = s[0];
                for (int i = 1; i < n; i++){
                        k[i] = (k[i - 1] * base + s[i]) % mod;
                }
        }

        int getH(int l, int r){
                return (!l ? h[r] : (h[r] - h[l - 1] * power[r - l + 1] + mod * mod) % mod);
        }
        int getK(int l, int r){
                int L = l;
                l = n - 1 - r;
                r = n - 1 - L;
                return (!l ? k[r] : (k[r] - k[l - 1] * power[r - l + 1] + mod * mod) % mod);
        }
};

struct bighash{
        bighash() {}
        hashing a, b;
        bighash(string s){
                a = hashing(s, mod1);
                b = hashing(s, mod2);
        }

        int getH(int l, int r){
                return a.getH(l, r) * b.getH(l, r);
        }
        int getK(int l, int r){
                return a.getK(l, r) * b.getK(l, r);
        }
};
