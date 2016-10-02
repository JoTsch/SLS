

// TODO: insert, binsearch, find algorithm


#ifndef _SLS_SORTEDLIST_HPP_
#define _SLS_SORTEDLIST_HPP_

#include <iostream>

#include "SLS_Iterator.hpp"

/*
 * a list accessed through binary search
 * very fast read operations
 * normal time write operations thanks to a
   combination of binary and linear search
 */
template <typename T>
class SLS_SortedList{
public:
	SLS_SortedList():
		length_(0), data_(nullptr)
	{}

	~SLS_SortedList(){
		delete[] data_;
		length_ = 0;
	}
	//adds element to list
	bool push(const T& idata);
	bool erase(SLS_Inputiterator<T> it);
	bool erase(const T& odata);
	bool pop_front(void);
	bool pop_back(void);
	//*returns -1 if element doesn't exist
	//*uses binary search
	int find(const T& idata) const;

	int length(void) const{ return length_; }

	const SLS_Inputiterator<T>* begin(void){
		return new SLS_Inputiterator<T>(&data_[0]);
	}
	const SLS_Inputiterator<T>* last(void){
		return new SLS_Inputiterator<T>(&data_[length_ - 1]);
	}
	const SLS_Inputiterator<T>* end(void){
		T* t = &data_[length_ - 1];
		t++;
		return new SLS_Inputiterator<T>(t);
	}

	const T& operator[](int index) const;

private:
	T *data_;
	std::size_t length_;

	int bin_search(const T& idata) const;
	// * returns the position where the next data_ is bigger than 
	//		the searched data for the first time
	// * index where an element would be if it existed
	int lin_search(const T& idata, int startInd = 0) const;
	void insert(const T& idata);
	void remove(int index);
};

template <typename T>
bool SLS_SortedList<T>::push(const T& idata){

	if (length_ == 0){
		data_ = new T;
		*data_ = idata;
		length_ = 1;
	}
	else{

		if (this->find(idata) != -1){
			return false;
		}
		else{
			this->insert(idata);
			return true;
		}
	}
}

template <typename T>
bool SLS_SortedList<T>::erase(SLS_Inputiterator<T> it){
	return erase(*it);
}

template <typename T>
bool SLS_SortedList<T>::erase(const T& odata){
	int ind = find(odata);
	if (ind < 0){
		return false;
	}
	else{
		remove(ind);
		return true;
	}
}

template <typename T>
bool SLS_SortedList<T>::pop_front(void){
	return erase(this->begin());
}

template <typename T>
bool SLS_SortedList<T>::pop_back(void){
	return erase(this->end() - 1);
}

template <typename T>
int SLS_SortedList<T>::find(const T& idata) const{
	int ind = bin_search(idata);

	if (data_[ind] != idata)
		return -1;
	else
		return ind;
}

template <typename T>
const T& SLS_SortedList<T>::operator[](int index) const{

	if (index < 0)
		index = 0;
	if (index >= length_)
		index = length_ - 1;

	return static_cast<T const&>(data_[index]);
}

template <typename T>
int SLS_SortedList<T>::bin_search(const T& idata) const{
	int lnghLef = length_;
	int currInd = 0;

	while (lnghLef != 0){

		if (lnghLef == 1){
			lnghLef = 0;
		}
		else{
			lnghLef = div(lnghLef, 2).quot;
		}

		if (data_[currInd + lnghLef] == idata){
			currInd += lnghLef;
			break;
		}
		else if (data_[currInd + lnghLef] < idata){
			currInd += lnghLef;
		}
		else if (data_[currInd + lnghLef] > idata){
			//do nothing to the current Index
		}
	}

	if (currInd > length_ - 1)
		currInd = length_ - 1;

	return currInd;
}

template <typename T>
int SLS_SortedList<T>::lin_search(const T& idata, int startInd) const{
	if (startInd >= length_)
		startInd = length_;
	else if (startInd < 0)
		startInd = 0;

	if (length_ == 1){
		if (idata < data_[0])
			return 0;
		else if (idata > data_[0])
			return 1;
	}

	for (int i = startInd; i < length_; i++){
		if (i < length_ - 1){
			if (idata < data_[i + 1]){
				return i;
			}
		}
		else{
			//exceptoin handling: if the searched element is bigger than the last element in the list
			//					  than the algo has to return the current length cause that's where 
			//					  the element would be
			//					  else it returns length_ -1 in this case i
			if (idata > data_[length_ - 1])
				return length_;
			else
				return i;
		}

	}
}

template <typename T>
void SLS_SortedList<T>::insert(const T& idata){
	/*
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	| * if the searched element isn't in the list the binary search points to the   |
	| * element right before it													    |
	| * setting this as the startpoint of the linear search can speed thinks really |
	| * up																		    |
	|_______________________________________________________________________________|
	*/
	int ind = lin_search(idata, bin_search(idata));

	length_ += 1;
	T* temp = (T*)malloc(length_ * sizeof(T));

	for (int i = 0; i < length_; i++){
		if (i < ind){
			temp[i] = data_[i];
		}
		else if (i == ind){
			temp[i] = idata;
		}
		else{
			temp[i] = data_[i - 1];
		}
	}

	delete[] data_;
	data_ = new T;
	data_ = (T*)malloc(length_ * sizeof(T));
	memcpy(data_, temp, length_ * sizeof(T));
	delete[] temp;
}

template <typename T>
void SLS_SortedList<T>::remove(int index){
	length_ -= 1;
	for (int i = index; i < length_; i++){
		data_[i] = data_[i + 1];
	}
}


#endif