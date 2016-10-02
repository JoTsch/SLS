#ifndef _SLS_STRING_HPP_
#define _SLS_STRING_HPP_

#include <iostream>
#include <string>
#include <algorithm>

//MERKE: Vergleichs- und Verknüpfungsoperatoren nur Klassenmember wenn ausschließlich Objekte der gleichen Klasse benutzt werden
//		 Zugriffsoperatoren sind immer Member 

class SLS_String{
public:
	SLS_String(void);
	SLS_String(const char *cstr);
	SLS_String(const std::string &str);
	SLS_String(const SLS_String &str);

	~SLS_String(void);

	const char* c_str(void) const { return data_; }

	int length(void) const{ return length_; }

	void concat(const char *cstr);
	void concat(const SLS_String &str);

	SLS_String& operator=(const char* rhs);
	SLS_String& operator=(const SLS_String &rhs);

	SLS_String& operator+=(const char* rhs);
	SLS_String& operator+=(const SLS_String &rhs);

	const char &operator[](int ind) const;
	char &operator[](int ind);

	//returns the count of characters in front of '\0'
	//'H', 'a', 'l', 'l', 'o', '\0' returns 5
	//REMEMBER: a char* cstr = "Hallo" is a cstr[6] not just cstr[5]
	//
	static int getCstrLen(const char *cstr);

	friend const SLS_String& operator+(const SLS_String &lhs, const SLS_String &rhs);
private:

	//deletes old data_ and stores 
	//newdata content inside data_
	//also it 
	//
	void selfcopy(const char* cstr);
	void selfcopy(const SLS_String &str);
	void selfappend(const SLS_String &str);

	char *data_;
	int length_;
};


bool operator==(const SLS_String &lhs, const SLS_String &rhs);
bool operator==(const SLS_String &lhs, const char* rhs);
bool operator==(const char* lhs, const SLS_String &rhs);

bool operator!=(const SLS_String &lhs, const SLS_String &rhs);
bool operator!=(const SLS_String &lhs, const char* rhs);
bool operator!=(const char* lhs, const SLS_String &rhs);

bool operator<(const SLS_String &lhs, const SLS_String &rhs);
bool operator<(const SLS_String &lhs, const char* rhs);
bool operator<(const char *lhs, const SLS_String &rhs);

bool operator<=(const SLS_String &lhs, const SLS_String &rhs);
bool operator<=(const SLS_String &lhs, const char* rhs);
bool operator<=(const char *lhs, const SLS_String &rhs);

bool operator>(const SLS_String &lhs, const SLS_String &rhs);
bool operator>(const SLS_String &lhs, const char* rhs);
bool operator>(const char* lhs, const SLS_String &rhs);

bool operator>=(const SLS_String &lhs, const SLS_String &rhs);
bool operator>=(const SLS_String &lhs, const char* rhs);
bool operator>=(const char *lhs, const SLS_String &rhs);

#endif