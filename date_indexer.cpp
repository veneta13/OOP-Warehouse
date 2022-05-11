#include "date_indexer.hpp"

DateIndexer::DateIndexer() : Container(5) {
    date = Date();
    productCount = 0;
    products = new Product[capacity];
}


DateIndexer::DateIndexer(Date const& _date) : Container(5) {
    date = _date;
    productCount = 0;
    products = new Product[capacity];
}


DateIndexer::DateIndexer(DateIndexer const& other) : Container(other.capacity) {
    productCount = other.productCount;
    products = new Product[capacity];
    copyProducts(other.products);
}


DateIndexer& DateIndexer::operator=(DateIndexer const& other) {
    if (this != &other) {
        delete[] products;
        capacity = other.capacity;
        products = new Product[capacity];
        copyProducts(other.products);
    }
    return *this;
}


DateIndexer::~DateIndexer() {
    delete[] products;
    products = nullptr;
    productCount = 0;
}


void DateIndexer::copyProducts(Product* others) {
    for (int i = 0; i < productCount; i++) {
        products[i] = others[i];
    }
}


void DateIndexer::resize() {
    capacity *= 2;
    Product* newProducts = new Product[capacity];

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


void DateIndexer::addProduct(Product const& product) {
    if (productCount == capacity) {
        resize();
    }
    products[productCount] = product;
    productCount++;
}


Date& DateIndexer::getDate() {
    return date;
}


Product* DateIndexer::getProduct(int index) const {
    if (index < 0 || index > productCount - 1) {
        return nullptr;
    }
    return &products[index];
}


int DateIndexer::size() const {
    return productCount;
}
