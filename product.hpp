#ifndef __PRODUCT
#define __PRODUCT

#include "date.hpp"
#include "placement.hpp"
#include <cstring>

class Product {
    char* name;
    char* manufacturer;
    char* comment;

    int quantity;

    Date expirationDate;
    Date stockedDate;

    Placement placement;

    void setName(char const* _name);
    void setManufacturer(char const* _manufacturer);
    void setComment(char const* _comment);

public:
    Product();
    Product(char* name, char* manufacturer, char* comment, int quantity, Date expirationDate, Date stockedDate, Placement placement);
    Product(Product const& other);
    Product& operator=(Product const& other);
    ~Product();

    bool operator==(Product const& other);
    bool operator>(Product const& other);
    bool operator<(Product const& other);
    bool hasSameName(Product const& other);
};

#endif
