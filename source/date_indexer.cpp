#include "date_indexer.hpp"

/// Default constructor
DateIndexer::DateIndexer() : Container(5) {
    date = Date();
    productCount = 0;
    products = new Product*[capacity];
}


/// Constructor with date parameter
/// \param _date date to be set as index date
DateIndexer::DateIndexer(Date const& _date) : Container(5) {
    date = _date;
    productCount = 0;
    products = new Product*[capacity];
}


/// Copy constructor (does NOT copy the products)
/// \param other date indexer to copy
DateIndexer::DateIndexer(DateIndexer const& other) : Container(other.capacity) {
    date = other.date;
    productCount = 0;
    products = new Product*[capacity];
}


/// Copy assignment operator
/// \param other date indexer to copy
/// \return the updated date indexer
DateIndexer& DateIndexer::operator=(DateIndexer const& other) {
    if (this != &other) {
        delete[] products;
        date = other.date;
        capacity = other.capacity;
        productCount = 0;
        products = new Product*[capacity];
    }
    return *this;
}


/// Destructor
DateIndexer::~DateIndexer() {
    for (int i = 0; i < productCount; i++) {
        delete products[i];
        products[i] = nullptr;
    }
    delete[] products;
    products = nullptr;
    productCount = 0;
}


/// Double the capacity of the date indexer
void DateIndexer::resize() {
    capacity *= 2;
    Product** newProducts = new Product*[capacity];

    for (int i = 0; i < productCount; i++) {
        newProducts[i] = products[i];
    }

    delete[] products;
    products = newProducts;
    newProducts = nullptr;
}


/// Setter for date
/// \param _date date to set
void DateIndexer::setDate(Date const& _date) {
    date = _date;
}


/// Add product to date indexer
/// \param product product to add
void DateIndexer::addProduct(Product* product) {
    if (!product) { return; }
    if (productCount == capacity) {
        resize();
    }
    products[productCount] = product;
    productCount++;
}


/// Getter for date
/// \return the date indexer's date
Date& DateIndexer::getDate() {
    return date;
}


/// Getter for products
/// \param index index of the product to get
/// \return the product at index
Product* DateIndexer::getProduct(int index) const {
    if (index < 0 || index > productCount - 1) {
        return nullptr;
    }
    return products[index];
}


/// Getter for product count
/// \return the amount of products saved in the indexer
int DateIndexer::size() const {
    return productCount;
}
