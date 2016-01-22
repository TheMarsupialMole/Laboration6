#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#include <utility>

#include "String.h"
#include <iostream>
#include <cassert>

//default konstruktor...skapar ett string-objekt som har en char array med tio tecken.
String::String(){
	capac = 10;
	strPtr = new char[capac];
	siz = 0; 
}

//destruktor som deallokerar char arrayen
String::~String(){
	delete[] strPtr;
}

//copy constructor
String::String(const String& rhs){
	
	//int count = (rhs.size() +1); //kolla antal tecken på parametern
	String::capac = rhs.size() * 2;	//sätt kapaciteten = antal tecken ggr 2
	strPtr = new char[capac];	//skapa en ny array med överdimensionerad storlek
	String::siz = rhs.size();	//sätt siz = antal verkliga tecken i strängen.

	for (int i = 0; i < rhs.size(); i++) {
		strPtr[i] = rhs.strPtr[i];	//kopiera in tecken från parametern till den nya strängen(this)
	}
}

////move constructor
//String::String(String&& rhs) {
//
//	siz = rhs.size();
//	capac = rhs.capacity();
//	strPtr = rhs.strPtr;
//	rhs.siz = 0;
//	rhs.capac = 0;
//	rhs.strPtr = nullptr;
//
//}

//konstruktor som tar en char array
String::String(const char* cstr) {

	int count = sLengthInclNull(cstr);
	String::capac = count * 2;
	strPtr = new char[capac] ;
	String::siz = count - 1;

	for (int i = 0; i < count; i++) {
		strPtr[i] = cstr[i];
	}

}

//sätter detta objektet till samma som parameterobjektet
String& String::operator=(const String& rhs) {
	if (strPtr != rhs.strPtr) {
		delete[]this->strPtr;
		//int count = (rhs.size() + 1); //kolla antal tecken på parametern
		String::capac = rhs.size() * 2;	//sätt kapaciteten = antal tecken ggr 2
		this->strPtr = new char[capac] {};	//skapa en ny array med överdimensionerad storlek
		String::siz = rhs.size(); // count - 1;	//sätt siz = antal verkliga tecken i strängen.

		for (int i = 0; i < rhs.size(); i++) {
			strPtr[i] = rhs.strPtr[i];	//kopiera in tecken från parametern till den nya strängen(this)
		}
	}
	return *this;
}

//sätter detta objektets variabler lika med den inkommande char arrayen
String& String::operator=(const char* cstr) {
	delete[]this->strPtr;
	int count = sLengthInclNull(cstr);
	String::capac = count * 2;
	strPtr = new char[capac];
	String::siz = count - 1;

	for (int i = 0; i < count; i++) {
		strPtr[i] = cstr[i];
	}

	return *this;
}

//detta objektet blir en character långt
String& String::operator=(char ch) {
	char* in = new char[1]{};
	in[0] = ch;
	delete []strPtr;
	strPtr = in;
	siz = 1;
	capac = 1;
	return *this;
}

//returnerar char vid positionen som kommer in i parametern
char& String::at(const int i) {

	if (i < size() && i > -1) {
		return strPtr[i];
	}
	throw std::out_of_range("Out of range");
}

//returnerar char vid positionen som kommer in i parametern
//const char& String::at(const int i) const{
//
//	if (i < sLengthInclNull(strPtr) && i > -1) {
//		return strPtr[i];
//	}
//	throw std::out_of_range("Out of range");
//}

//returnerar char vid positionen som kommer in i parametern
char& String::operator[](const int i) {
	if (i < sLengthInclNull(strPtr) && i > -1) {
		return strPtr[i];
	}
}

//returnerar char vid positionen som kommer in i parametern
//const char& String::operator[](const int i) const{
//	if (i < sLengthInclNull(strPtr) && i > -1) {
//		return strPtr[i];
//	}
//}

//returnerar datan i objektet(char arrayen)
const char* String::data() const {
	return strPtr;
}

//returnerar antalet tecken i objektets char array
int String::size() const
{
	return String::siz;
}

//anger ny storlek på arrayen
void String::reserve(int newCapacity) {
	if (newCapacity > capac) {
		char* tmp = new char[newCapacity];

		for (int i = 0; i < siz + 1; ++i) {
			tmp[i] = strPtr[i];
		}
		tmp[siz + 1] = '\0';
		delete[] strPtr;
		strPtr = tmp;
		capac = newCapacity;
	}
}

//returnerar kapaciteten på arrayen
int String::capacity() const
{
	return String::capac;
}

//lägger till ett tecken sist i arrayen
void String::push_back(char c) {
	if (siz + 1 < capac) {
		strPtr[siz] = c;
		++siz;
	}
	else {
		reserve(capac * 2);
		push_back(c);
	}
	strPtr[siz] = '\0';
}

//krymper arrayen så att den precis får plats med strängen inklusive '\0' i slutet
void String::shrink_to_fit(){
	String tmp = String(strPtr);
	capac = siz + 1;
	delete[]strPtr;
	strPtr = new char[capac] {};
	
	for (int i = 0; i < capac; ++i)
		strPtr[i] = tmp.strPtr[i];

}

//skalar om arrayen
void String::resize(int n) {

	if (n < siz) {	//om den nya storleken är mindre än nuvarande sträng
		char* tmp = new char[n] {};
		for (int i = 0; i < n; ++i) {
			tmp[i] = strPtr[i];
		}
		delete[]strPtr;
		strPtr = tmp;
		siz = n;
		capac = n;
	}
	else {
		if(n > capac)	//om nya storleken är större än nuvarande kapacitet
			reserve(n);
		else {			//om nya storleken är mellan strängstorlek och kapacitet
			char* tmp = new char[n] {};
			for (int i = 0; i < siz; ++i) {
				tmp[i] = strPtr[i];
			}
			delete[]strPtr;
			strPtr = tmp;
		}
	}
}

//konkatenerar
String& String::operator+=(const String& rhs) {//kolla om strängen redan får plats utan att allokera nytt
	int tmp = (size() + rhs.size());
	if (tmp < capacity()) {
		for (int i = size(), j = 0; i < tmp; ++i, ++j) {
			strPtr[i] = rhs.strPtr[j];
		}
	}
	else {
		char* newArr = new char[tmp];
		for (int i = 0; i < size(); ++i) {
			newArr[i] = strPtr[i];
		}
		for (int i = size(), j = 0; j < rhs.size(); ++i, ++j) {
			newArr[i] = rhs.strPtr[j];
		}
		delete[]strPtr;
		strPtr = newArr;
		capac = (tmp);
	}
	siz = tmp;
	
	return *this;
}

//konkatenerar
String& String::operator+=(const char* cstr) {
 	String tmp(cstr);
	*this = operator+=(tmp);
	return *this;
}

//metod som returnerar antal tecken hos parametern inklusive (ett)Null-tecken i slutet
const int String::sLengthInclNull(const char* str) const {
	int count = 0;
	while (str[count] != '\0') {
		count++;
	}
	count++;
	return count;
}

const String String::operator+(const String &rhs) {
	return String(*this)+=rhs;
}

