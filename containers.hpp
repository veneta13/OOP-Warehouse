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

    Product& operator[](int index) const;
    Product& at(int index) const;

    Product* findByName(char const* name);
    Product* findEqual(char const* name, Date date);
    void findAllByName(const char* name, DynArray<Product*>& results);
    void findAllByDate(Date date, DynArray<Product*>& results);

    bool addProduct(Product product, int index);
    Placement addProduct(Product product);

    void removeProduct(int index);
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

    Shelf& operator[](int index) const;
    Shelf& at(int index) const;

    Product* findByName(char const* name);
    Product* findEqual(char const* name, Date date);
    void findAllByName(const char* name, DynArray<Product*>& results);
    void findAllByDate(Date date, DynArray<Product*>& results);

    bool addProduct(Product product, int shelfIndex, int index);
    Placement addProduct(Product product);

    void removeProduct(int shelfIndex, int index);
};


class Warehouse : public Container {
    Section* sections;

    void copySections(Section* others);
    int sortAndCount(DynArray<Product*> products);
    void printProducts(std::ostream& out, DynArray<Product*>& products);
    bool insufficientQuantity(std::ostream& out, std::istream& in, int productCount, DynArray<Product*>& products);

    bool addProduct(Product product, int sectionIndex, int shelfIndex, int index);
    bool addProduct(Product product);
    void removeProduct(int sectionIndex,int shelfIndex, int index);

public:
    Warehouse();
    Warehouse(int capacity);
    Warehouse(Warehouse const& other);
    Warehouse& operator=(Warehouse const& other);
    ~Warehouse();

    void operator<<(std::ostream& out);

    Product* findEqual(char const* name, Date date);
    void findAllByName(const char* name, DynArray<Product*>& results);
    void findAllByDate(Date date, DynArray<Product*>& results);

    bool insertProduct(Product product);
    bool takeOutProduct(std::ostream& out, std::istream& in, char const* name, int wanted);

    void cleanup(Date const& date);
};

#endif
