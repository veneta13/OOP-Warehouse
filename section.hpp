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

    Shelf& operator[](int index);

    bool setShelfCapacity(int index, int shelfCapacity);

    Product* findByName(char const* name) const;
    Product* findEqual(char const* name, Date const& date) const;
    void findAllByName(const char* name, DynArray<Product*>& results) const;
    void findAllByDate(Date const& date, DynArray<Product*>& results) const;

    bool addProduct(Product const& product, int shelfIndex, int index);
    Placement addProduct(Product const& product);

    void removeProduct(int shelfIndex, int index);
};

#endif
