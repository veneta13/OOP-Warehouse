#ifndef __DATE_INDEXER
#define __DATE_INDEXER

#include "dyn_array.hpp"
#include "date.hpp"
#include "product.hpp"
#include "container.hpp"

class DateIndexer : public Container {
    Date date;
    int productCount;
    Product* products;

    void copyProducts(Product *others);
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
    void addProduct(const Product &product);
};

#endif
