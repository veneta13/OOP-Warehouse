#ifndef __TRACKER
#define __TRACKER

#include "date_indexer.hpp"

///\brief Tracks products removed from warehouse
class Tracker : public Container {
    /// The removed products indexed by date of remooval
    DateIndexer* removed;

    int getRemovedIndex(Date const& date);
    void addSlotRemoved();

public:
    Tracker();
    Tracker(Tracker const& other);
    Tracker& operator=(Tracker const& other);
    ~Tracker();

    void addRemoved(Product* product, Date const& dateRemoved);
    void searchInInterval(Date const& from, Date const& to, DynArray<Product*>& stocked, DynArray<Product*>& cleanedUp);
};

#endif
