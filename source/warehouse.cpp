#include "warehouse.hpp"

/// Default constructor
Warehouse::Warehouse() : Container(0) {
    today = Date();
    tracker = new Tracker;
    sections = nullptr;
}


/// Constructor with capacity parameter
/// \param capacity amount of shelves in section
Warehouse::Warehouse(int capacity) : Container(capacity) {
    today = Date();
    tracker = new Tracker;
    sections = new Section[capacity];
}


/// Copy constructor
/// \param other warehouse to copy
Warehouse::Warehouse(Warehouse const& other) : Container(other.capacity) {
    tracker = nullptr;
    today = other.today;
    sections = new Section[other.capacity];
    tracker = new Tracker;
    copySections(other.sections);
}


/// Copy assignment operator
/// \param other warehouse to copy
/// \return the updated warehouse
Warehouse& Warehouse::operator=(Warehouse const& other) {
    if (this != &other) {
        delete tracker;
        delete[] sections;
        today = other.today;
        capacity = other.capacity;
        tracker = new Tracker;
        sections = new Section[capacity];
        copySections(other.sections);
    }
    return *this;
}


/// Destructor
Warehouse::~Warehouse() {
    capacity = 0;
    delete tracker;
    delete[] sections;
    sections = nullptr;
}


/// Copy sections
/// \param others sections to copy
void Warehouse::copySections(Section* others) {
    for (int i = 0; i < capacity; i++) {
        sections[i] = others[i];
    } 
}


/// Print products
/// \param out output stream
/// \param products products to output
void Warehouse::printProducts(std::ostream& out, DynArray<Product*>& products) const {
    for (int i = 0; i < products.size(); i++) {
        out << *products[i] << "\n";
    }
}


/// Sort products by expiration date and count amount
/// \param products products to sort and count
/// \return sum of the quantities of the products
int Warehouse::sortAndCount(DynArray<Product*> products) const {
    if (products.size() == 0) {
        return 0;
    }

    int quantitySum = 0;
    for (int i = 0; i < products.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < products.size(); j++) {
            if (products[j] < products[minIndex]) {
                minIndex = j; 
            }
        }
        products.swap(i, minIndex);
        quantitySum += products[i]->getQuantity();
    }
    quantitySum += products[products.size()-1]->getQuantity();
    return quantitySum;
}


/// Output prompt if the user wants to remove more than the available quantity of a product
/// \param out output stream to write the prompt in
/// \param in input stream to read user input from
/// \param productCount available quantity
/// \param products available products
/// \return if the available products should be kept
bool Warehouse::insufficientQuantity(std::ostream& out, std::istream& in, int productCount,
                                     DynArray<Product*>& products) const {
    char response;
    out << "! Only " << productCount << " products available:\n";
    printProducts(out, products);
    out << "\nDo you want to remove anyway? y/n\n";
    in >> response;
    if (response == 'y') {
        return false;
    }
    return true;
}


/// Getter for sections
/// \param index index of the section
/// \return the section at index
Section& Warehouse::operator[](int index) {
    return sections[index];
}


/// Setter for today
/// \param date date to set
void Warehouse::setToday(const Date &date) {
    today = date;
}


/// Getter for today
/// \return today's date
Date* Warehouse::getToday() {
    return &today;
}


/// Setter for section capacity
/// \param index index of the section
/// \param sectionCapacity capacity to set
/// \return if the setting was successful
bool Warehouse::setSectionCapacity(int index, int sectionCapacity) {
    if (index < 0 || index > capacity - 1) { return false; }
    sections[index] = Section(sectionCapacity);
    return true;
}


/// Find product by name and expiration date
/// \param name name to search for
/// \param date expiration date to search for
/// \return pointer to the product
Product* Warehouse::findEqual(char const* name, Date const& date) {
    Product* found = nullptr;
    for (int i = 0; i < capacity && !found; i++) {
        found = sections[i].findEqual(name, date);
    }
    return found;
}


/// Find all products with name
/// \param name name to search for
/// \param results dynamic size array to save found products in
void Warehouse::findAllByName(const char* name, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        sections[i].findAllByName(name, results);
    }
}


/// Find all products by expiration date
/// \param date expiration date to search for
/// \param results dynamic size array to save found products in
void Warehouse::findAllExpiredByDate(Date const& date, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        sections[i].findAllExpiredByDate(date, results);
    }
}


/// Find all products stocked between dates
/// \param from beginning of date interval
/// \param to end of date interval
/// \param results dynamic size array to save found products in
void Warehouse::findAllStockedBetweenDates(Date const& from, Date const& to, DynArray<Product*> &results) const {
    for (int i = 0; i < capacity; i++) {
        sections[i].findAllStockedBetweenDates(from, to, results);
    }
}


/// Add product somewhere in warehouse
/// \param product product to add
/// \return if placement is successful
bool Warehouse::addProduct(Product const& product) {
    for (int i = 0; i < capacity; i++) {
        Placement p = sections[i].addProduct(product);

        if (p.shelf != -1) {
            p.section = i;
            sections[p.section][p.shelf][p.index].setPlacement(p);
            return true;
        }
    }
    return false;
}


/// Remove product from a set position
/// \param sectionIndex index of section to remove from
/// \param shelfIndex index of shelf to remove from
/// \param index index of the product to remove
/// \param quantity quantity to remove
/// \return the removed product (nullptr if unsuccessful)
Product* Warehouse::removeProduct(int sectionIndex, int shelfIndex, int index, int quantity) {
    if (sectionIndex > capacity - 1 || sectionIndex < 0) {
        return nullptr;
    }

    return sections[sectionIndex].removeProduct(shelfIndex, index, quantity);
}


