template<typename T> 
struct Matrix
{
    // int mod = 998244353 ^ 1755654;
    vector<vector<T>> mat;
    int r,c;

    Matrix(int n, int m)
    {
        r = n, c = m;
        mat = vector<vi>(n);
        for (int i = 0; i < n; i++) mat[i] = vi(m);
    }

    static Matrix Identity(int n)
    {
        Matrix I = Matrix(n, n);
        for (int i = 0; i < n; i++) I[i][i]=1;
        return I;
    }

    vi& operator[](int k) { return mat[k]; }

    Matrix operator*(Matrix& O) 
    {
        Matrix R(r, O.c);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < O.c; j++) 
                for (int k = 0; k < O.r; k++) 
                    R[i][j] = (R[i][j] + ((*this)[i][k] * O[k][j]) % mod) % mod;
        return R;
    }
    void operator*=(Matrix& O) { (*this) = (*this) * O; }

    Matrix operator^(int n) 
    {
        Matrix R = Identity(r);
        Matrix A = *this;
        while (n)
            if (n % 2) R *= A, n--;
            else A *= A, n /= 2;
        return R;
    }
    void operator^=(int n) { (*this) = (*this) ^ n; }

    typedef  T(*func)(T a, T b);
    void oper(Matrix& O, func OP) 
    {
        Matrix R(r, c);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) 
                (*this)[i][j] = OP((*this)[i][j], O[i][j]);
    }
};



// rotate the matrix 45 degrees
int gg[5000][5000]
void Input(int n)
{
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> gg[i+j][n-i+j-1];
}
