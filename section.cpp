#include "section.hpp"

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


Shelf& Section::operator[](int index) {
    return shelves[index];
}


bool Section::setShelfCapacity(int index, int shelfCapacity) {
    if (index < 0 || index > capacity - 1) { return false; }
    shelves[index] = Shelf(shelfCapacity);
    return true;
}


Product* Section::findEqual(char const* name, Date const& date) const {
    Product* found = nullptr;
    for (int i = 0; i < capacity && !found; i++) {
        found = shelves[i].findEqual(name, date);
    }
    return found;
}


Product* Section::findByName(char const* name) const {
    Product* found = nullptr;
    for (int i = 0; i < capacity && !found; i++) {
        found = shelves[i].findByName(name);
    }
    return found;
}


void Section::findAllByName(const char* name, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        shelves[i].findAllByName(name, results);
    }
}


void Section::findAllByDate(Date const& date, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        shelves[i].findAllByDate(date, results);
    }
}


bool Section::addProduct(Product const& product, int shelfIndex, int index) {
    if (shelfIndex < 0 || shelfIndex > capacity - 1) { return false; }
    return shelves[shelfIndex].addProduct(product, index);
}


Placement Section::addProduct(Product const& product) {
    for (int i = 0; i < capacity; i++) {
        Placement p = shelves[i].addProduct(product);

        if (p.index != -1) {
            p.shelf = i;
            return p;
        }
    }
    return Placement();
}

///
/// \param shelfIndex the shelf we want to remove the project from
/// \param index the index of the product we want to remove
/// \param quantity the quantity to remove
/// \return the removed product (if the removal is unsuccessful -> nullptr)
Product* Section::removeProduct(int shelfIndex, int index, int quantity) {
    if (shelfIndex > capacity - 1 || shelfIndex < 0) {
        return nullptr;
    }

    return shelves[shelfIndex].removeProduct(index, quantity);
}


std::ostream& operator<<(std::ostream& out, Section const& s) {
    for (int i = 0; i < s.capacity; i++) {
        out << s.shelves[i];
    }
    return out;
}
