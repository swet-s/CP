namespace STUFF
{
	using namespace std;

	const double pi = 3.141592653589793;
	const int mod = 1e9 + 7;
	const int mod1 = 998244353;
	const int maxn = 1e6 + 1;

	int gcd(int a, int b)
	{
		if (b == 0) return a;
		else return gcd(b, a % b);
	}

	int power(int a, int n, int m)
	{
		int res = 1;
		while (n)
			if (n % 2) res = ((res % m) * (a % m)) % m, n--;
			else a = ((a % m) * (a % m)) % m, n /= 2;
		return res;
	}

	// modulo inverse
	inline int minv(int a, int m) { return power(a, m - 2, m); }

	// primality test
	bool isprime(int n) 
	{ 
	  if (n <= 1) return false; 
	  if (n <= 3) return true; 
	  if (n % 2 == 0 || n % 3 == 0) return false; 
	  for (int i = 5; i * i <= n; i += 6) if (n % i == 0 || n % (i+2) == 0) return false; 
	  return true; 
	} 

	// prime seive
	vector<int> is_prime(maxn, 1);
	void seive()
	{
		is_prime[0] = is_prime[1] = 0;
		for (int i = 2; i * i <= maxn; i++)
			if (is_prime[i])
				for (int j = i * i; j < maxn; j += i)
					is_prime[j] = 0;
	}



	// prime seive O(n)
	vector<int> is_prime(maxn, 1);
	vector<int> mpf(maxn, 1);
	vector<int> prime;
	void manipulated_seive()
	{
	    is_prime[0] = is_prime[1] = 0;
	 
	    for (int i=2; i<maxn; i++)
	    {
	        if (is_prime[i])
	        {
	            prime.push_back(i);
	            mpf[i] = i;
	        }
	        for (int j=0;j < sz(prime) && i*prime[j] < maxn && prime[j] <= mpf[i];j++)
	        {
	            is_prime[i*prime[j]]=0;
	            mpf[i*prime[j]] = prime[j];
	        }
	    }
	}

	// prime factorization
	vector<int> arr(maxn, -1);
	void seivepf()
	{
		for (int i = 2; i * i <= maxn; i++)
			if (arr[i] == -1)
				for (int j = i * i; j < maxn; j += i)
				{
					if (arr[j] == -1) arr[j] = i;
					arr[i] = i;
				}
	}
	void fetch(int no, map<int, int>& mp)
	{
		int k = no;
		while (k != 1)
		{
			if (arr[k] == -1)
			{
				mp[k]++;
				break;
			}
			mp[arr[k]]++;
			k /= arr[k];
		}
	}

	// # of co-prime pair with n, eular totient function.
	int phi[maxn];
	void calc() 
	{
	    for (int i = 1; i < maxn; i++) phi[i]=i;

	    for (int i = 2; i < maxn; ++i)
	    {
	        if (phi[i]==i)
	            for (int j = i; j < maxn; j+=i)
	                phi[j]/=i, phi[j]*=(i-1);
	    }
	}

	//Fermat's little theorem --> a^(p-1) ≡ 1 mod p (where p is a prime)

	// Multiply two very large numbers up to 1e18.
	int mulmod(int a, int b, int m)
	{
	    int x=0,y=a%m;
	    while(b>0)
	    {
	        if (b%2==1)
	            x = (x+y)%m;
	        y = (y*2ll)%m;
	        b/=2;
	    }
	    return x%m;
	}
	
	// primality test 2
	bool MillerRabin(int n) 
	{
	    if (n < 2) return 0;

	    int r = 0;
	    int d = n - 1;
	    while ((d & 1) == 0) d >>= 1,r++;
	    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) 
	    {
	        if (n == a) return 1;

	        int x = 1;
	        while (d) if (d % 2) x = mulmod(x,a,n), d--; else a = mulmod(a,a,n), d /= 2;

	        if (x == 1 || x == n - 1) continue;
	        for (int s = 1; s < r; s++) 
	        {
	            x = mulmod(x, x, n);
	            if (x == n - 1) goto end;
	        }
	        return 0;
	        end:;
	    }
	    return 1;
	}
}