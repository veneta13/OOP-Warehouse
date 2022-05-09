#ifndef __SHELF
#define __SHELF

#include "container.hpp"

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

#endif
