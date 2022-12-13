#ifdef _BELUGA 
#include "DEBUG.h"
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>  
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
using namespace std;
#define debug(...) 
#endif

#define int long long
#define endl '\n'
#define sz(a) (int)((a).size())
#define all(a) (a).begin(),(a).end()
#define allr(a) (a).rbegin(),(a).rend() 
#define mem0(a) memset(a, 0, sizeof(a))
#define mem1(a) memset(a, -1, sizeof(a))
#define uniq(a) (a).erase(unique(all(a)),(a).end())
#define sum(a) accumulate(all(a), 0ll)
#define rotl(x, a) rotate(x.begin(), x.begin()+(a%sz(x)), x.end())
#define rotr(x, a) rotate(x.begin(), x.begin()+sz(x)-(a%sz(x)), x.end())
#define ppc(x) __builtin_popcountll(x) 
#define type(x) remove_reference<decltype(x)>::type

typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef map<int, int> mii;
typedef pair<int, int> pii;

const double pi = 3.141592653589793;

void google() { static int _gtest_ = 1; cout << "Case #" << _gtest_++ << ": "; }

mt19937 rngi(chrono::steady_clock::now().time_since_epoch().count());
int rng() { return uniform_int_distribution<int>(1, numeric_limits<int>::max())(rngi); }

template<typename T1, typename T2>istream& operator>>(istream& in, pair<T1, T2>& a) { return in >> a.first >> a.second; }
template<typename T1, typename T2>ostream& operator<<(ostream& ot, pair<T1, T2> a) { return ot << a.first << " " << a.second; }
template<typename T>istream& operator>>(istream& in, vector<T>& a) { for (auto& e : a) in >> e ; return in; }
template<typename T>ostream& operator<<(ostream& out, vector<T>& a) { for (auto& e : a) out << e << " "; return out; }
template<typename T>void print(T t) { cout << t; }
template<typename T, typename... Args>void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename... Args>void printl(Args... args) { print(args...); cout << endl; }

signed main()
{
    int test = 1;
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << setprecision(10) << fixed;


    cin >> test;    
    // void calc(); calc();
    void code(); while (test--) code();
}

const int mod = 998244353 ^ 1755654; // Confirm It.
const int maxn = 2e5 + 10; // This as well.

void code()
{
    
}