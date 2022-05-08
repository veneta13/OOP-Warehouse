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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


Product& Shelf::operator[](int index) const {
    return products[index];
}


Product& Shelf::at(int index) const {
    return products[index];
}


bool Shelf::addProduct(Product product, int index) {
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


int Shelf::countProduct(char const* name) {
    int counter = 0;
    for (int i = 0; i < capacity; i++) {
        if (strcmp(products[i].getName(), name) == 0) {
            counter += products[i].getQuantity();
        }
    }
    return counter;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


Shelf& Section::operator[](int index) const {
    return shelves[index];
}


Shelf& Section::at(int index) const {
    return shelves[index];
}


Product* Section::findByName(char const* name) {
    Product* found = nullptr;
    for (int i = 0; i < capacity && !found; i++) {
        found = shelves[i].findByName(name);
    }
    return found;
}


void Section::findAllByName(const char* name, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        shelves[i].findAllByName(name, results);
    }
}


void Section::findAllByDate(Date date, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        shelves[i].findAllByDate(date, results);
    }
}


bool Section::addProduct(Product product, int shelfIndex, int index) {
    if (shelves[shelfIndex].addProduct(product, index)) {
        return true;
    }
    return false;
}


Placement Section::addProduct(Product product) {
    for (int i = 0; i < capacity; i++) {
        Placement p = shelves[i].addProduct(product);

        if (p.index != -1) {
            p.shelf = i;
            return p;
        }
    }
    return Placement();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


int Warehouse::sortAndCount(DynArray<Product*> products) {
    int quantitySum = 0;
    for (int i = 0; i < products.size() - 1; i++) 
    { 
        int minIndex = i; 
        for (int j = i + 1; j < products.size(); j++) {
            if (products[j] < products[minIndex]) {
                minIndex = j; 
            }
        }

        Product* temp = products[i];
        products[i] = products[minIndex];
        products[minIndex] = temp;
        quantitySum += products[i]->getQuantity();
    }
    quantitySum += products[products.size()-1]->getQuantity();
    return quantitySum;
}


void Warehouse::printProducts(std::ostream& out, DynArray<Product*>& products) {
    int productCount = sortAndCount(products);

    out << products[0]->getName() << "\nCOUNT: "
        << productCount << "\nDETAILS:\n";

    for (int i = 0; i < products.size(); i++) {
        out << products[i]->getManufacturer() << " \n "
            << products[i]->getPlacement().index << " SHELF "
            << products[i]->getPlacement().shelf << " SECTION "
            << products[i]->getPlacement().section << "\n EXP:"
            << products[i]->getExpirationDate().day << "/"
            << products[i]->getExpirationDate().month << "/"
            << products[i]->getExpirationDate().year << " STOCK:"
            << products[i]->getStockedDate().day << "/"
            << products[i]->getStockedDate().month << "/"
            << products[i]->getStockedDate().year << "\nNOTES:"
            << products[i]->getComment() << "\n";
    }
}

void Warehouse::findAllByName(const char* name, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        sections[i].findAllByName(name, results);
    }
}


void Warehouse::findAllByDate(Date date, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        sections[i].findAllByDate(date, results);
    }
}


bool Warehouse::addProduct(Product product, int sectionIndex, int shelfIndex, int index) {
    if (sections[sectionIndex].addProduct(product, shelfIndex, index)) {
        sections[sectionIndex][shelfIndex][index].setPlacement(Placement{sectionIndex, shelfIndex, index});
        return true;
    }
    return false;
}


bool Warehouse::addProduct(Product product) {
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


void Warehouse::operator<<(std::ostream& out) {
    DynArray<const char*> listed(10);

    for (int i = 0; i < capacity; i++) { // section counter
        for (int j = 0; j < sections[i].getCapacity(); j++) { // shelf counter
            for (int k = 0; k < sections[i][j].getCapacity(); k++) { // index counter
                bool visited = false;
                
                for (int l = 0; l < listed.size(); l++) {
                    if (strcmp(listed[l], sections[i][j][k].getName()) == 0){
                        visited = true;
                        break;
                    }
                }

                if (!visited) {
                    listed.push(sections[i][j][k].getName());
                    DynArray<Product*> products(10);
                    findAllByName(sections[i][j][k].getName(), products);
                    printProducts(out, products);
                }
            }
        }
    }
}

