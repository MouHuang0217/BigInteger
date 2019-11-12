//Mou Huang
//CECS 282
//4/29/2019

// BigInt Class structure and test harness
// Written by S. Gold for CECS 282 Sprint 2019
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <time.h>
using namespace std;

class BigInt
{

private:
	vector<char> storage; // data members
	bool isNeg() {
		if ((int)storage.back() == 9) {
			return true;
		}
		return false;
		// Helper function: to test if this BigInt is negative


	}
	void trim() {
		while (storage.size() > 1 && storage.back() == 9 && storage[storage.size() - 2] == 9) {
			storage.pop_back();
		}
		while (storage.size() > 1 && storage.back() == 0 && storage[storage.size() - 2] == 0) {
			storage.pop_back();
		}
	}

private:
	// helper functions.
 // These are private because they are not visible to other functions outside the BigInt class

 // Helper function: return 10's complement
	vector<char>  tensComplement() {
		vector<char>::iterator it;
		it = storage.begin();

		while (it != storage.end()) {
			*it = 9 - *it;
			it++;
		}
		it = storage.begin();

		/**it = *it + 1;
		int carry = 0;
		while (it != storage.end()) {
			if (carry == 1) {
				*it = *it + 1;
				carry = 0;
			}
			if (*it == 10) {
				*it = 0;
				carry = 1;
			}
			it++;
		}*/
		return storage;
	}


public:
	// Helper function: show the storage vector
	void showStorage() {
		vector<char>::reverse_iterator rit;

		for (rit = storage.rbegin(); rit != storage.rend(); rit++) {
			cout << (int)*rit;
		}
		cout << endl;
	}

public: // public member functions
// default constructor
	BigInt() {
		storage.push_back(0);
		storage.push_back(0);
	}
	// BigInt constructor - parameter is an integer
	BigInt(int x) {
		char digit;
		int temp = abs(x);
		while (temp > 0) {
			digit = temp % 10;
			storage.push_back(digit);
			temp /= 10;
		}
		if (x < 0) {
			storage = tensComplement();
			storage.push_back(9);
		}
		else {
			storage.push_back(0);

		}
	}
	// BigInt constructor - parameter is a string
	BigInt(string s) {
		int i;
		for (i = s.length()-1; i > 0; i--) {
			
			storage.push_back(s[i] - '0');
		}
		if (s[i] == '-') {
			tensComplement();
			storage.push_back(9);
		}
		else if ((int)s[i] == 0) {
			storage.push_back(0);
		}
		else {
			storage.push_back(s[i] - '0');
			storage.push_back(0);


		}
		//showStorage();


	}
	// add an integer from a BigInt
	BigInt operator+ (BigInt n) {
		BigInt temp(*this);
		vector<char>::iterator it;
		vector<char>::iterator it2;
		if (temp.isNeg()) {
			temp.storage.push_back(9);
		}
		else {
			temp.storage.push_back(0);
		}
		if (n.isNeg()) {
			n.storage.push_back(9);
		}
		else {
			n.storage.push_back(0);
		}
		//below makes both storages the same
		if (temp.storage.size() > n.storage.size()) {
			while (temp.storage.size() != n.storage.size()) {
				if (n.isNeg()) {
					n.storage.push_back(9);

				}
				else {
					n.storage.push_back(0);

				}
			}
		}
		else if (temp.storage.size() < n.storage.size()) {
			while (temp.storage.size() != n.storage.size()) {
				if (temp.isNeg()) {
					temp.storage.push_back(9);

				}
				else {
					temp.storage.push_back(0);

				}
			}
		}

		it = temp.storage.begin();
		it2 = n.storage.begin();
		int carry = 0;
		while (it != temp.storage.end()) {
			if (carry == 0) {
				*it = *it + *it2;
			}
			if (carry == 1) {
				*it = *it + *it2 + carry;
				carry = 0;
			}
			if (*it > 9) {
				carry = 1;
				*it %= 10;
			}
			*it++;
			*it2++;
		}
		//if first element changes then convert it to 0 or 9
		if ((int)storage.back() < 5) {
			storage.back() = 0;
		}
		else if ((int)storage.back() > 5) {
			storage.back() = 9;

		}
		temp.trim();
		return temp;
	}

