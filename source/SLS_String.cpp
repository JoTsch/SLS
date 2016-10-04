#include "SLS_String.hpp"

SLS_String::SLS_String(void)
	:length_(0), data_(new char[1])
{}

SLS_String::SLS_String(const char *cstr)
	: length_(0), data_(new char[1])
{
	selfcopy(cstr);
}

SLS_String::SLS_String(const SLS_String &str)
	: length_(0), data_(new char[1])
{
	selfcopy(str);
}

SLS_String::~SLS_String(void){
	delete[] data_;
	length_ = 0;
}

void SLS_String::concat(const char *cstr){
	*this += cstr;
}

void SLS_String::concat(const SLS_String &str){
	*this += str;
}

SLS_String& SLS_String::operator=(const char *rhs){
	selfcopy(rhs);
	return *this;
}

SLS_String& SLS_String::operator=(const SLS_String &rhs){
	selfcopy(rhs);
	return *this;
}

SLS_String& SLS_String::operator+=(const SLS_String &rhs){
	selfappend(rhs);
	return *this;
}

SLS_String& SLS_String::operator+=(const char* rhs){
	SLS_String temp = rhs;
	selfappend(temp);
	return *this;
}

const char &SLS_String::operator[](int ind) const{
	if (ind < 0)
		return data_[0];
	else if (ind >= length_)
		return data_[length_ - 1];
	else
		return data_[ind];
}

char &SLS_String::operator[](int ind){
	return const_cast<char&>(
		static_cast<const SLS_String&>(*this)[ind]
		);
}

bool operator==(const SLS_String &lhs, const SLS_String &rhs){

	if (lhs.length() != rhs.length())
		return false;

	for (int i = 0; i < rhs.length(); i++){
		if (lhs[i] != rhs[i])
			return false;
	}

	return true;
}

bool operator==(const SLS_String &lhs, const char* rhs){
	return lhs == SLS_String(rhs);
}

bool operator==(const char* lhs, const SLS_String &rhs){
	return SLS_String(lhs) == rhs;
}

bool operator!=(const SLS_String &lhs, const SLS_String &rhs){
	return !(lhs == rhs);
}

bool operator!=(const SLS_String &lhs, const char* rhs){
	return !(lhs == rhs);
}

bool operator!=(const char* lhs, const SLS_String &rhs){
	return !(lhs == rhs);
}

bool operator<(const SLS_String& lhs, const SLS_String& rhs){
	for (int i = 0; i < std::min(lhs.length(), rhs.length()); i++){
		if (lhs[i] < rhs[i])
			return true;
		else if (lhs[i] > rhs[i])
			return false;
	}

	if (lhs.length() < rhs.length())
		return true;
	else
		return false;
}

bool operator<(const SLS_String& lhs, const char* rhs){
	return lhs < SLS_String(rhs);
}

bool operator<(const char* lhs, const SLS_String& rhs){
	return SLS_String(lhs) < rhs;
}

bool operator<=(const SLS_String& lhs, const SLS_String& rhs){
	if (lhs == rhs)
		return true;
	else if (lhs < rhs)
		return true;
	else
		return false;
}

bool operator<=(const SLS_String& lhs, const char* rhs){
	return lhs <= SLS_String(rhs);
}

bool operator<=(const char* lhs, const SLS_String& rhs){
	return SLS_String(lhs) <= rhs;
}

bool operator>(const SLS_String& lhs, const SLS_String& rhs){
	return !(lhs <= rhs);;
}

bool operator>(const SLS_String& lhs, const char* rhs){
	return lhs > SLS_String(rhs);
}

bool operator>(const char* lhs, const SLS_String& rhs){
	return SLS_String(lhs) > rhs;
}

bool operator>=(const SLS_String& lhs, const SLS_String& rhs){
	return !(lhs < rhs);
}

bool operator>=(const SLS_String& lhs, const char* rhs){
	return lhs >= SLS_String(rhs);
}

bool operator>=(const char* lhs, const SLS_String& rhs){
	return SLS_String(lhs) >= rhs;
}

int SLS_String::getCstrLen(const char *cstr){
	int len = 0;
	while (cstr[len] != '\0'){
		len++;
	}
	return len;
}

void SLS_String::selfcopy(const char *cstr){
	length_ = SLS_String::getCstrLen(cstr);
	delete[] data_;
	data_ = new char[length_ + 1];					//the '\0' also needs a byte of memory therefor + 1
	memcpy(data_, cstr, (length_ + 1));				//length_ + 1 cause without it wouldn't copy the '\0'
}

void SLS_String::selfcopy(const SLS_String &str){
	length_ = str.length_;
	delete[] data_;
	data_ = new char[str.length_ + 1];				//the '\0' also needs a byte of memory therefor + 1
	memcpy(data_, str.data_, (str.length_ + 1));	//length_ + 1 cause without it wouldn't copy the '\0'
}

void SLS_String::selfappend(const SLS_String &str){

	char *temp = new char[length_];
	memcpy(temp, data_, length_);

	//temp var
	int len = length_;

	length_ += str.length_;
	delete[] data_;
	data_ = new char[length_ + 1];					//the '\0' also needs a byte of memory therefor + 1

	memcpy(
		data_,
		temp,
		len						//copy just the part of the string in front of '\0'
		);

	memcpy(
		data_ + len,
		str.data_,
		str.length_ + 1			//copy the whole string with the '\0'
		);
}