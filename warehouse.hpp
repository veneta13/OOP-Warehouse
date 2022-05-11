#ifndef __WAREHOUSE
#define __WAREHOUSE

#include "section.hpp"

class Warehouse : public Container {
    Section* sections;

    void copySections(Section* others);
    int sortAndCount(DynArray<Product*> products) const;
    void printProducts(std::ostream& out, DynArray<Product*>& products) const;
    bool insufficientQuantity(std::ostream& out, std::istream& in, int productCount, DynArray<Product*>& products) const;

    bool addProduct(Product const& product);
    void removeProduct(int sectionIndex,int shelfIndex, int index);

public:
    Warehouse();
    Warehouse(int capacity);
    Warehouse(Warehouse const& other);
    Warehouse& operator=(Warehouse const& other);
    ~Warehouse();

    Section& operator[](int index);

    bool setSectionCapacity(int index, int sectionCapacity);

    Product* findEqual(char const* name, Date const& date);
    void findAllByName(const char* name, DynArray<Product*>& results) const;
    void findAllByDate(Date const& date, DynArray<Product*>& results);

    bool addProduct(Product const& product, int sectionIndex, int shelfIndex, int index);
    Product* removeProduct(int sectionIndex, int shelfIndex, int index, int quantity);

    bool restock(Product const& product);

    bool takeOutProduct(std::ostream& out, std::istream& in, char const* name, int wanted);
    void cleanup(std::ostream& file, Date const& date);

    friend std::ostream& operator<<(std::ostream& out, Warehouse const& w);
};

#endif
