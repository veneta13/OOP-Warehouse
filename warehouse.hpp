#ifndef __WAREHOUSE
#define __WAREHOUSE

#include "section.hpp"

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

    void cleanup(std::ostream& file, Date date);
};


#endif
