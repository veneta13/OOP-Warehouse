#include "tracker.hpp"

Tracker::Tracker() : Container(0){
    removed = nullptr;
}


Tracker::Tracker(Tracker const& other) : Container(0) {
    removed = nullptr;
}


Tracker &Tracker::operator=(Tracker const& other) {
    if (this != &other) {
        delete[] removed;
        capacity = other.capacity;
        removed = nullptr;
    }
    return *this;
}


Tracker::~Tracker() {
    delete[] removed;
}


int Tracker::getRemovedIndex(const Date &date) {
    for (int i = 0; i < capacity; i++) {
        if (removed[i].getDate() == date) {
            return i;
        }
    }
    return -1;
}


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


void Tracker::addRemoved(Product *product, const Date &dateRemoved) {
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

