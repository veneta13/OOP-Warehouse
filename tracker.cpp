#include "tracker.hpp"

/// Default constructor
Tracker::Tracker() : Container(0){
    removed = nullptr;
}


/// Copy constructor
/// \param other tracker to copy
Tracker::Tracker(Tracker const& other) : Container(0) {
    removed = nullptr;
}


/// Copy assignment operator
/// \param other tracker to copy
/// \return the updated tracker
Tracker &Tracker::operator=(Tracker const& other) {
    if (this != &other) {
        delete[] removed;
        capacity = other.capacity;
        removed = nullptr;
    }
    return *this;
}


/// Destructor
Tracker::~Tracker() {
    delete[] removed;
}


/// Getter for date indexer
/// \param date date to search for
/// \return the index of the date indexer (-1 if not found)
int Tracker::getRemovedIndex(const Date &date) {
    for (int i = 0; i < capacity; i++) {
        if (removed[i].getDate() == date) {
            return i;
        }
    }
    return -1;
}


/// Add a slot for date indexer
void Tracker::addSlotRemoved() {
    DateIndexer* temp = new DateIndexer[capacity + 1];

    for (int i = 0; i < capacity; i++) {
        temp[i].capacity = removed[i].capacity;
        temp[i].productCount = removed[i].productCount;
        temp[i].products = removed[i].products;
        temp[i].date = removed[i].date;
    }

    delete[] removed;
    removed = temp;
    temp = nullptr;
}


/// Add a product
/// \param product product to add
/// \param dateRemoved date of removal of the product
void Tracker::addRemoved(Product *product, const Date &dateRemoved) {
    if (product == nullptr) { return; }
    int index = getRemovedIndex(dateRemoved);
    if (index == -1) {
        addSlotRemoved();
        removed[capacity].setDate(dateRemoved);
        removed[capacity].addProduct(product);
        capacity++;
        return;
    }
    removed[index].addProduct(product);
}


/// Search for stocked and removed products in date interval
/// \param from beginning of date interval
/// \param to end of date interval
/// \param stocked dynamic size array to save stocked in
/// \param cleanedUp dynamic size array to save removed in
void Tracker::searchInInterval(Date const& from, Date const& to,
                      DynArray<Product*>& stocked, DynArray<Product*>& cleanedUp) {
    for (int i = 0; i < capacity; i++) {
        bool cleanedUpFlag = removed[i].getDate() >= from && removed[i].getDate() <= to;
        for (int j = 0; j < removed[i].size(); j++) {
            if (cleanedUpFlag) {
                cleanedUp.push(removed[i].getProduct(j));
            }

            Date tempDate = removed[i].getProduct(j)->getStockedDate();
            if (tempDate >= from && tempDate <= to) {
                stocked.push(removed[i].getProduct(j));
            }
        }
    }
}
