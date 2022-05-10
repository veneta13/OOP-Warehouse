#ifndef __SHELF
#define __SHELF

#include "container.hpp"

class Shelf : public Container {
    Product* products;

    void copyProducts(Product* others);
    void initialize();

public:
    Shelf();
    Shelf(int capacity);
    Shelf(Shelf const& other);
    Shelf& operator=(Shelf const& other);
    ~Shelf();

    Product& operator[](int index);

    Product* findByName(char const* name) const;
    Product* findEqual(char const* name, Date date) const;
    void findAllByName(const char* name, DynArray<Product*>& results) const;
    void findAllByDate(Date const& date, DynArray<Product*>& results) const;

    bool addProduct(Product const& product, int index, bool replace = false);
    Placement addProduct(Product const& product);

    void removeProduct(int index);
};

#endif
