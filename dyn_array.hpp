#ifndef __DYN_ARRAY
#define __DYN_ARRAY

template <class T>
class DynArray {
    int count;
    int capacity;
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

    int size() const;
};

#endif
