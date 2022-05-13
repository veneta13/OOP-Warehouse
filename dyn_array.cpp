#include "dyn_array.hpp"
#include "product.hpp"

/// Constructor with capacity parameter
/// \tparam T type of objects saved in array
/// \param capacity the start capacity
template<class T>
DynArray<T>::DynArray(int capacity) : capacity(capacity) {
    elements = new T[capacity];
    count = 0;
}


/// Copy constructor
/// \tparam T type of objects saved in array
/// \param other array to copy
template<class T>
DynArray<T>::DynArray(const DynArray<T>& other) {
    elements = nullptr;
    copyOther(other);
}


/// Copy assignment operator
/// \tparam T type of objects saved in array
/// \param other array to copy
/// \return the updated array
template<class T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T>& other) {
    if (this != &other) {
        copyOther(other);
    }
    return *this;
}


/// Destructor
/// \tparam T type of objects saved in array
template <class T>
DynArray<T>::~DynArray() {
    clear();
}


/// Double the capacity of the array
/// \tparam T type of objects saved in array
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


/// Copy array elements
/// \tparam T type of objects saved in array
/// \param other array to be copied
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


/// Clear elements
/// \tparam T type of objects saved in array
template <class T>
void DynArray<T>::clear() {
    delete[] elements;
    elements = nullptr;
    count = 0;
}


/// Getter for array element
/// \tparam T type of objects saved in array
/// \param index the index to get element from
/// \return element at index
template <class T>
T& DynArray<T>::operator[](int index) {
    return elements[index];
}


/// Insert element at index
/// \tparam T type of objects saved in array
/// \param element element to insert
/// \param index index to insert the element at
template <class T>
void DynArray<T>::insert(T element, int index) {
    if (index > capacity - 1) { return; }

    if (count == capacity) {
        doubleSpace();
    }

    for (int i = count-1; i > index-1; i--) {
        elements[i + 1] = elements[i];
    }

    elements[index] = element;
    count++;
}


/// Push element at the end of array
/// \tparam T type of objects saved in array
/// \param element element to push
template <class T>
void DynArray<T>::push(T element) {
    if (count == capacity) {
        doubleSpace();
    }
    elements[count] = element;
    count++;
}


/// Erase element at index
/// \tparam T type of objects saved in array
/// \param index index to erase element from
template<class T>
void DynArray<T>::erase(int index) {
    if (index > capacity - 1) { return; }

    for (int i = index; i < count - 1; i++) {
        elements[i] = elements[i + 1];
    }
    count--;
}


/// Remove last element
/// \tparam T type of objects saved in array
template <class T>
void DynArray<T>::pop() {
    count--;
}


/// Getter for size
/// \tparam T type of objects saved in array
/// \return the count of elements saved in array
template <class T>
int DynArray<T>::size() const {
    return count;
}


/// Swap elements
/// \tparam T type of objects saved in array
/// \param a index of the first element
/// \param b index of the second element
/// \return if the swap was successful
template<class T>
bool DynArray<T>::swap(int a, int b) {
    if (a < 0 || b < 0 || a > count - 1 || b > count - 1) {
        return false;
    }
    if (a != b) {
        T temp = elements[b];
        elements[b] = elements[a];
        elements[a] = temp;
    }
    return true;
}

template class DynArray<Product*>;
template class DynArray<char const*>;
