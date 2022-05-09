#include "shelf.hpp"

Shelf::Shelf() : Container(0) {
    products = nullptr;
}


Shelf::Shelf(int capacity) : Container(capacity) {
    products = new Product[capacity];
}


Shelf::Shelf(Shelf const& other) : Container(other.capacity) {
    products = new Product[other.capacity];
    copyProducts(other.products);
}


Shelf& Shelf::operator=(Shelf const& other) {
    if (this != &other) {
        delete[] products;
        capacity = other.capacity;
        products = new Product[capacity];
        copyProducts(other.products);
    }
    return *this;
}


Shelf::~Shelf() {
    capacity = 0;
    delete[] products;
    products = nullptr;
}


void Shelf::copyProducts(Product* others) {
    for (int i = 0; i < capacity; i++) {
        products[i] = others[i];
    } 
}


Product& Shelf::operator[](int index) const {
    return products[index];
}


Product& Shelf::at(int index) const {
    return products[index];
}


Product* Shelf::findEqual(char const* name, Date date) {
    for (int i = 0; i < capacity; i++) {
        if ((strcmp(products[i].getName(), name) == 0) && products[i].getExpirationDate() == date) {
            return &products[i];
        }
    }
    return nullptr;
}


Product* Shelf::findByName(char const* name) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getName() != nullptr && strcmp(products[i].getName(), name) == 0) {
            return &products[i];
        }
    }
    return nullptr;
}


void Shelf::findAllByName(const char* name, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getName() != nullptr && strcmp(products[i].getName(), name) == 0) {
            results.push(&products[i]);
        }
    }
}


void Shelf::findAllByDate(Date date, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() != 0 && products[i].getExpirationDate() <= date) {
            results.push(&products[i]);
        }
    }
}


bool Shelf::addProduct(Product product, int index) {
    if (index < 0 || index > capacity - 1) { return false; }
    if (products[index].getQuantity() != 0) { return false; }
    products[index] = product;
    return true;
}


Placement Shelf::addProduct(Product product) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() != 0) { continue; }
        products[i] = product;
        return Placement({0, 0, i});
    }
    return Placement();
}


void Shelf::removeProduct(int index) {
    delete &products[index];
    products[index] = Product();
}
