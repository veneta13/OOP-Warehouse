#ifndef __DYN_ARRAY
#define __DYN_ARRAY

/// Dynamic size array template
/// \tparam T type of objects saved in array
template <class T>
class DynArray {
    /// The amount of objects currently saved
    int count;

    /// The current max capacity
    int capacity;

    /// The elements currently saved
    T* elements;

    void doubleSpace();
    void copyOther(const DynArray<T>& arr);
    void clear();

public:
    DynArray(int capacity);
    DynArray(const DynArray<T>& arr);
    DynArray& operator=(const DynArray<T>& arr);
    ~DynArray();

    T& operator[](int index);

    void insert(T element, int index);
    void push(T element);

    void erase(int index);
    void pop();

    bool swap(int a, int b);

    int size() const;
};

#endif
