#include "containers.hpp"

Container::Container() : capacity(0) {}


Container::Container(int capacity) : capacity(capacity) {}


Container::Container(Container const& other) : capacity(other.capacity) {}


Container& Container::operator=(Container const& other) {
    if (this != &other) {
        capacity = other.capacity;
    }
    return *this;
}


Container::~Container() {
    capacity = 0;
}


int Container::getCapacity() const {
    return capacity;
}

//////////////////////////////////////////////////////////////////////////

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


Product* Shelf::findByName(char const* name) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getName() != nullptr && strcmp(products[i].getName(), name) == 0) {
            return &products[i];
        }
    }
}


Product* Shelf::operator[](int index) const {
    return index < capacity ? &products[index] : nullptr;
}


Product* Shelf::at(int index) const {
    return &products[index];
}


int Shelf::addProduct(Product product, int index) {
    if (products[index].getQuantity() != 0) { return -1; }
    product.setIndex(index);
    products[index] = product;
    return index;
}


int Shelf::addProduct(Product product) {
    for (int i = 0; i < capacity; i++) {
        if (products[i].getQuantity() != 0) { continue; }
        products[i] = product;
        products[i].setIndex(i);
        return i;
    }
    return -1;
}


void Shelf::removeProduct(int index) {
    delete &products[index];
    products[index] = Product();
}


int Shelf::countProduct(char const* name) {
    int counter = 0;
    for (int i = 0; i < capacity; i++) {
        if (strcmp(products[i].getName(), name) == 0) {
            counter += products[i].getQuantity();
        }
    }
    return counter;
}

//////////////////////////////////////////////////////////////////////////

Section::Section() : Container(0) {
    shelves = nullptr;
}


Section::Section(int capacity) : Container(capacity) {
    shelves = new Shelf[capacity];
}


Section::Section(Section const& other) : Container(other.capacity) {
    shelves = new Shelf[other.capacity];
    copyShelves(other.shelves);
}


Section& Section::operator=(Section const& other) {
    if (this != &other) {
        delete[] shelves;
        capacity = other.capacity;
        shelves = new Shelf[capacity];
        copyShelves(other.shelves);
    }
    return *this;
}


Section::~Section() {
    capacity = 0;
    delete[] shelves;
    shelves = nullptr;
}


void Section::copyShelves(Shelf* others) {
    for (int i = 0; i < capacity; i++) {
        shelves[i] = others[i];
    } 
}


Shelf* Section::operator[](int index) const {
    return index < capacity ? &shelves[index] : nullptr;
}


void Section::list() {
    for (int i = 0; i < capacity; i++) {
        shelves[i].list();
    }
}

//////////////////////////////////////////////////////////////////////////

Warehouse::Warehouse() : Container(0) {
    sections = nullptr;
}


Warehouse::Warehouse(int capacity) : Container(capacity) {
    sections = new Section[capacity];
}


Warehouse::Warehouse(Warehouse const& other) : Container(other.capacity) {
    sections = new Section[other.capacity];
    copySections(other.sections);
}


Warehouse& Warehouse::operator=(Warehouse const& other) {
    if (this != &other) {
        delete[] sections;
        capacity = other.capacity;
        sections = new Section[capacity];
        copySections(other.sections);
    }
    return *this;
}


Warehouse::~Warehouse() {
    capacity = 0;
    delete[] sections;
    sections = nullptr;
}


void Warehouse::copySections(Section* others) {
    for (int i = 0; i < capacity; i++) {
        sections[i] = others[i];
    } 
}


void Warehouse::list(std::ostream& out) {
    for (int i = 0; i < capacity; i++) {
        sections[i].list();
    }
}

