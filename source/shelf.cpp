#include "shelf.hpp"

/// Default constructor
Shelf::Shelf() : Container(0) {
    products = nullptr;
}


/// Constructor with capacity parameter
/// \param capacity amount of products on shelf
Shelf::Shelf(int capacity) : Container(capacity) {
    products = new Product[capacity];
}


/// Copy constructor
/// \param other shelf to copy
Shelf::Shelf(Shelf const& other) : Container(other.capacity) {
    products = new Product[other.capacity];
    copyProducts(other.products);
}


/// Copy assignment operator
/// \param other shelf to copy
/// \return the updated shelf
Shelf& Shelf::operator=(Shelf const& other) {
    if (this != &other) {
        delete[] products;
        capacity = other.capacity;
        products = new Product[other.capacity];
        copyProducts(other.products);
    }
    return *this;
}


/// Destructor
Shelf::~Shelf() {
    capacity = 0;
    delete[] products;
    products = nullptr;
}


/// Copy products
/// \param others products to copy
void Shelf::copyProducts(Product* others) {
    for (int i = 0; i < capacity; i++) {
        if (others[i].getQuantity() != 0) {
            products[i] = others[i];
        }
    }
}


/// Getter for products
/// \param index index of the product
/// \return the product at index
Product& Shelf::operator[](int index) {
    return products[index];
}


/// Find product by name and expiration date
/// \param name name to search for
/// \param date expiration date to search for
/// \return pointer to the product
Product* Shelf::findEqual(char const* name, Date const& date) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if ((strcmp(products[i].getName(), name) == 0) && products[i].getExpirationDate() == date) {
            return &products[i];
        }
    }
    return nullptr;
}


/// Find product by name
/// \param name name to search for
/// \return pointer to the product
Product* Shelf::findByName(char const* name) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (strcmp(products[i].getName(), name) == 0) {
            return &products[i];
        }
    }
    return nullptr;
}


/// Find all products with name
/// \param name name to search for
/// \param results dynamic size array to save found products in
void Shelf::findAllByName(const char* name, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (strcmp(products[i].getName(), name) == 0) {
            results.push(&products[i]);
        }
    }
}


/// Find all products by expiration date
/// \param date expiration date to search for
/// \param results dynamic size array to save found products in
void Shelf::findAllExpiredByDate(Date const& date, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (products[i].getExpirationDate() <= date) {
            results.push(&products[i]);
        }
    }
}


/// Find all products stocked between dates
/// \param from beginning of date interval
/// \param to end of date interval
/// \param results dynamic size array to save found products in
void Shelf::findAllStockedBetweenDates(Date const& from, Date const& to, DynArray<Product *> &results) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (products[i].getStockedDate() >= from && products[i].getStockedDate() <= to) {
            results.push(&products[i]);
        }
    }
}


/// Add product at a set position
/// \param product product to add
/// \param index index to add at
/// \param replace if existing product should be replaced
/// \return if the product was added successfully
bool Shelf::addProduct(Product const& product, int index, bool replace) {
    if (index < 0 || index > capacity - 1) { return false; }
    if (!replace && products[index].getQuantity() != 0) { return false; }

    products[index] = product;
    return true;
}


/// Add product somewhere on shelf
/// \param product product to add
/// \return placement of the product in the section (default placement if unsuccessful)
Placement Shelf::addProduct(Product const& product) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() != 0) { continue; }
        products[i] = product;
        return Placement({0, 0, i});
    }
    return Placement();
}


/// Remove product from a set position
/// \param index index of the product to remove
/// \param quantity quantity to remove
/// \return placement of the product in the section (default placement if unsuccessful)
Product* Shelf::removeProduct(int index, int quantity) {
    if (index > capacity - 1 || index < 0) {
        return nullptr;
    }
    if (quantity > products[index].getQuantity()) {
        return nullptr;
    }
    quantity = quantity == -1 ? products[index].getQuantity() : quantity;

    Product* copy = new Product(products[index]);
    copy->setQuantity(quantity);
    products[index].setQuantity(products[index].getQuantity() - quantity);
    return copy;
}


/// Stream insertion operator
/// \param out output stream
/// \param s shelf to output
/// \return the stream with products inserted
std::ostream& operator<<(std::ostream& out, Shelf const& s) {
    for (int i = 0; i < s.capacity; i++) {
        if (s.products[i].getQuantity() == 0) { continue; }
        out << s.products[i] << "\n";
    }
    return out;
}
