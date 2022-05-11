#ifndef __TRACKER
#define __TRACKER

#include "date_indexer.hpp"

class Tracker {
    Date today;
    int removedCount = 0;
    DateIndexer* removed;

    int getRemovedIndex(Date const& date);
    void addSlotRemoved();

public:
    Tracker();
    Tracker(Date const& _date);
    Tracker(Tracker const& other);
    Tracker& operator=(Tracker const& other);
    ~Tracker();

    Date* getToday();
    void setToday(Date const& date);

    void addRemoved(Product* product, Date const& dateRemoved);
    void searchInInterval(Date const& from, Date const& to, DynArray<Product*>& stocked, DynArray<Product*>& cleanedUp);
};

#endif
