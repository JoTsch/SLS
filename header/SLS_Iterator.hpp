#ifndef _SLS_ITERATOR_HPP_
#define _SLS_ITERATOR_HPP_


#include <iostream>

//readaccess only (siehe unten Erklärung)
//
template <typename T>
class SLS_Inputiterator{
public:
	SLS_Inputiterator(void) : iter_(nullptr) {}
	SLS_Inputiterator(T* it){ iter_ = it; }
	SLS_Inputiterator(const SLS_Inputiterator<T> *rhs){ iter_ = rhs->iter_; }
	SLS_Inputiterator(const SLS_Inputiterator<T> &rhs){ iter_ = rhs.iter_; }

	~SLS_Inputiterator(void){
		iter_ = nullptr;
		delete iter_;
	}

	//dereferenceoperator
	const T& operator*(void){
		return *iter_;
	}

	//allocationoperator
	void operator=(T* it){
		iter_ = it;
	}

	void operator=(const SLS_Inputiterator<T> &rhs){
		iter_ = rhs.iter_;
	}

	void operator+(int x){
		for (int i = 0; i < x; i++)
			this++;
	}

	//incrementoperator
	void operator++(void){
		iter_++;
	}

	//decrementoperator
	void operator--(void){
		iter_--;
	}

	bool operator==(const SLS_Inputiterator<T> &rhs) const{
		if (iter_ == rhs.iter_)
			return true;
		else
			return false;
	}

	bool operator!=(const SLS_Inputiterator<T> &rhs) const{
		return !(operator==(rhs));
	}

private:
	T* iter_;
};


/*

	Erklärung:

	Dadurch, dass die Daten des iterators in iter_ private sind können sie nur mit Funktionen manipuliert werden.
	Diese Funktionen existieren allerdings nicht, da der Zuweisungsoperator sich auch die Speicheradresse und nicht
	auf den Wert des aktuell gespeicherten Elementes bezieht. Und, da der Dereferenzierungsoperator nur einen const 
	Verweis auf das gerade gespeicherte Element zurückgibt kann auch hier nur lesend auf den Wert des Elementes 
	zugegriffen werden.

*/

#endif