/// Take out product from warehouse
/// \param out output stream to write the prompt in
/// \param in input stream to read user input from
/// \param name name of product
/// \param wanted quantity to take out
/// \return if product was taken out successfully
bool Warehouse::takeOutProduct(std::ostream& out, std::istream& in, char const* name, int wanted) {
    DynArray<Product*> products(10);
    findAllByName(name, products);
    int productCount = sortAndCount(products);

    if (productCount < wanted && insufficientQuantity(out, in, productCount, products)) {
        return false;
    }

    for (int i = 0; i < products.size() && wanted > 0; i++) {
        Placement p = products[i]->getPlacement();
        int currentQuantity = products[i]->getQuantity();

        if (wanted >= currentQuantity) {
            tracker->addRemoved(removeProduct(p.section, p.shelf, p.index, -1), today);
            wanted -= currentQuantity;
        }
        else {
            tracker->addRemoved(removeProduct(p.section, p.shelf, p.index, wanted), today);
            wanted = 0;
        }
    }
    
    return true;
}


/// Add product at a set position
/// \param product product to add
/// \param sectionIndex section to add in
/// \param shelfIndex shelf to add on
/// \param index index to add at
/// \return if the product was added successfully
bool Warehouse::addProduct(Product const& product, int sectionIndex, int shelfIndex, int index) {
    if (sectionIndex < 0 || sectionIndex > capacity - 1) { return false; }
    if (sections[sectionIndex].addProduct(product, shelfIndex, index)) {
        sections[sectionIndex][shelfIndex][index].setPlacement(Placement{sectionIndex, shelfIndex, index});
        return true;
    }
    return false;
}


/// Add product in warehouse as close to a similar product as possible
/// \param product product to add
/// \return if the product was added successfully
bool Warehouse::restock(Product const& product) {
    Product* found = findEqual(product.getName(), product.getExpirationDate());

    if (found) {
        Placement pNew, p = found->getPlacement();

        // Place next to item on the shelf
        if (addProduct(product, p.section, p.shelf, p.index - 1)) {
            return true;
        }
        if (addProduct(product, p.section, p.shelf, p.index + 1)) {
            return true;
        }

        // Place on the same shelf
        pNew = sections[p.section, p.shelf].addProduct(product);
        if (pNew.index != -1) {
            sections[pNew.section][pNew.shelf][pNew.index].setPlacement(pNew);
            return true;
        }

        // Place on close by shelves in the same section
        pNew = sections[p.section, p.shelf + 1].addProduct(product);
        if (pNew.index != -1) {
            sections[pNew.section][pNew.shelf][pNew.index].setPlacement(pNew);
            return true;
        }
        pNew = sections[p.section, p.shelf - 1].addProduct(product);
        if (pNew.index != -1) {
            sections[pNew.section][pNew.shelf][pNew.index].setPlacement(pNew);
            return true;
        }

        // Place in close by sections
        pNew = sections[p.section + 1].addProduct(product);
        if (pNew.index != -1) {
            sections[pNew.section][pNew.shelf][pNew.index].setPlacement(pNew);
            return true;
        }
        pNew = sections[p.section - 1].addProduct(product);
        if (pNew.index != -1) {
            sections[pNew.section][pNew.shelf][pNew.index].setPlacement(pNew);
            return true;
        }
    }
    
    return addProduct(product);
}


/// Cleanup expired and expiring products
/// \param file filestream to save product information in
/// \param date current date
void Warehouse::cleanup(std::ostream& file, Date const& date) {
    DynArray<Product*> products(10);
    findAllExpiredByDate(date, products);
    printProducts(file, products);

    for (int i = 0; i < products.size(); i++) {
        Placement place = products[i]->getPlacement();
        tracker->addRemoved(removeProduct(place.section, place.shelf, place.index, -1), date);
    }
}


/// Stream insertion operator
/// \param out output stream
/// \param w warehouse to output
/// \return the stream with products inserted
std::ostream& operator<<(std::ostream& out, Warehouse const& w) {
    DynArray<Product *> listed(10);

    for (int i = 0; i < w.capacity; i++) { // section counter
        for (int j = 0; j < w.sections[i].getCapacity(); j++) { // shelf counter
            for (int k = 0; k < w.sections[i][j].getCapacity(); k++) { // index counter
                if (w.sections[i][j][k].getQuantity() == 0) { continue; }

                bool visited = false;

                for (int l = 0; l < listed.size() && !visited; l++) {
                    if (w.sections[i][j][k].hasSameName(*listed[l])){
                        visited = true;
                    }
                }

                if (!visited) {
                    listed.push(&w.sections[i][j][k]);

                    DynArray<Product*> products(10);
                    w.findAllByName(w.sections[i][j][k].getName(), products);
                    int count = w.sortAndCount(products);

                    w.printProducts(out, products);
                    out << "---------- COUNT: " << count << "\n\n";
                }
            }
        }
    }

    return out;
}


/// List all products stocked and taken out in a date interval
/// \param out output stream
/// \param from beginning of date interval
/// \param to end of date interval
void Warehouse::makeQuery(std::ostream& out, Date const& from, Date const& to) {
    DynArray<Product *> stocked(5);
    DynArray<Product *> removed(5);
    tracker->searchInInterval(from, to , stocked, removed);
    findAllExpiredByDate(to, removed);
    findAllStockedBetweenDates(from, to, stocked);

    out << "STOCKED BETWEEN " << from << " AND " << to << "\n";
    printProducts(out, stocked);

    out << "\nREMOVED BETWEEN " << from << " AND " << to << "\n";
    printProducts(out, removed);
}
