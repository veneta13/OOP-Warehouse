#ifndef __SECTION
#define __SECTION

#include "shelf.hpp"

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

#endif
