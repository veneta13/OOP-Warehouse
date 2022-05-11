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
        products = new Product[other.capacity];
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
        if (others[i].getQuantity() != 0) {
            products[i] = others[i];
        }
    }
} 


Product& Shelf::operator[](int index) {
    return products[index];
}


Product* Shelf::findEqual(char const* name, Date const& date) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if ((strcmp(products[i].getName(), name) == 0) && products[i].getExpirationDate() == date) {
            return &products[i];
        }
    }
    return nullptr;
}


Product* Shelf::findByName(char const* name) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (strcmp(products[i].getName(), name) == 0) {
            return &products[i];
        }
    }
    return nullptr;
}


void Shelf::findAllByName(const char* name, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (strcmp(products[i].getName(), name) == 0) {
            results.push(&products[i]);
        }
    }
}


void Shelf::findAllExpiredByDate(Date const& date, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (products[i].getExpirationDate() <= date) {
            results.push(&products[i]);
        }
    }
}


void Shelf::findAllStockedBetweenDates(Date const& from, Date const& to, DynArray<Product *> &results) const {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() == 0) { continue; }
        if (products[i].getStockedDate() >= from && products[i].getStockedDate() <= to) {
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

///
/// \param index the index of the product we want to remove
/// \param quantity the amount we want to removes1.findEqual(dummyName1, dummyDate1)
/// \return the removed product (if the removal is unsuccessful -> nullptr)
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

std::ostream& operator<<(std::ostream& out, Shelf const& s) {
    for (int i = 0; i < s.capacity; i++) {
        if (s.products[i].getQuantity() == 0) { continue; }
        out << s.products[i] << "\n";
    }
    return out;
}
