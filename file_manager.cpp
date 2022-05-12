#include "file_manager.hpp"

FileManager::FileManager() {}


FileManager::FileManager(FileManager const& other) {}


FileManager& FileManager::operator=(FileManager const& other) {
    return *this;
}


FileManager::~FileManager() {}


bool FileManager::readWarehouseParams(std::istream& in, Warehouse& w) {
    int num;
    in >> num;
    if (num < 0) { return false; }

    w = Warehouse(num);

    for (int i = 0; i < w.getCapacity(); i++) {
        in >> num;
        if (num < 0) { return false; }
        w.setSectionCapacity(i, num);
    }

    for (int i = 0; i < w.getCapacity(); i++) {
        for (int j = 0; j < w[i].getCapacity(); j++) {
            in >> num;
            if (num < 0) { return false; }
            w[i].setShelfCapacity(j, num);
        }
    }

    return true;
}


bool FileManager::readWarehouseProducts(std::istream& in, Warehouse& w) {
    bool ok = true;
    while (!in.eof() && ok) {
        ok = readProduct(in, w);
    }
    return ok;
}


bool FileManager::readProduct(std::istream& in, Warehouse& w) {
    Product p;
    std::string str;
    int num1, num2, num3;

    while (str.empty()) {
        getline(in, str);
        if (in.eof()) { return true; }
    }
    p.setName(str.c_str());

    getline(in, str);
    p.setManufacturer(str.c_str());

    in >> num1;
    if (num1 < 0) {
        return false;
    }
    p.setQuantity(num1);

    in >> num1 >> num2 >> num3;
    p.setPlacement(Placement{num3, num2, num1});

    in >> num1 >> num2 >> num3;
    p.setExpirationDate(Date(num1, num2, num3));
    if (!p.getExpirationDate().isValid()) {
        return false;
    }

    in >> num1 >> num2 >> num3;
    p.setStockedDate(Date(num1, num2, num3));
    if (!p.getStockedDate().isValid()) {
        return false;
    }

    getline(in, str);
    getline(in, str);
    p.setComment(str.c_str());

    return w.addProduct(p, p.getSection(), p.getShelf(), p.getIndex());
}


void FileManager::writeWarehouseParams(std::ostream& out, Warehouse& w) const {
    out << w.getCapacity() << "\n";

    for (int i = 0; i < w.getCapacity(); i++) {
        out << " " << w[i].getCapacity();
    }

    out << "\n";

    for (int i = 0; i < w.getCapacity(); i++) {
        for (int j = 0; j < w[i].getCapacity(); j++) {
            out << " " << w[i][j].getCapacity();
        }
    }

    out << "\n";
}


void FileManager::writeWarehouseProducts(std::ostream& out, Warehouse& w) const {
    for (int i = 0; i < w.getCapacity(); i++) {
        for (int j = 0; j < w[i].getCapacity(); j++) {
            for (int k = 0; k < w[i][j].getCapacity(); k++) {
                if (w[i][j][k].getQuantity() != 0) {
                    writeProduct(out, w[i][j][k]);
                }
            }
        }
    }
}


void FileManager::writeProduct(std::ostream& out, Product const& product) const {
    out << product.getName() << "\n"
        << product.getManufacturer() << "\n"
        << product.getQuantity() << "\n"
        << product.getIndex() << " "
        << product.getShelf() << " "
        << product.getSection() << "\n"
        << product.getExpirationDate().day << " "
        << product.getExpirationDate().month << " "
        << product.getExpirationDate().year << "\n"
        << product.getStockedDate().day << " "
        << product.getStockedDate().month << " "
        << product.getStockedDate().year << "\n"
        << product.getComment() << "\n";
}


bool FileManager::readFile(std::istream& in, Warehouse& w) {
    return readWarehouseParams(in, w) && readWarehouseProducts(in, w);
}


void FileManager::writeFile(std::ostream& out, Warehouse& w) {
    writeWarehouseParams(out, w);
    writeWarehouseProducts(out, w);
}
