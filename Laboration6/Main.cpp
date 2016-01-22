#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <iostream>
#include "TestTypes.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "String.h"
#include "HiResTimer.h"


const int NofStrings = 10000;
const int MaxLengthofString = 100;

using namespace std;

//function that sorts using forward iterators
template <class ForwardIterator>
void ForwardSort(ForwardIterator begin, ForwardIterator end) {
	ForwardIterator i, j;
	for (i = begin; i != end; i++)
		for (j = begin; j != i; j++)
			if (*i < *j)
				std::iter_swap(i, j);
}

//function that sorts using forward iteration but also uses a lambda function 
//to set the criteria of the sort
template <class ForwardIterator, class Func>
void ForwardSortLambda(ForwardIterator begin, ForwardIterator end, Func func) {
	ForwardIterator i, j;
	for (i = begin; i != end; i++)
		for (j = begin; j != i; j++)
			if (func(*i, *j))
				std::iter_swap(i, j);
}

//function that sorts using backward iterators
template <class BackwardIterator>
void BackwardSort(BackwardIterator begin, BackwardIterator end) {
	BackwardIterator i, j;
	for (i = begin; i != end; i++)
		for (j = begin; j != i; j++)
			if (*i < *j)
				std::iter_swap(i, j);
}

//function that prints
void print(string s, vector<C> v) {

	cout << s.data() << endl << endl;

	for (auto it = v.begin(); it != v.end(); ++it) {
		cout << *it << endl;
	}

	cout << endl;
}

//assignment1
void task1() {

	vector<C> vec;

	for (int i = 0; i < 10; ++i) {
		vec.push_back(C(rand()));
	}

	print("assignment 1 before removal", vec);
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](const C value) { return (value.value % 2) == 1; }), vec.end());
	print("assignment 1 after removal", vec);
}

//assignment 2A and 2B
void task2() {

	vector<C> vec;

	for (int i = 0; i < 10; ++i) {
		vec.push_back(C(rand()));
	}

	ForwardSort(vec.begin(), vec.end());
	print("assignment 2", vec);
}

//assignment 3A
void task3A() {
	vector<C> vec;

	for (int i = 0; i < 10; ++i) {
		vec.push_back(C(rand()));
	}
	print("assignment 3A before sort", vec);
	BackwardSort(vec.rbegin(), vec.rend());
	print("assignment 3A after sort", vec);

}

//assignment 3B
void task3B() {
	vector<C> vec;

	for (int i = 0; i < 10; ++i) {
		vec.push_back(C(rand()));
	}
	print("Assignment 3B before sort", vec);
	ForwardSortLambda(vec.rbegin(), vec.rend(), [](C a, C b) { return a.value > b.value; });
	print("Assignment 3B after sort", vec);

}

//assignment 4
void task4() {
	vector<C> vec;

	for (int i = 0; i < 10; ++i) {
		vec.push_back(C(rand()));
	}
	print("assignment 4 before sort", vec);
	std::sort(vec.begin(), vec.end(), [](C a, C b) { return a.value < b.value; });
	print("assignment 4 after sort", vec);
}

char GenRandLetter() {
	return ('a' + (rand()*('z' - 'a' + 1) / RAND_MAX));
}

template<class str>
double GenerateStrings(vector<str>& VectorOfString) {
	HiResTimer timer;
	VectorOfString.resize(0);
	VectorOfString.shrink_to_fit();
	VectorOfString.resize(NofStrings);
	timer.Start();
	for (unsigned i = 0; i < VectorOfString.size(); ++i) {
		int length = MaxLengthofString* rand() / RAND_MAX;
		for (int j = 0; j < length; ++j)
			VectorOfString[i].push_back(GenRandLetter());
	}
	timer.Stop();
	return timer.GetDeltaTime();
}

//assignment 5
double task5S() {
	vector<String> myStrings;
	double timeS = GenerateStrings(myStrings);
	return timeS;

}

double task5s() {
	vector<string> mystrings;
	double times = GenerateStrings(mystrings);
	return times;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	double S = 0, s = 0;
	task1();
	task2();
	task3A();
	task3B();
	task4();
	S += task5S();
	s += task5s();
	S += task5S();
	s += task5s();
	S += task5S();
	s += task5s();
	S += task5S();
	s += task5s();
	S += task5S();
	s += task5s();
	std::cout << S / 5 << " S : s " << s / 5 << std::endl;

	cin.get();
}