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

public:
    Product();
    Product(char const* name, char const* manufacturer, char const* comment, int quantity, Date expirationDate, Date stockedDate, Placement placement);
    Product(Product const& other);
    Product& operator=(Product const& other);
    ~Product();

    bool operator==(Product const& other);
    bool operator>(Product const& other);
    bool operator<(Product const& other);
    bool hasSameName(Product const& other);

    void setName(char const* _name);
    void setManufacturer(char const* _manufacturer);
    void setComment(char const* _comment);
    void setQuantity(int _quantity);
    void setExpirationDate(Date _expirationDate);
    void setStockedDate(Date _stockedDate);
    void setPlacement(Placement _placement);
    void setIndex(int _index);
    void setShelf(int _shelf);
    void setSection(int _section);

    char const* getName() const;
    char const* getManufacturer() const;
    char const* getComment() const;
    int getQuantity() const;
    Date getExpirationDate() const;
    Date getStockedDate() const;
    Placement getPlacement() const;
    int getIndex() const;
    int getShelf() const;
    int getSection() const;
};

#endif
