#include "date_indexer.hpp"

DateIndexer::DateIndexer() : Container(5) {
    date = Date();
    productCount = 0;
    products = new Product*[capacity];
}


DateIndexer::DateIndexer(Date const& _date) : Container(5) {
    date = _date;
    productCount = 0;
    products = new Product*[capacity];
}


DateIndexer::DateIndexer(DateIndexer const& other) : Container(other.capacity) {
    date = other.date;
    productCount = 0;
    products = new Product*[capacity];
}


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


DateIndexer::~DateIndexer() {
    for (int i = 0; i < productCount; i++) {
        delete products[i];
        products[i] = nullptr;
    }
    delete[] products;
    products = nullptr;
    productCount = 0;
}


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


void DateIndexer::setDate(Date const& _date) {
    date = _date;
}


void DateIndexer::addProduct(Product* product) {
    if (productCount == capacity) {
        resize();
    }
    products[productCount] = product;
    productCount++;
}


Date& DateIndexer::getDate() {
    return date;
}


Product** DateIndexer::getProduct(int index) const {
    if (index < 0 || index > productCount - 1) {
        return nullptr;
    }
    return &products[index];
}


int DateIndexer::size() const {
    return productCount;
}
