int next_x[N];
    int j = next_x[0] = 0;
    n = s.length();
    m = t.length();
    for (int i = 1; i < n; i++){
        while (j > 0 && s[j] != s[i]){
            j = next_x[j - 1];
        }
        if (s[i] == s[j])
            j++;
        next_x[i] = j;
    }
    j = 0;
    for (int i = 0; i < m; i++){
        while (j > 0 && s[j] != t[i])
            j = next_x[j - 1];
        if (s[j] == t[i])
            j++;
        if (j == n){
            cout << i - n + 2 << " ";
        }
    }
