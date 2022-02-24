class u_int128
{
private:
	bitset<128> m_value;
	bitset<128> to_bitset() { return this->m_value; }

public:

	u_int128() { m_value = bitset<128>(); }
	u_int128(bitset<128> value) { m_value = value; }
	u_int128(unsigned long long value) { m_value = bitset<128>(value); }

	u_int128 operator~() { return ~(this->to_bitset()); }
	u_int128 operator|(u_int128 other) { return this->to_bitset() | other.to_bitset(); }
	u_int128 operator&(u_int128 other) { return this->to_bitset() & other.to_bitset(); }
	u_int128 operator^(u_int128 other) { return this->to_bitset() ^ other.to_bitset(); }

	bool operator<(u_int128 other)
	{
		for (int i = 128 - 1; i >= 0; i--)
		{
			if (this->to_bitset()[i] < other.to_bitset()[i]) return true;
			else if (this->to_bitset()[i] > other.to_bitset()[i]) return false;
		}
		return false;
	}
	
	bool operator>(u_int128 other)
	{
		for (int i = 128 - 1; i >= 0; i--)
		{
			if (this->to_bitset()[i] > other.to_bitset()[i]) return true;
			else if (this->to_bitset()[i] < other.to_bitset()[i]) return false;
		}
		return false;
	}

	bool operator==(u_int128 other) { return this->to_bitset() == other.to_bitset(); }
	bool operator!=(u_int128 other) { return this->to_bitset() != other.to_bitset(); }
	bool operator<=(u_int128 other) { return *this == other || *this < other; }
	bool operator>=(u_int128 other) { return *this == other || *this > other; }

	u_int128 operator<<(size_t val)
	{
		bitset<128> ans;
		for (size_t i = val; i < 128; i++)
			ans[i] = this->to_bitset()[i - val];
		return ans;
	}
	u_int128 operator<<=(size_t val) { return *this = *this << val; }

	u_int128 operator>>(size_t val)
	{
		bitset<128> ans;
		for (size_t i = 0; i + val < 128; i++)
			ans[i] = this->to_bitset()[i + val];
		return ans;
	}
	u_int128 operator>>=(size_t val) { return *this = *this >> val; }

	u_int128 operator+(u_int128 other)
	{
		bool c = 0;
		bitset<128> sum;
		for (size_t i = 0; i < 128; i++)
		{
			sum[i] = m_value[i] ^ other.to_bitset()[i] ^ c;
			c = (m_value[i] & other.to_bitset()[i] | m_value[i] & c | other.to_bitset()[i] & c);
		}
		return sum;
	}
	u_int128 operator+=(u_int128 other) { return *this = *this + other; }

	u_int128 operator-(u_int128 other)
	{
		bool c = 0;
		bitset<128> diff;
		for (size_t i = 0; i < 128; i++)
		{
			bool tp = m_value[i];
			m_value[i] = m_value[i] ^ c;
			c = !tp && c;

			diff[i] = m_value[i] ^ other.to_bitset()[i];
			c |= !m_value[i] && other.to_bitset()[i];
		}
		return diff;
	}
	u_int128 operator-=(u_int128 other) { return *this = *this - other; }

	u_int128 operator*(u_int128 other)
	{
		u_int128 mul, tmp = *this;
		for (size_t i = 0; i < 128; i++)
		{
			mul += other.to_bitset()[i] ? tmp : u_int128(0);
			tmp += tmp;
		}
		return mul;
	}
	u_int128 operator*=(u_int128 other) { return *this = *this * other; }

	u_int128 operator/(u_int128 other)
	{
		u_int128 ans, cpy = *this;

		int cnt=0;
		while (!other.to_bitset()[127])	other <<= 1, cnt++;

		for (size_t i = 0; i <= cnt; i++)
		{	
			ans += ans;
			if (cpy >= other)
			{
				ans += 1;
				cpy -= other;
			}
			other >>= 1;
		}
		return ans;
	}
	u_int128 operator/=(u_int128 other) { return *this = *this / other; }

	u_int128 operator%(u_int128 other)
	{
		u_int128 ans, cpy = *this;

		int cnt = 0;
		while (!other.to_bitset()[127])	other <<= 1, cnt++;

		for (size_t i = 0; i <= cnt; i++)
		{
			ans += ans;
			if (cpy >= other)
			{
				ans += 1;
				cpy -= other;
			}
			other >>= 1;
		}
		return cpy;
	}
	u_int128 operator%=(u_int128 other) { return *this = *this % other; }

	u_int128(string str)
	{
		reverse(str.begin(), str.end());
		u_int128 value;
		while (str.size())
		{
			int bck = str.back() - '0';
			if (bck > 9 || bck < 0) break;
			value *= 10;
			value += bck;
			str.pop_back();
		}
		m_value = value.m_value;
	}

	friend istream& operator>>(istream& in, u_int128& self);
	friend ostream& operator<<(ostream& out, u_int128& self);
};

istream& operator>>(istream& in, u_int128& self)
{
	string num;
	in >> num;
	self = num;
	return in;
}

ostream& operator<<(ostream& out, u_int128& self)
{
	string num = "";
	u_int128 cpy = self;

	if (cpy == 0)
		return out << 0;

	while (cpy != 0)
	{
		num += (cpy % 10).to_bitset().to_ulong() + '0';
		cpy /= 10;
	}
	reverse(num.begin(), num.end());
	return out << num;
}

typedef u_int128 ulll;