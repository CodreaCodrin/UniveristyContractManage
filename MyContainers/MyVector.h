#pragma once

#define INITIAL_CAPACITY 2
template<typename TElem>
class IteratorVector;

template<typename TElem>
class MyVector {
	friend class IteratorVector<TElem>;

private:
	int lg;
	int cap;
	TElem* elems;

	//check for space resizing
	void ensure_Capacity();

public:
	MyVector();
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);
	~MyVector();

	void add(const TElem& elem);
	TElem& operator[](int index);
	const TElem& operator[](int index) const;

	void erase(IteratorVector<TElem> position);
	IteratorVector<TElem> begin() const;
	IteratorVector<TElem> final() const;

	int get_size() const;

	IteratorVector<TElem> find_elem(const TElem& elem);

	/*
	Move constructor
	Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
	Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	*/
	MyVector(MyVector&& ot); //rule of 5 

	/*
	Move assignment
	Similar cu move constructor
	Folosit la assignment
	*/
	MyVector& operator=(MyVector&& ot); //rule of 5 
};

template<typename TElem>
inline void MyVector<TElem>::ensure_Capacity()
{
	if (lg < cap) {
		return; //mai avem loc
	}

	cap *= 2;
	TElem* aux = new TElem[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
}

template<typename TElem>
MyVector<TElem>::MyVector() : elems{ new TElem[INITIAL_CAPACITY] }, cap{ INITIAL_CAPACITY }, lg{ 0 } {
}

template<typename TElem>
MyVector<TElem>::~MyVector() {
	delete[] elems;
}

template<typename TElem>
MyVector<TElem>& MyVector<TElem>::operator=(const MyVector<TElem>& other)
{
	if (this == &other) {
		return *this;//s-a facut l=l;
	}
	delete[] elems;
	elems = new TElem[other.cap];
	//copiez elementele
	for (int i = 0; i < other.lg; i++) {
		elems[i] = other.elems[i];  //assignment din Pet
	}
	lg = other.lg;
	cap = other.cap;
	return *this;
}

template<typename TElem>
TElem& MyVector<TElem>::operator[](int index)
{
	return elems[index];
}

template<typename TElem>
void MyVector<TElem>::erase(IteratorVector<TElem> position)
{
	int index = position.poz;
	for (int i = index; i < lg - 1; ++i) {
		elems[i] = elems[i + 1];
	}

	lg--;
}

template<typename TElem>
int MyVector<TElem>::get_size() const
{
	return lg;
}

template<typename TElem>
IteratorVector<TElem> MyVector<TElem>::find_elem(const TElem& elem)
{
	int i;
	for (i = 0; i < lg; i++)
		if (elems[i] == elem)
			return IteratorVector<TElem>(*this, i);
	return IteratorVector<TElem>(*this, i + 1);
}

template<typename TElem>
MyVector<TElem>::MyVector(MyVector&& ot)
{
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.  
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}

template<typename TElem>
MyVector<TElem>& MyVector<TElem>::operator=(MyVector<TElem>&& ot)
{
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.  
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}

template<typename TElem>
const TElem& MyVector<TElem>::operator[](int index) const
{
	return elems[index];
}

template<typename TElem>
void MyVector<TElem>::add(const TElem& elem)
{
	ensure_Capacity();
	elems[lg++] = elem;
}

template<typename TElem>
MyVector<TElem>::MyVector(const MyVector<TElem>& other) {
	elems = new TElem[other.cap];
	//copiez elementele
	for (int i = 0; i < other.lg; i++) {
		elems[i] = other.elems[i];
	}
	lg = other.lg;
	cap = other.cap;
}

template<typename TElem>
IteratorVector<TElem> MyVector<TElem>::begin() const
{
	return IteratorVector<TElem>(*this);
}

template<typename TElem>
IteratorVector<TElem> MyVector<TElem>::final() const
{
	return IteratorVector<TElem>(*this, lg);
}

template<typename TElem>
class IteratorVector
{
	friend class MyVector<TElem>;
private:
	const MyVector<TElem>& v;
	int poz = 0;
public:
	IteratorVector(const MyVector<TElem>& v) noexcept;
	IteratorVector(const MyVector<TElem>& v, int poz) noexcept;
	bool valid()const;
	TElem& element() const;
	void next();

	TElem& operator*();
	IteratorVector& operator++();
	bool operator==(const IteratorVector<TElem>& ot) noexcept;
};

template<typename TElem>
IteratorVector<TElem>::IteratorVector(const MyVector<TElem>& v) noexcept : v{ v } {
}

template<typename TElem>
IteratorVector<TElem>::IteratorVector(const MyVector<TElem>& v, int poz) noexcept : v{ v }, poz{ poz } {
}

template<typename TElem>
bool IteratorVector<TElem>::valid() const
{
	return poz < v.lg;
}

template<typename TElem>
TElem& IteratorVector<TElem>::element() const
{
	return v.elems[poz];
}

template<typename TElem>
void IteratorVector<TElem>::next() {
	poz++;
}

template<typename TElem>
TElem& IteratorVector<TElem>::operator*()
{
	return element();
}

template<typename TElem>
IteratorVector<TElem>& IteratorVector<TElem>::operator++()
{
	next();
	return *this;
}

template<typename TElem>
bool IteratorVector<TElem>::operator==(const IteratorVector<TElem>& ot) noexcept
{
	return poz == ot.poz;
}
