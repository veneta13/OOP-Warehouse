#include "product.hpp"

Product::Product() {
    name = nullptr;
    manufacturer = nullptr;
    comment = nullptr;
    quantity = 0;
    expirationDate = Date();
    stockedDate = Date();
    placement = Placement();
}


Product::Product(char const* name, char const* manufacturer, char const* comment, int quantity, Date expirationDate, Date stockedDate, Placement placement) {
    setName(name);
    setManufacturer(manufacturer);
    setComment(comment);
    this->quantity = quantity;
    this->expirationDate = expirationDate;
    this->stockedDate = stockedDate;
    this->placement = placement;
}


Product::Product(Product const& other) {
    setName(other.name);
    setManufacturer(other.manufacturer);
    setComment(other.comment);
    this->quantity = other.quantity;
    this->expirationDate = other.expirationDate;
    this->stockedDate = other.stockedDate;
    this->placement = other.placement;
}


Product& Product::operator=(Product const& other) {
    if (this != &other) {
        setName(other.name);
        setManufacturer(other.manufacturer);
        setComment(other.comment);
        this->quantity = other.quantity;
        this->expirationDate = other.expirationDate;
        this->stockedDate = other.stockedDate;
        this->placement = other.placement;
    }
    return *this;
}


Product::~Product() {
    delete[] name;
    name = nullptr;
    delete[] manufacturer;
    manufacturer = nullptr;
    delete[] comment;
    comment = nullptr;
    quantity = 0;
    delete &expirationDate;
    delete &stockedDate;
    placement = Placement();
}


void Product::setName(char const* _name) {
    delete[] name;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}


void Product::setManufacturer(char const* _manufacturer) {
    delete[] manufacturer;
    manufacturer = new char[strlen(_manufacturer) + 1];
    strcpy(manufacturer, _manufacturer);
}


void Product::setComment(char const* _comment) {
    delete[] comment;
    comment = new char[strlen(_comment) + 1];
    strcpy(comment, _comment);
}


void Product::setQuantity(int _quantity) {
    quantity = _quantity;
}


void Product::setPlacement(Placement _placement) {
    placement = _placement;
}


void Product::setIndex(int _index) {
    placement.index = _index;
}


void Product::setShelf(int _shelf) {
    placement.shelf = _shelf;
}


void Product::setSection(int _section) {
    placement.section = _section;
}


bool Product::operator==(Product const& other) {
    if (hasSameName(other) && (expirationDate == other.expirationDate)) {
        return true;
    }
    return false;
}

bool Product::operator>(Product const& other) {
    if (hasSameName(other) && (expirationDate > other.expirationDate)) {
        return true;
    }
    return false;
}


bool Product::operator<(Product const& other) {
    if (hasSameName(other) && (expirationDate < other.expirationDate)) {
        return true;
    }
    return false;
}


bool Product::hasSameName(Product const& other) {
    if (strcmp(name, other.name) == 0) {
        return true;
    }
    return false;
}


char const* Product::getName() const {
    return name;
}


char const* Product::getManufacturer() const {
    return manufacturer;
}


char const* Product::getComment() const {
    return comment;
}


int Product::getQuantity() const {
    return quantity;
}


Date Product::getExpirationDate() const {
    return expirationDate;
}


Date Product::getStockedDate() const {
    return stockedDate;
}


Placement Product::getPlacement() const {
    return placement;
}
 