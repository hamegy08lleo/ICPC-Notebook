z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++){
        if (i > r){
            l = r = i;
            while (r < n && s[r] == s[r-l]) ++r;
            z[i] = r - l; 
            r-=1;
        }
        else{
            int k= i - l;
            if (z[k] < r - i + 1) z[i] = [k];
            else{
                l = i;
                while (r < n && s[r] == s[r - l]) r++;
                z[i]= r - l;
                r--;
            }
        }
    }
