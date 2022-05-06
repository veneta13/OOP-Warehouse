#ifndef __CONTAINERS
#define __CONTAINERS
#include "product.hpp"

class Container {
protected:
    int capacity;

public:
    Container(int capacity);
    Container(Container const& other);
    Container& operator=(Container const& other);
    ~Container();

    Product* findByName(char* name);
    Product* findByIndex(int index);
    Product* findByExpirationDate(Date const& expirationDate);
};


class Shelf : public Container {
    Product* products = nullptr;
    void copyProducts(Product* others);

public:
    Shelf(int capacity);
    Shelf(Shelf const& other);
    Shelf& operator=(Shelf const& other);
    ~Shelf();
};


class Section : public Container {
    Shelf* shelves = nullptr;
    void copyShelves(Shelf* others);

public:
    Section(int capacity);
    Section(Section const& other);
    Section& operator=(const Section& other);
    ~Section();
};

#endif
