#ifndef __WAREHOUSE
#define __WAREHOUSE

#include "tracker.hpp"
#include "section.hpp"

class Warehouse : public Container {
    Tracker* tracker;
    Date today;

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

    void setToday(Date const& date);
    Date* getToday();
    bool setSectionCapacity(int index, int sectionCapacity);

    Product* findEqual(char const* name, Date const& date);
    void findAllByName(const char* name, DynArray<Product*>& results) const;
    void findAllExpiredByDate(Date const& date, DynArray<Product*>& results) const;
    void findAllStockedBetweenDates(Date const& from, Date const& to, DynArray<Product*> &results) const;

    bool addProduct(Product const& product, int sectionIndex, int shelfIndex, int index);
    Product* removeProduct(int sectionIndex, int shelfIndex, int index, int quantity);

    bool restock(Product const& product);

    bool takeOutProduct(std::ostream& out, std::istream& in, char const* name, int wanted);
    void cleanup(std::ostream& file, Date const& date);

    friend std::ostream& operator<<(std::ostream& out, Warehouse const& w);

    void makeQuery(std::ostream &out, const Date &from, const Date &to);
};

#endif
