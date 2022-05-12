#ifndef STACK_FILE_MANAGER_HPP
#define STACK_FILE_MANAGER_HPP

#include "warehouse.hpp"

#include <string>

class FileManager {

    bool readWarehouseParams(std::istream& in, Warehouse& w);
    bool readWarehouseProducts(std::istream& in, Warehouse& w);
    bool readProduct(std::istream& in, Warehouse& w);

    void writeWarehouseParams(std::ostream &out, Warehouse &w) const;
    void writeWarehouseProducts(std::ostream &out, Warehouse &w) const;
    void writeProduct(std::ostream& out, Product const& product) const;

public:
    FileManager();
    FileManager(FileManager const& other);
    FileManager& operator=(FileManager const& other);
    ~FileManager();

    bool readFile(std::istream& in, Warehouse& w);
    void writeFile(std::ostream& out, Warehouse& w);
};

#endif
