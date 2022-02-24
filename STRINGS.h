#pragma once
#include "SS.h"


namespace STUFF
{
    // much needed
    string operator*(string s, int cnt) { string t = "";for (size_t i = 0; i < cnt; i++)t += s;return t; }
    string operator*=(string& s, int cnt) { return s = s * cnt; }

    vi z_function(string s)
    {
        int n = s.size();
        vi z(n);
        for (int i = 1, l = 0, r = 0; i < n; ++i)
        {
            if (i <= r)
                z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
        return z;
    }

    vi prefix_function(string s) 
    {
        int n = (int)s.length();
        vi pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i-1];
            while (j > 0 && s[i] != s[j])
                j = pi[j-1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return pi;
    }

    struct string_hash 
    {
        int n;
        int m, poly, inv;
        vi prefix, invs;

        int power(int a, int n, int m)
        {
            int res = 1;
            while (n)
                if (n % 2) res = ((res % m) * (a % m)) % m, n--; else a = ((a % m) * (a % m)) % m, n /= 2;
            return res;
        }
        int minv(int a, int m) { return power(a, m - 2, m); }

        void init(string s, int k = 94, int m = 1062599999) 
        {
            this->m = m; n = sz(s); poly = k; prefix = vi(n); invs = vi(n);

            invs[0] = 1; inv = minv(k, m);
            for (int i = 1; i < n; i++) invs[i] = (invs[i - 1] * inv) % m;

            int x = 1;
            prefix[0] = (s[0] - '0' + 1);
            for (int i = 1; i < n; i++) x = (x * k) % m, prefix[i] = (prefix[i - 1] + x * (s[i] - '0' + 1)) % m;
        }

        void extend(string next)
        {
            int x = sz(next);
            for (int i = 0; i < x; i++) invs.push_back((invs[i + n - 1] * inv) % m);

            int p = power(poly, n - 1, m);
            for (int i = 0; i < x; i++) p = (p * poly) % m, prefix.push_back((prefix[i + n - 1] + p * (next[i] - '0' + 1)) % m);
            n += x;
        }

        void kill(int sz) // remove last [sz] characters
        {  
            for (int i = 0; i < sz; i++) invs.pop_back(), prefix.pop_back();
            n -= sz;
        }

        int get_hash(int left, int right)
        {
            if (left == 0) return prefix[right];
            return ((prefix[right] - prefix[left - 1] + m) * invs[left]) % m;
        }
    };

    int kk[10] = { 89, 101, 189, 94, 621, rng() % 1000 + 1051, rng() % 2000 + 2761, rng() % 4000 + 4441, rng() % 8000 + 8111, rng() % 16000 + 18883 };
    int primes[10] = { 533000401, 735632791, 776531419, 797003413, 1062599999, 1047899999, 1031999999, 1027799999, 1018199999, 1000000007};

    template<int K>
    struct multihash 
    {
        string_hash sh[K];

        void init(string s) { for (int i = 0; i < K; i++) sh[i].init(s, kk[9 - i], primes[9 - i]); }
        void extend(string s) { for (int i = 0; i < K; i++) sh[i].extend(s); }
        void kill(int x) { for (int i = 0; i < K; i++) sh[i].kill(x); }

        vi get_hash(int l, int r) 
        {
            vi ret(K);
            for (int i = 0; i < K; i++) ret[i] = sh[i].get_hash(l, r);
            return ret;
        }

        bool compare(vi a, vi b) 
        {
            for (int i = 0; i < K; i++) if (a[i] != b[i]) return 0;
            return 1;
        }
    };


    const int SIZE = 26;
    struct Node
    {
        bool endOfWord;
        Node* ar[SIZE];

    };
     
    Node* getNode()
    {
        Node* n = new Node;
        n->endOfWord = false;
     
        for(int i=0;i<SIZE;i++) n->ar[i] = NULL;
     
        return n;
    }
     
    void insert(Node *root , string st)
    {
        Node *tempRoot = root;
     
        for(int i=0;i<st.size();i++)
        {
            int index = st[i] - 'a';
     
            if(tempRoot->ar[index] == NULL)
            tempRoot->ar[index] = getNode();
     
            tempRoot = tempRoot->ar[index];
        }
     
        tempRoot->endOfWord = true;
    }
     
    bool search(Node *root , string st)
    {
        Node *tempRoot = root;
     
        for(int i=0;i<st.size();i++)
        {
            int index = st[i] - 'a';
     
            if(tempRoot->ar[index] == NULL)
            return false;
     
            tempRoot = tempRoot->ar[index];
        }
     
        return tempRoot->endOfWord;
    }

    Node *root = getNode();
}


int change(int id, char ch) 
    {
        if (id==0)
        {
            return (prefix[n-1]-prefix[0]+(ch-'0'+1)+m)%m;
        }
        else
        {
            int gg = power(poly, id, m);
            gg*=(ch-'0'+1);
            gg%=m;
            return (prefix[n-1]-prefix[id]+m+prefix[id-1]+gg)%m;
        }
    }