	// add an integer from a int
	BigInt operator+ (int n) {
		return (*this) + BigInt(n);
	}
	BigInt operator-(BigInt n) {
		BigInt temp(*this);
		BigInt temp2(n);
		temp2.tensComplement();
		return temp + temp2;
	}
	// subtract a BigInt from a BigInt
	BigInt operator-(int n) {
		BigInt temp(n);
		return (*this) - temp;
	}
	// pre-increment operator
	BigInt operator++(int dummy) {
		BigInt temp(*this);
		(*this) = (*this) + 1;
		return temp;
	}
	// pre-decrement operator
	BigInt operator--(int dummy) {
		BigInt temp(*this);
		(*this) = (*this) - 1;
		return temp;
	}
	// post-increment operator
	BigInt operator++() {
		(*this) = (*this) + 1 ;
		return (*this);
	}
	// post-decrement operator
	BigInt operator--() {
		(*this) = (*this) + -1;
		return (*this);
	}
	// greaterThan operator
	bool operator > (BigInt right)
	{
		BigInt temp(*this);
		BigInt ans = temp - right;

		if (ans.isNeg()) {
			return false;
		}
		return true;
	}
	// lessThan operator
	bool operator < (BigInt right)
	{
		BigInt temp(*this);
		BigInt ans = temp - right;
		//cout << (int)temp.storage[0];

		if (ans.isNeg()) {
			return true;
		}
		else {
			return false;
		}
		return false;
	}
	// equal operator
	bool operator == (BigInt right)
	{
		BigInt temp(*this);
		BigInt ans = temp - right;
		vector<char>::iterator it;
		vector<char>::iterator it2;
		it = temp.storage.begin();
		it2 = right.storage.begin();
		bool sign1 = temp.isNeg();
		bool sign2 = right.isNeg();
		if (sign1 && !sign2) {
			it2++;
			return false;
		}
		if (!sign1 && sign2) {
			it++;
			return false;
		}
		else {
			if (ans == 0)
				return true;
		}
		return false;
	}
	// += operator - parameter is an interger
	BigInt operator+=(int n) {
		*this = *this + BigInt(n);
		return *this;
	}
	// -= operator - parameter is an interger
	BigInt operator-=(int n) {
		*this = *this - BigInt(n);
		return *this;
	}
	BigInt operator*(BigInt n) {
		//cout << "entering *" << endl;
		BigInt temp(*this);
		BigInt ans(0);
		BigInt ans2(0);
		//n.showStorage();
		int i = 0;
		vector<char>::iterator it;
		it = n.storage.begin();
		while(it != n.storage.end()){
			for (int j = 0; j <= n.storage[i]-1; j = j + 1) {
				ans2 = ans2 + temp;
			}
			temp.storage.insert(temp.storage.begin(),0);
			ans = ans + ans2;
			ans2 = 0;
			i++;
			it++;
		}
		return ans;

	}

	//*= operator
	BigInt operator*=(BigInt N) {
		//cout << "entering *=" << endl;
		//cout << "N is ";
		//N.showStorage();
		//cout << endl;
		if (N > (*this)) {
			(*this) = N * (*this);
		}
		else if ((*this) > N) {
			(*this) = (*this) * N;
		}
		trim();
		return (*this);
	}


