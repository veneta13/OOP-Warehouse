#ifndef STACK_EXECUTOR_HPP
#define STACK_EXECUTOR_HPP

#include "file_manager.hpp"

#include <fstream>

///\brief User interface provider
class Executor {
    /// The warehouse
    Warehouse warehouse;

    /// File reader/writer
    FileManager fileManager;

    void list(std::ostream& out);
    void addProduct(std::ostream& out, std::istream& in);
    void takeOutProduct(std::ostream& out, std::istream& in);
    void makeQuery(std::ostream& out, std::istream& in);
    void cleanup(std::ostream& out, std::istream& in);
    void load(std::ostream& out, std::istream& in);
    void save(std::ostream& out, std::istream& in);

    void readDate(Date& date, std::ostream& out, std::istream& in);

public:
    Executor();
    Executor(Executor const& other);
    Executor& operator=(Executor const& other);
    ~Executor();

    void setToday(std::ostream& out, std::istream& in);
    bool enter(std::ostream& out, std::istream& in);
};


#endif
