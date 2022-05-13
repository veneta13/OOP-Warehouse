#ifndef __DATE_INDEXER
#define __DATE_INDEXER

#include "date.hpp"
#include "product.hpp"
#include "container.hpp"

///\brief Contain dates removed on a specific date from the warehouse
class DateIndexer : public Container {
    /// Date of removal
    Date date;

    /// The quantity of the products in indexer
    int productCount;

    /// Product pointers
    Product** products;

    void resize();

public:
    DateIndexer();
    DateIndexer(Date const& _date);
    DateIndexer(DateIndexer const& other);
    DateIndexer& operator=(DateIndexer const& other);
    ~DateIndexer();

    Date& getDate();
    Product* getProduct(int index) const;
    int size() const;

    void setDate(Date const& _date);
    void addProduct(Product* product);

    friend class Tracker;
};

#endif
