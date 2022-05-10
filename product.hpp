#ifndef __PRODUCT
#define __PRODUCT

#include "date.hpp"
#include "placement.hpp"
#include <cstring>

class Product {
    char* name = nullptr;
    char* manufacturer = nullptr;
    char* comment = nullptr;

    int quantity;

    Date expirationDate;
    Date stockedDate;

    Placement placement;

public:
    Product();
    Product(const char *name, const char *manufacturer, const char *comment, int quantity, const Date &expirationDate,
            const Date &stockedDate, const Placement &placement);
    Product(Product const& other);
    Product& operator=(Product const& other);
    ~Product();

    bool operator==(Product const& other) const;
    bool operator>(Product const& other) const;
    bool operator<(Product const& other) const;
    bool hasSameName(Product const& other) const;

    void setName(char const* _name);
    void setManufacturer(char const* _manufacturer);
    void setComment(char const* _comment);
    void setQuantity(int _quantity);
    void setExpirationDate(Date const& _expirationDate);
    void setStockedDate(Date const& _stockedDate);
    void setPlacement(Placement const& _placement);
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
