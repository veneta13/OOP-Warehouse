#ifndef __CONTAINERS
#define __CONTAINERS
#include "product.hpp"
#include "dyn_array.hpp"
#include <iostream>

class Container {
protected:
    int capacity;

public:
    Container();
    Container(int capacity);
    Container(Container const& other);
    Container& operator=(Container const& other);
    ~Container();

    int getCapacity() const;
};


class Shelf : public Container {
    Product* products;
    void copyProducts(Product* others);

public:
    Shelf();
    Shelf(int capacity);
    Shelf(Shelf const& other);
    Shelf& operator=(Shelf const& other);
    ~Shelf();

    Product* operator[](int index) const;
    Product* at(int index) const;

    Product* findByName(char const* name);
    void findAllByName(const char* name, DynArray<Product*>& results);
    void findAllByDate(Date date, DynArray<Product*>& results);

    int addProduct(Product product, int index);
    int addProduct(Product product);

    void removeProduct(int index);

    int countProduct(char const* name);

    void list(std::ostream& out);
};


class Section : public Container {
    Shelf* shelves;
    void copyShelves(Shelf* others);

public:
    Section();
    Section(int capacity);
    Section(Section const& other);
    Section& operator=(const Section& other);
    ~Section();

    Shelf* operator[](int index) const;
    Shelf* at(int index) const;

    Product* findByName(char const* name);
    void findAllByName(const char* name, DynArray<Product*>& results);
    void findAllByDate(Date date, DynArray<Product*>& results);

    void list();
};


class Warehouse : public Container {
    Section* sections;
    void copySections(Section* others);

public:
    Warehouse();
    Warehouse(int capacity);
    Warehouse(Warehouse const& other);
    Warehouse& operator=(Warehouse const& other);
    ~Warehouse();

    Section* operator[](int index) const;

    bool addProduct(Product product);
    bool removeProduct(char const* name, int capacity);

    void list(std::ostream& out);
    void cleanup(Date const& date);
};

#endif
