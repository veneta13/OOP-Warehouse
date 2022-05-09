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
        if (products != nullptr) { delete[] products; }
        capacity = other.capacity;
        products = new Product[other.capacity];
        copyProducts(other.products);
    }
    return *this;
}


Shelf::~Shelf() {
    capacity = 0;
    if (products != nullptr) { delete[] products; }
    products = nullptr;
}


void Shelf::copyProducts(Product* others) {
    for (int i = 0; i < capacity; i++) {
        if (others[i].getQuantity() != 0) {
            products[i] = others[i];
        }
    }
} 


Product& Shelf::operator[](int index) {
    return products[index];
}


Product* Shelf::findEqual(char const* name, Date date) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if ((strcmp(products[i].getName(), name) == 0) && products[i].getExpirationDate() == date) {
            return &products[i];
        }
    }
    return nullptr;
}


Product* Shelf::findByName(char const* name) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (products[i].getQuantity() != 0 && strcmp(products[i].getName(), name) == 0) {
            return &products[i];
        }
    }
    return nullptr;
}


void Shelf::findAllByName(const char* name, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (products[i].getQuantity() != 0 && strcmp(products[i].getName(), name) == 0) {
            results.push(&products[i]);
        }
    }
}


void Shelf::findAllByDate(Date const& date, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (products[i].getQuantity() != 0 && products[i].getExpirationDate() <= date) {
            results.push(&products[i]);
        }
    }
}


bool Shelf::addProduct(Product const& product, int index, bool replace) {
    if (index < 0 || index > capacity - 1) { return false; }
    if (!replace && products[index].getQuantity() != 0) { return false; }

    products[index] = product;
    return true;
}


Placement Shelf::addProduct(Product const& product) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() != 0) { continue; }
        products[i] = product;
        return Placement({0, 0, i});
    }
    return Placement();
}


void Shelf::removeProduct(int index) {
    products[index].setQuantity(0);
}