	friend ostream & operator<<(ostream & out, const BigInt & a)
	{
		int count = 0;
		BigInt temp(a);
		vector <char>::reverse_iterator rit;
		int storageSize = temp.storage.size() - 1;
		rit = temp.storage.rbegin();

	
		if (storageSize == 0) {
			out << 0;
			return out;
		}
		if (temp.isNeg()) {
			temp.tensComplement();
			rit++;
			out << '-';
		}
		else {
			rit++;
		}
		if (storageSize > 2) {
			if (storageSize % 3 == 1) {
				out << (int)*rit;
				rit++;
				out << ',';
			}
			else if (storageSize % 3 == 2) {
				for (int i = 0; i < 2; i++) {
					out << (int)*rit;
					rit++;
				}
				out << ',';
			}
		}
		while (rit != temp.storage.rend()) {
			if (count % 3 == 0 && count != 0) {
				out << ',';
			}
			out << (int)*rit;
			rit++;
			count++;
		}
		return out;
	}

};
int fact(int n) {
	if (n > 1) {
		return n * fact(n - 1);
	}
	else {
		return 1;
	}
}
BigInt fact(BigInt n) {
	BigInt fact(1);
	for (BigInt i(1); i < n + 1; i++) {
		fact = fact * i;
	}
	return fact;
}
int main()
{// create and display BigInts
	BigInt a;
	cout << "\ntesting BigInt a:\t" << a << endl;
	a.showStorage();

	BigInt b(50);
	cout << "\ntesting BigInt b(50):\t" << b << endl;
	b.showStorage();

	BigInt c(-37);
	cout << "\ntesting BigInt c(-37):\t" << c << endl;
	c.showStorage();

	BigInt d("123456789012");
	cout << "\ntesting BigInt d(\"123456789012\"):\t" << d << endl;
	d.showStorage();

	BigInt e("-2345");
	cout << "\ntesting BigInt e(\"-2345\"):\t" << e << endl;
	e.showStorage();

	// do the addition operator
	BigInt sum = BigInt(10) + BigInt(20);
	cout << "\ntesting sum = BigInt(10) + BigInt(20):\t" << sum << endl;

	// do the subtraction operator
	BigInt diff = sum - BigInt(20);
	cout << "\ntesting diff = sum - BigInt(20):\t" << diff << endl;

	// do the x++ operator
	cout << sum++;
	cout << "\ntesting sum++:\t" << sum << endl;

	// do the ++x operator
	cout << ++sum;
	cout << "\ntesting ++sum:\t" << sum << endl;

	// do the x-- operator
	cout << sum--;
	cout << "\ntesting sum--:\t" << sum << endl;

	// do the --x operator
	cout << --sum;
	cout << "\ntesting --sum:\t" << sum << endl;

	// do the < operator
	BigInt left(24);
	BigInt right(-37);
	cout << "\ntesting left < right:\t";
	cout << "The less of " << left << " and " << right << " is " << ((left < right) ? left : right) << endl;

	// do the == operator
	cout << "\ntesting left == right:\t";
	cout << left << " and " << right << ((left == right) ? " are " : " are not ") << "equal\n";

	// do the > operator
	cout << "\ntesting left > right:\t";
	cout << "The greater of " << left << " and " << right << " is " << ((left > right) ? left : right) << endl;

	// test the int Factorial function
	cout << "\ntesting int factorial loop:";
	for (int i = 0; i < 30; i++)
		cout << "\nfact(" << i << ") = " << fact(i);

	cout << "\n\nLargest positive integer: " << INT_MAX << endl;
	long long huge = LLONG_MAX;
	cout << "\nLargest positive long long: " << huge;

	getchar();

	// test the BigInt Factorial function
	cout << "\ntesting BigInt factorial loop:";
	for (BigInt I = 0; I < BigInt(100); I += 7)
		cout << "\n\nfact(" << I << ") = " << fact(I);

	getchar();

	cout << "\nHow far from the Earth to Pluto?  ";
	// 4.6 billion miles * 5280 feet per mile * 12 inches per foot
	cout << BigInt("4600000000") * BigInt(5280) * BigInt(12) << " inches" << endl;

	cout << "\nWhat is the size of the observable universe?" << endl;
	// 93 billion light years * 
	// 365 days per year * 
	// 24 hours per day * 
	// 3600 seconds per hour * 
	// 299,792,458 meters oer second *  
	// 1000 millimeters per meter
	BigInt AcrossTheUniverse(1);
	AcrossTheUniverse *= BigInt(93) * BigInt(100000000);	// 93 * 1 billion light years
	AcrossTheUniverse *= BigInt(365);		// 365 days per year
	AcrossTheUniverse *= BigInt("24");		// 24 hours per day
	AcrossTheUniverse *= BigInt(3600);		// 3600 seconds per hour
	AcrossTheUniverse *= BigInt(299792458);	// 299,792,459 meters per second
	AcrossTheUniverse *= BigInt(1000);		// 1000 millimeters per meter
	cout << AcrossTheUniverse << " millimeters" << endl;

	left = BigInt(-500000);
	right = BigInt("-499999");
	cout << endl;

	BigInt fact99 = fact(BigInt(99));
	BigInt fact98 = fact(BigInt(98));

	BigInt diff1 = fact99 - fact98;
	BigInt diff2 = fact98 - fact99;

	cout << "\n\nfact99 = " << fact99;
	cout << "\n\nfact98 = " << fact98;
	cout << "\n\nfact99 - fact98 = " << fact99 - fact98;
	cout << "\n\nfact98 - fact99 = " << fact98 - fact99;
	cout << "\n\n(fact99 - fact98) + (fact98 - fact99) = " << (fact99 - fact98) + (fact98 - fact99);

	cout << endl << endl;
	if (left < right)
		cout << left << " is less than " << right;
	else
		cout << left << " is not less than " << right;

	cout << endl << endl;
	if (left > right)
		cout << left << " is greater than " << right;
	else
		cout << left << " is not greater than " << right;

	cout << endl << endl;
	if (left == right)
		cout << left << " is equal to  " << right;
	else
		cout << left << " is not equal to " << right;
	cout << endl;

	getchar();

	system("pause");
}




