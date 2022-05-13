#include "product.hpp"

/// Default constructor
Product::Product() : name(nullptr), manufacturer(nullptr), comment(nullptr) {
    quantity = 0;
    expirationDate = Date();
    stockedDate = Date();
    placement = Placement();
}

/// Constructor with parameters
/// \param name The name of the product
/// \param manufacturer The manufacturer of the product
/// \param comment A comment
/// \param quantity The quantity of the batch
/// \param expirationDate The batch expiration date
/// \param stockedDate The batch stocked date
/// \param placement The placement of the batch in the warehouse
Product::Product(char const* name, char const* manufacturer, char const* comment, int quantity,
                 Date const& expirationDate, Date const& stockedDate, Placement const& placement) {
    setName(name);
    setManufacturer(manufacturer);
    setComment(comment);
    this->quantity = quantity;
    this->expirationDate = expirationDate;
    this->stockedDate = stockedDate;
    this->placement = placement;
}


/// Copy constructor
/// \param other product to copy
Product::Product(Product const& other) {
    setName(other.name);
    setManufacturer(other.manufacturer);
    setComment(other.comment);
    this->quantity = other.quantity;
    this->expirationDate = other.expirationDate;
    this->stockedDate = other.stockedDate;
    this->placement = other.placement;
}


/// Copy assignment operator
/// \param other product to copy
/// \return the updated product
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


/// Destructor
Product::~Product() {
    if (name != nullptr) {
        delete[] name;
        name = nullptr;
    }
    if (manufacturer != nullptr) {
        delete[] manufacturer;
        manufacturer = nullptr;
    }
    if (comment != nullptr) { 
        delete[] comment;
        comment = nullptr;
    }
    quantity = 0;
    placement = Placement();
}


/// Setter for name
/// \param _name name to set
void Product::setName(char const* _name) {
    if (_name == nullptr) { return; }
    delete[] name;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}


/// Setter for manufacturer
/// \param _manufacturer manufacturer to set
void Product::setManufacturer(char const* _manufacturer) {
    if (_manufacturer == nullptr) { return; }
    delete[] manufacturer;
    manufacturer = new char[strlen(_manufacturer) + 1];
    strcpy(manufacturer, _manufacturer);
}


/// Setter for comment
/// \param _comment comment to set
void Product::setComment(char const* _comment) {
    if (_comment == nullptr) { return; }
    delete[] comment;
    comment = new char[strlen(_comment) + 1];
    strcpy(comment, _comment);
}


/// Setter for quantity
/// \param _quantity quantity to set
void Product::setQuantity(int _quantity) {
    quantity = _quantity;
}


/// Setter for expiration date
/// \param _expirationDate expiration date to set
void Product::setExpirationDate(Date const& _expirationDate) {
    expirationDate = _expirationDate;
}


/// Setter for stocked date
/// \param _stockedDate stocked date to set
void Product::setStockedDate(Date const& _stockedDate) {
    stockedDate = _stockedDate;
}


/// Setter for placement
/// \param _placement placement to set
void Product::setPlacement(Placement const& _placement) {
    placement = _placement;
}


/// Setter for index
/// \param _index index to set
void Product::setIndex(int _index) {
    placement.index = _index;
}


/// Setter for shelf
/// \param _shelf shelf to set
void Product::setShelf(int _shelf) {
    placement.shelf = _shelf;
}


/// Setter for section
/// \param _section section to set
void Product::setSection(int _section) {
    placement.section = _section;
}


/// Compare products with equality operator
/// \param other product to compare the current product to
/// \return if the current product has the same name and expiration date as the other
bool Product::operator==(Product const& other) const {
    if (hasSameName(other) && (expirationDate == other.expirationDate)) {
        return true;
    }
    return false;
}


/// Compare products with greater than operator
/// \param other product to compare the current product to
/// \return if the current product has the same name and latter expiration date than the other
bool Product::operator>(Product const& other) const {
    if (hasSameName(other) && (expirationDate > other.expirationDate)) {
        return true;
    }
    return false;
}


/// Compare products with less than operator
/// \param other product to compare the current product to
/// \return if the current product has the same name and prior expiration date than the other
bool Product::operator<(Product const& other) const {
    if (hasSameName(other) && (expirationDate < other.expirationDate)) {
        return true;
    }
    return false;
}


/// Compare product names
/// \param other product to compare names to
/// \return if the current product's name is the same as the other's name
bool Product::hasSameName(Product const& other) const {
    if (strcmp(name, other.name) == 0) {
        return true;
    }
    return false;
}


/// Getter for name
/// \return the name of the product
char const* Product::getName() const {
    return name;
}


/// Getter for manufacturer
/// \return the name of the product manufacturer
char const* Product::getManufacturer() const {
    return manufacturer;
}


/// Getter for comment
/// \return the comment of the product
char const* Product::getComment() const {
    return comment;
}


/// Getter for quantity
/// \return the quantity of the product
int Product::getQuantity() const {
    return quantity;
}


/// Getter for expiration date
/// \return the expiration date of the product
Date Product::getExpirationDate() const {
    return expirationDate;
}


/// Getter for stocked date
/// \return the stocked date of the product
Date Product::getStockedDate() const {
    return stockedDate;
}


/// Getter for placement
/// \return the placement of the product
Placement Product::getPlacement() const {
    return placement;
}


/// Getter for index
/// \return the index the product is at
int Product::getIndex() const {
    return placement.index;
}


/// Getter for shelf
/// \return the shelf the product is on
int Product::getShelf() const {
    return placement.shelf;
}


/// Getter for section
/// \return the section the product is in
int Product::getSection() const {
    return placement.section;
}


/// Stream insertion operator
/// \param out output stream
/// \param p product to output
/// \return the stream with product inserted
std::ostream& operator<<(std::ostream& out, Product const& p) {
    out << "NAME: "
        << p.getName() << "\nDETAILS:\nCOUNT: "
        << p.getQuantity() << "\nMANUFACTURER: "
        << p.getManufacturer() << "\nINDEX: "
        << p.getPlacement().index << " SHELF: "
        << p.getPlacement().shelf << " SECTION: "
        << p.getPlacement().section << "\nEXP: "
        << p.getExpirationDate() << " STOCK: "
        << p.getStockedDate() << "\nNOTES: "
        << p.getComment();
    return out;
}
 