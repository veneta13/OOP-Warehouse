#ifndef __SHELF
#define __SHELF

#include "container.hpp"

///\brief Represents a shelf in the warehouse
class Shelf : public Container {
    /// The products on the shelf
    Product* products;

    void copyProducts(Product* others);

public:
    Shelf();
    Shelf(int capacity);
    Shelf(Shelf const& other);
    Shelf& operator=(Shelf const& other);
    ~Shelf();

    Product& operator[](int index);

    Product* findByName(char const* name) const;
    Product* findEqual(char const* name, Date const& date) const;
    void findAllByName(const char* name, DynArray<Product*>& results) const;
    void findAllExpiredByDate(Date const& date, DynArray<Product*>& results) const;
    void findAllStockedBetweenDates(Date const& from, Date const& to, DynArray<Product*> &results) const;

    bool addProduct(Product const& product, int index, bool replace = false);
    Placement addProduct(Product const& product);

    Product* removeProduct(int index, int quantity);

    friend std::ostream& operator<<(std::ostream& out, Shelf const& s);
};

#endif
