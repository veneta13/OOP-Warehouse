#include "section.hpp"

/// Default constructor
Section::Section() : Container(0) {
    shelves = nullptr;
}


/// Constructor with capacity parameter
/// \param capacity amount of shelves in section
Section::Section(int capacity) : Container(capacity) {
    shelves = new Shelf[capacity];
}


/// Copy constructor
/// \param other section to copy
Section::Section(Section const& other) : Container(other.capacity) {
    shelves = new Shelf[other.capacity];
    copyShelves(other.shelves);
}


/// Copy assignment operator
/// \param other section to copy
/// \return the updated section
Section& Section::operator=(Section const& other) {
    if (this != &other) {
        delete[] shelves;
        capacity = other.capacity;
        shelves = new Shelf[capacity];
        copyShelves(other.shelves);
    }
    return *this;
}


/// Destructor
Section::~Section() {
    capacity = 0;
    delete[] shelves;
    shelves = nullptr;
}


/// Copy shelves
/// \param others shelves to copy
void Section::copyShelves(Shelf* others) {
    for (int i = 0; i < capacity; i++) {
        shelves[i] = others[i];
    }
}


/// Getter for shelves
/// \param index index of the shelf
/// \return the shelf at index
Shelf& Section::operator[](int index) {
    return shelves[index];
}


/// Setter for shelf capacity
/// \param index index of the shelf
/// \param shelfCapacity capacity to set
/// \return if the setting was successful
bool Section::setShelfCapacity(int index, int shelfCapacity) {
    if (index < 0 || index > capacity - 1) { return false; }
    shelves[index] = Shelf(shelfCapacity);
    return true;
}


/// Find product by name and expiration date
/// \param name name to search for
/// \param date expiration date to search for
/// \return pointer to the product
Product* Section::findEqual(char const* name, Date const& date) const {
    Product* found = nullptr;
    for (int i = 0; i < capacity && !found; i++) {
        found = shelves[i].findEqual(name, date);
    }
    return found;
}


/// Find product by name
/// \param name name to search for
/// \return pointer to the product
Product* Section::findByName(char const* name) const {
    Product* found = nullptr;
    for (int i = 0; i < capacity && !found; i++) {
        found = shelves[i].findByName(name);
    }
    return found;
}


/// Find all products with name
/// \param name name to search for
/// \param results dynamic size array to save found products in
void Section::findAllByName(const char* name, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        shelves[i].findAllByName(name, results);
    }
}


/// Find all products by expiration date
/// \param date expiration date to search for
/// \param results dynamic size array to save found products in
void Section::findAllExpiredByDate(Date const& date, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        shelves[i].findAllExpiredByDate(date, results);
    }
}


/// Find all products stocked between dates
/// \param from beginning of date interval
/// \param to end of date interval
/// \param results dynamic size array to save found products in
void Section::findAllStockedBetweenDates(Date const& from, Date const& to, DynArray<Product*> &results) const {
    for (int i = 0; i < capacity; i++) {
        shelves[i].findAllStockedBetweenDates(from, to, results);
    }
}


/// Add product at a set position
/// \param product product to add
/// \param shelfIndex shelf to add in
/// \param index index to add at
/// \return if the product was added successfully
bool Section::addProduct(Product const& product, int shelfIndex, int index) {
    if (shelfIndex < 0 || shelfIndex > capacity - 1) { return false; }
    return shelves[shelfIndex].addProduct(product, index);
}


/// Add product somewhere in section
/// \param product product to add
/// \return placement of the product in the section (default placement if unsuccessful)
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


/// Remove product from a set position
/// \param shelfIndex index of shelf to remove from
/// \param index index of the product to remove
/// \param quantity quantity to remove
/// \return the removed product (nullptr if unsuccessful)
Product* Section::removeProduct(int shelfIndex, int index, int quantity) {
    if (shelfIndex > capacity - 1 || shelfIndex < 0) {
        return nullptr;
    }

    return shelves[shelfIndex].removeProduct(index, quantity);
}


/// Stream insertion operator
/// \param out output stream
/// \param p section to output
/// \return the stream with products inserted
std::ostream& operator<<(std::ostream& out, Section const& s) {
    for (int i = 0; i < s.capacity; i++) {
        out << s.shelves[i];
    }
    return out;
}
