// Matthew Kerr
//
// Addition uses the method at https://www.mathsisfun.com/numbers/addition-column.html
// Subtraction uses the method at https://www.mathsisfun.com/numbers/subtraction-quick.html
// Multiplication uses the method at https://www.mathsisfun.com/numbers/multiplication-long.html

#include <iostream>
#include <string>
using namespace std;

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

class BigInteger
{
	friend istream& operator>>(istream& in, BigInteger& num);
	friend ostream& operator<<(ostream& out, const BigInteger& num);
	
	public:
		int size;
		int * nums;
		int sign;
		BigInteger();
		BigInteger(const int& input);
		BigInteger(const string input);
		BigInteger(const BigInteger& other);
		BigInteger& operator=(const BigInteger& orig);
		BigInteger& operator=(const int& orig);
		virtual ~BigInteger();
		BigInteger operator+(const BigInteger& rhs) const;
		BigInteger operator-(const BigInteger& rhs) const;
		BigInteger operator*(const BigInteger& rhs) const;
		bool operator<(const BigInteger& rhs) const;
		bool operator<=(const BigInteger& rhs) const;
		bool operator==(const BigInteger& rhs) const;
		bool operator!=(const BigInteger& rhs) const { return !(*this == rhs); }	
		bool operator>(const BigInteger& rhs) const;
		bool operator>=(const BigInteger& rhs) const;
		void stripZeros();
};

#endif