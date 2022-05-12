#ifndef STACK_EXECUTOR_HPP
#define STACK_EXECUTOR_HPP


#include "warehouse.hpp"

#include <fstream>

class Executor {
    int commandCodes[6];
    Warehouse warehouse;

    void list(std::ostream& out);
    void addProduct(std::ostream& out, std::istream& in);
    void takeOutProduct(std::ostream& out, std::istream& in);
    void makeQuery(std::ostream& out, std::istream& in);
    void cleanup(std::ostream& out, std::istream& in);
    void load(std::ostream& out, std::istream& in);
    void save(std::ostream& out, std::istream& in);

    void readDate(Date& date, std::ostream& out, std::istream& in);

public:
    void setToday();
    bool enter(std::ostream& out, std::istream& in);
};


#endif
