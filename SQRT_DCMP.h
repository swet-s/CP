#define BLK 500

struct MO
{   
    struct Query{
        int l, r, id;

        bool operator<(Query b){
            if (l / BLK != b.l / BLK) return l / BLK < b.l / BLK;
            else return r < b.r;
        }
    };
    vector<Query> qq;
    int n,m;
    vector<int> a;

    // edit here
    vector<int> ans;
    vector<int> freq;
    int cc;

    void init(int nn, int mm, vector<int>& aa){
        n = nn;
        m = mm;
        a = aa;
        qq = vector<Query>(m);
        for (int i = 0; i < m; ++i)
        {
            cin>>qq[i].l>>qq[i].r;
            qq[i].l--;
            qq[i].r--;
            qq[i].id = i;
        }
        sort(all(qq));
        //edit here
        ans = vector<int>(m);
        freq = vector<int>(n+1);
        cc = 0;
    }

    void Add(int i){
        if (a[i]<=n){
            freq[a[i]]++;
            if (freq[a[i]]==a[i]) cc++;
            if (freq[a[i]]==a[i]+1) cc--;
        }
    }

    void Remove(int i){
        if (a[i]<=n){
            if (freq[a[i]]==a[i]) cc--;
            if (freq[a[i]]==a[i]+1) cc++;
            freq[a[i]]--;
        }
    }

    void run(){
        int ml = 0, mr = -1;
        for (int i = 0; i < m; ++i){
            while (ml > qq[i].l) ml--,Add(ml);
            while (mr < qq[i].r) mr++,Add(mr);
            while (ml < qq[i].l) Remove(ml), ml++;
            while (mr > qq[i].r) Remove(mr), mr--;
            ans[qq[i].id] = cc;
        }
    }

    void print(){
        for (int i = 0; i < m; ++i){
            printl(ans[i]);
        }
    }
};