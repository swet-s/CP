template<typename T>
struct lazySegTree
{
    int n;
    vector<T> st,arr;
    vector<T> lazy;
    T inf= -1e16;
 
    T oper(T a,T b){
        if(a==inf) return b;
        if(b==inf) return a;
        return max(a,b);
    };
    void evalazy(int si, int ss, int se){
        st[si] += (se-ss+1)*lazy[si];
        if (ss != se){  
            if (lazy[si<<1]!=inf) lazy[si<<1] += lazy[si];
            else lazy[si<<1] = lazy[si];
            if (lazy[(si<<1)+1]!=inf) lazy[(si<<1)+1] += lazy[si];
            else lazy[(si<<1)+1] = lazy[si];
        }
    };
    void build(int si, int ss, int se){
        if (ss == se) { st[si] = arr[ss-1]; return; }
        build(si<<1,ss,(ss+se)/2);
        build((si<<1)+1,((ss+se)/2)+1,se);
        st[si] = oper(st[si<<1],st[(si<<1)+1]);
    }
    void init(int size){
        n=size;
        st=vector<T>(4*n); 
        lazy=vector<T>(4*n,inf);
        build(1,1,n);
    }
    T query(int qs, int qe, int si, int ss, int se){
        if (lazy[si] != inf) {evalazy(si,ss,se);lazy[si]=inf;}
        if (qs > se || qe < ss) return inf;
        if (ss >= qs && se <= qe) return st[si];
        return oper(query(qs,qe,si<<1,ss,(ss+se)/2),query(qs,qe,(si<<1)+1,((ss+se)/2)+1,se));
    } 
    void update(int qs, int qe, T val, int si, int ss, int se){
        if (lazy[si] != inf) {evalazy(si,ss,se);lazy[si] = inf;}
        if (qs > se || qe < ss) return;
        if (ss >= qs && se <= qe) {lazy[si]=val;evalazy(si,ss,se);lazy[si]=inf;return;}
        update(qs,qe,val,si<<1,ss,(ss+se)/2);
        update(qs,qe,val,(si<<1)+1,((ss+se)/2)+1,se);
        st[si] = oper(st[si<<1],st[(si<<1)+1]);
    }
    lazySegTree(int size, T val=T()){ arr=vector<T>(size,val);init(size); }
    lazySegTree(vector<T>& arr2){ arr=arr2;init(sz(arr)); }
    T query(int qs, int qe) { return query(qs,qe,1,1,n);}
    void update(int qi, T val) { update(qi,qi,val,1,1,n);}
    void update(int qs, int qe, T val) { update(qs,qe,val,1,1,n);}
};

template<typename T>
struct segTree
{
    int n;
    vector<T> st,arr;
    T inf = -1e16;
 
    T oper(T a,T b){
        if(a==inf) return b;
        if(b==inf) return a;
        return max(a,b);
    };
    void build(int si, int ss, int se){
        if (ss == se) { st[si] = arr[ss-1]; return; }
        build(si<<1,ss,(ss+se)/2);
        build((si<<1)+1,((ss+se)/2)+1,se);
        st[si] = oper(st[si<<1],st[(si<<1)+1]);
    }
    void init(int size){
        n=size;
        st=vector<T>(4*n); 
        build(1,1,n);
    }
    T query(int qs, int qe, int si, int ss, int se){
        if (qs > se || qe < ss) return inf;
        if (ss >= qs && se <= qe) return st[si];
        return oper(query(qs,qe,si<<1,ss,(ss+se)/2),query(qs,qe,(si<<1)+1,((ss+se)/2)+1,se));
    } 
    void update(int qi, T val, int si, int ss, int se){
        if (ss == se) { st[si]=val; return; }
        if (qi <= (ss + se) / 2) update(qi,val,si<<1,ss,(ss+se)/2);
        else update(qi,val,(si<<1)+1,((ss+se)/2)+1,se);
        st[si] = oper(st[si<<1],st[(si<<1)+1]);
    }
    segTree(int size, T val=T()){ arr=vector<T>(size,val);init(size); }
    segTree(vector<T>& arr2){ arr=arr2;init(sz(arr)); }
    T query(int qs, int qe) { return query(qs,qe,1,1,n);}
    void update(int qi, T val) { update(qi,val,1,1,n);}
};


template<typename T, typename L>
struct lazySegTree2
{
    int n;
    vector<T> st,arr;
    vector<L> lazy;
    T inf= 1e16;
    L linf = 1e16;
 
    T oper(T a,T b){
        if(a==inf) return b;
        if(b==inf) return a;
        return a+b;
    };
    void evalazy(int si, int ss, int se){
        st[si] += (se-ss+1)*lazy[si];
        if (ss != se)
        {
            if (lazy[si<<1]!=inf) lazy[si<<1] += lazy[si];
            else lazy[si<<1] = lazy[si];
            if (lazy[(si<<1)+1]!=inf) lazy[(si<<1)+1] += lazy[si];
            else lazy[(si<<1)+1] = lazy[si];
        }
    };
    void build(int si, int ss, int se){
        if (ss == se) { st[si] = arr[ss-1]; return; }
        build(si<<1,ss,(ss+se)/2);
        build((si<<1)+1,((ss+se)/2)+1,se);
        st[si] = oper(st[si<<1],st[(si<<1)+1]);
    }
    void init(int size){
        n=size;
        st=vector<T>(4*n); 
        lazy=vector<L>(4*n,linf);
        build(1,1,n);
    }
    T query(int qs, int qe, int si, int ss, int se){
        if (lazy[si]!=linf) {evalazy(si,ss,se);lazy[si]=linf;}
        if (qs > se || qe < ss) return inf;
        if (ss >= qs && se <= qe) return st[si];
        return oper(query(qs,qe,si<<1,ss,(ss+se)/2),query(qs,qe,(si<<1)+1,((ss+se)/2)+1,se));
    } 
    void update(int qs, int qe, L val, int si, int ss, int se){
        if (lazy[si]!=linf) {evalazy(si,ss,se);lazy[si]=linf;}
        if (qs > se || qe < ss) return;
        if (ss >= qs && se <= qe) {lazy[si]=val;evalazy(si,ss,se);lazy[si]=linf;return;}
        update(qs,qe,val,si<<1,ss,(ss+se)/2);
        update(qs,qe,val,(si<<1)+1,((ss+se)/2)+1,se);
        st[si] = oper(st[si<<1],st[(si<<1)+1]);
    }
    lazySegTree2(int size, T val=T()){ arr=vector<T>(size,val);init(size); }
    lazySegTree2(vector<T>& arr2){ arr=arr2;init(sz(arr)); }
    T query(int qs, int qe) { return query(qs,qe,1,1,n);}
    void update(int qi, T val) { update(qi,qi,val,1,1,n);}
    void update(int qs, int qe, L val) { update(qs,qe,val,1,1,n);}
};