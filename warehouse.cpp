#include "warehouse.hpp"

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


void Warehouse::printProducts(std::ostream& out, DynArray<Product*>& products) const {
    for (int i = 0; i < products.size(); i++) {
        out << *products[i] << "\n";
    }
}


int Warehouse::sortAndCount(DynArray<Product*> products) const {
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

Section& Warehouse::operator[](int index) {
    return sections[index];
}


bool Warehouse::setSectionCapacity(int index, int sectionCapacity) {
    if (index < 0 || index > capacity - 1) { return false; }
    sections[index] = Section(sectionCapacity);
    return true;
}


Product* Warehouse::findEqual(char const* name, Date const& date) {
    Product* found = nullptr;
    for (int i = 0; i < capacity && !found; i++) {
        found = sections[i].findEqual(name, date);
    }
    return found;
}


void Warehouse::findAllByName(const char* name, DynArray<Product*>& results) const {
    for (int i = 0; i < capacity; i++) {
        sections[i].findAllByName(name, results);
    }
}


void Warehouse::findAllByDate(Date const& date, DynArray<Product*>& results) {
    for (int i = 0; i < capacity; i++) {
        sections[i].findAllByDate(date, results);
    }
}


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


void Warehouse::removeProduct(int sectionIndex,int shelfIndex, int index) {
    sections[sectionIndex].removeProduct(shelfIndex, index);
}


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
            removeProduct(p.section, p.shelf, p.index);
            wanted -= currentQuantity;
        }
        else {
            sections[p.section][p.shelf][p.index].setQuantity(currentQuantity - wanted);
            wanted = 0;
        }
    }
    
    return true;
}


bool Warehouse::addProduct(Product const& product, int sectionIndex, int shelfIndex, int index) {
    if (sectionIndex < 0 || sectionIndex > capacity - 1) { return false; }
    if (sections[sectionIndex].addProduct(product, shelfIndex, index)) {
        sections[sectionIndex][shelfIndex][index].setPlacement(Placement{sectionIndex, shelfIndex, index});
        return true;
    }
    return false;
}


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


void Warehouse::cleanup(std::ostream& file, Date const& date) {
    DynArray<Product*> products(10);
    findAllByDate(date, products);
    printProducts(file, products);
}


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
                    out << "\n----- COUNT: " << count << "\n";
                }
            }
        }
    }

    return out;
}
