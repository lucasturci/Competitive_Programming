#include <bits/stdc++.h>

using namespace std;

template<typename T, int bits = 30>
struct bitwise {
	T val;

	bitwise(T x = 0): val(x) {}

	// normal operators
	bitwise operator <<(bitwise x) { return val <<x.val; }
	bitwise operator >>(bitwise x) { return val >>x.val; }
	bitwise operator ~() { return ~val; }
	bitwise operator ^ (bitwise x) { return val ^ x.val; }
	bitwise operator & (bitwise x) { return val & x.val; }
	bitwise operator | (bitwise x) { return val | x.val; }
	bitwise operator * (bitwise x) { return val * x.val; }
	bitwise operator - (bitwise x) { return val - x.val; }
	bitwise operator + (bitwise x) { return val + x.val; }
	bitwise operator / (bitwise x) { return val / x.val; }

	int operator[](int p) {
		return (val >> p)&1;
	}

	// keep
	bitwise toggle(int p) {
		val ^= (T(1) << p);
		return (*this);
	}
	bitwise set(int p) {
		val |= (T(1) << p);	
		return (*this);
	}
	bitwise unset(int p) {
		if((*this)[p]) toggle(p);
		return (*this);
	}

	int count() {
		return __builtin_popcountll(val);
	}

	static bitwise ones(int x) {
		return (bitwise(1) << x) - 1;
	}
	bitwise substr(int l, int r) {
		return (val >> l) & ones(r - l + 1);
	}

	bool superset(bitwise x) {
		return ((*this) & x) == x;
	}
	bool subset(bitwise x) {
		return ((*this) | x) == x;
	}

	T operator()() {
		return val;
	}

	friend ostream & operator <<(ostream & out, bitwise val) {
		out << bitset<bits>(val.val);
	}
};


int main() {

	bitwise<long long, 20 > b = 1;
	long long c = 2;

	b = (b|c).toggle(1).set(2);
	cout << b << endl;

}