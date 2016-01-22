#pragma once
//#include "RelOps.h"
#include <iostream>

using namespace std;

const int S = 1000;

struct C {
	int value;
	C(int x) :value(x){};
	C() = default;
	C(const C&) = default;
	C& operator=(C rhs) { value = rhs.value; return *this; }
	C& operator++() { ++value; return *this; }
	bool operator<(const C & rhs) const { return this->value < rhs.value; }

	friend 	ostream& operator<<(ostream & cout, C& rhs) {
		cout << rhs.value;
		return cout;
	}
private:
	char A[S];
};


//template<class T>
//ostream& operator<<(ostream & cout, vector<T> &container) {
//	bool first = true;
//	for (auto item : container) {
//		if (first) {
//			first = false;
//		}
//		else
//			cout << ", ";
//		cout << item;
//	}
//	return	cout << endl;
//
//}
//

//template<class T>
//ostream& operator<<(ostream & cout, T &container) {
//	bool first = true;
//	for (auto item : container) {
//		if (first) {
//			first = false;
//		}
//		else
//			cout << ',' << ' ';
//		cout << item;
//	}
//	return	cout << endl;
//
//}


//template<class T>
//basic_ostream<char, std::char_traits<char>>& operator<<(basic_ostream<char, std::char_traits<char>> & cout, T &container) {
//	bool first = true;
//	for (auto item : container) {
//		if (first) {
//			first = false;
//		}
//		else
//			cout << ',' << ' ';
//		cout << item;
//	}
//	return	cout << endl;
//
//}

//template<class T>
//ostream& operator+(ostream & cout, T &container) {
//	cout << container[0];
//	return cout;
//}


