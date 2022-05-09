#include "dyn_array.hpp"
#include "product.hpp"

template<class T>
DynArray<T>::DynArray(int capacity) : capacity(capacity) {
    elements = new T[capacity];
    count = 0;
}


template<class T>
DynArray<T>::DynArray(const DynArray<T>& other) {
    copyOther(other);
}


template<class T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T>& other) {
    if (this != &other) {
        copyOther(other);
    }
    return *this;
}


template <class T>
DynArray<T>::~DynArray() {
    clear();
}


template <class T>
void DynArray<T>::doubleSpace() {
    capacity *= 2;
    T* newElem = new T[capacity];

    for (int i = 0; i < count; i++) {
        newElem[i] = elements[i];
    }

    delete[] elements;
    elements = newElem;
}


template <class T>
void DynArray<T>::copyOther(const DynArray<T>& other) {
    clear();

    elements = new T[other.count];
    for (int i = 0; i < other.count; i++) {
        elements[i] = other.elements[i];
    }

    count = other.count;
    capacity = other.capacity;
}


template <class T>
void DynArray<T>::clear() {
    delete[] elements;
    elements = nullptr;
    count = 0;
}


template <class T>
T& DynArray<T>::operator[](int index) {
    return elements[index];
}


template <class T>
void DynArray<T>::insert(T element, int index) {
    if (count == capacity) {
        doubleSpace();
    }

    for (int i = count-1; i > index-1; i--) {
        elements[i + 1] = elements[i];
    }

    elements[index] = element;
    count++;
}


template <class T>
void DynArray<T>::push(T element) {
    if (count == capacity) {
        doubleSpace();
    }
    elements[count] = element;
    count++;
}


template<class T>
void DynArray<T>::erase(int index) {
    for (int i = index; i < count - 1; i++) {
        elements[i] = elements[i + 1];
    }
    count--;
}


template <class T>
void DynArray<T>::pop() {
    count--;
}


template <class T>
int DynArray<T>::size() const {
    return count;
}

template class DynArray<Product*>;
template class DynArray<char const*>;
