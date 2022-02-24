#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>  
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
using namespace std;

template<typename T>void debugLog(T a);

template<typename T>struct segTree;
template<typename T>struct lazySegTree;
template<typename T, typename L>struct lazySegTree2;
template<typename T>struct Matrix;
template<typename T>struct Dsu;
template<unsigned int T>struct ABC;

void debugLog(bool a) { cerr << a; }
void debugLog(int a) { cerr << a; }
void debugLog(long long int a) { cerr << a; }
void debugLog(float a) { cerr << setprecision(6) << fixed << a; }
void debugLog(double a) { cerr << setprecision(10) << fixed << a; }
void debugLog(long double a) { cerr << setprecision(15) << fixed << a; }
void debugLog(char a) { cerr << a; }
void debugLog(const char* a) { cerr << (string)a;}
void debugLog(string a) { cerr << a; }

template<size_t T>void debugLog(ABC<T> a) { cerr << "(" << a << ")"; }

template<size_t T>void debugLog(bitset<T> a) { cerr << a; }

template<typename T1, typename T2>void debugLog(pair<T1, T2> a) 
{ 
	cerr << "("; debugLog(a.first); cerr << ","; debugLog(a.second); cerr << ")"; 
}

void debugLog(vector<bool> a) 
{
    cerr << "[ "; 
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i]==1) cerr<<1;
        else cerr<<0;
        cerr << ' ';
    } 
    cerr << "]";
}

template<typename T>
void debugLog(T a) 
{
	cerr << "[ "; for (auto& e : a) { debugLog(e); cerr << ' '; } cerr << "]";
}

template<typename T>
void debugLog(stack<T> st)
{
	cerr << "[ ";
	while (!st.empty()) { debugLog(st.top()); cerr << ' '; st.pop(); } 
	cerr << "]";
}

template<typename T>
void debugLog(queue<T> q)
{
	cerr << "[ ";
	while (!q.empty()) { debugLog(q.front()); cerr << ' '; q.pop(); } 
	cerr << "]";
}

template<typename T>
void debugLog(segTree<T> st)
{
	cerr << "[ ";
	for (int i = 1; i <= st.n; ++i) { debugLog(st.query(i, i)); cerr << ' '; } 
	cerr << "]";
}

template<typename T>
void debugLog(lazySegTree<T> st)
{
	cerr << "[ ";
	for (int i = 1; i <= st.n; ++i) { debugLog(st.query(i, i)); cerr << ' '; } 
	cerr << "]";
}

template<typename T, typename L>
void debugLog(lazySegTree2<T, L> st)
{
	cerr << "[ ";
	for (int i = 1; i <= st.n; ++i) { debugLog(st.query(i, i)); cerr << ' '; } 
	cerr << "]";
}

template<typename T>
void debugLog(Matrix<T> M)
{
	for (int i = 0; i < M.r; ++i) { cerr << "\n\t\t"; debugLog(M[i]); } 
}

template<typename T>
void debugLog(Dsu<T> d)
{
	cerr << "[ ";
	for (int i = 0; i < d.m_n ; ++i) { debugLog(d.getPar(i)); cerr << ' '; } 
	cerr << "]";
}


template<typename T, typename... Args>
void debugLog(string var, T t, Args... args)
{
	int firstcomma = var.find(',');
	
	if (firstcomma == -1)
	{
		while (var.back() == ' ') var.pop_back();
		debugLog("  " + var + " : ");
		debugLog(t);
		debugLog("\n");
	}
	else
	{
		string var2 = var.substr(0, firstcomma);
		while (var2.back() == ' ') var2.pop_back();

		var = var.substr(firstcomma + 1, var.size() - firstcomma);
		reverse(var.begin(), var.end());
		while (var.back() == ' ') var.pop_back();
		reverse(var.begin(), var.end());

		debugLog("  " + var2 + " : ");
		debugLog(t);
		debugLog("\n");
		debugLog(var, args...);
	}
}

template<typename... Args>
void debug(string func, string var,  Args... args)
{
	// debugLog(func + "():\n"); /*Experimental*/
	reverse(var.begin(), var.end());
	while (var.back() == ' ') var.pop_back();
	reverse(var.begin(), var.end());

	debugLog(var, args...);
	debugLog("\n");
}

namespace DebugArray
{
	void shrink(string& var)
	{
		var = var.substr(0, var.find(','));
		reverse(var.begin(), var.end());
		while (var.back() == ' ') var.pop_back();
		reverse(var.begin(), var.end());
		while (var.back() == ' ') var.pop_back();
	}
	template<typename T>void debugA(T a, int n)
	{ 
		cerr << "[ ";
		for (int i = 0; i < n; ++i) 
		{ 
			debugLog(a[i]); cerr<<" ";
		} 
		cerr << "]";
	}
	template<typename T>void debugA(T a, int n, int m, int szz)
	{
		for (int i = 0; i < n; ++i)
		{ 
			if (i) debugLog(string(szz, ' '));
			debugA(a[i], m);
			debugLog("\n");
		}
	}
	template<typename T>void debugA(T a, int n, int m, int o, int szz)
	{
		for (int j = 0; j < m; ++j)
		{
			if (j) debugLog(string(szz, ' '));
			for (int i = 0; i < n; ++i)
			{ 
				debugA(a[i][j], o);
				debugLog("  ");
			}
			debugLog("\n");
		}
	}
	template<typename T>
	void debug(string func, string var, T* t, int n, int m, int o)
	{
		shrink(var);
		string sze = "  " + var + " : ";
		debugLog(sze);
		debugA(t, n, m, o, sze.size());
		debugLog("\n");	
	}
	template<typename T>
	void debug(string func, string var, T* t, int n, int m)
	{
		shrink(var);
		string sze = "  " + var + " : ";
		debugLog(sze);
		debugA(t, n, m, sze.size());
		debugLog("\n");	
	}
	template<typename T>
	void debug(string func, string var, T* t, int n)
	{
		shrink(var);
		debugLog("  " + var + " : ");
		debugA(t, n);
		debugLog("\n\n");	
	}
}
using namespace DebugArray;

#define debug(...) debug(__func__,#__VA_ARGS__,__VA_ARGS__)





#define __FUN__(...) debug(__LINE__, __TIME__, __DATE__, __func__, __COUNTER__, __FILE__)