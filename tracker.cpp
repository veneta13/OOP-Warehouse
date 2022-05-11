#include "tracker.hpp"

Tracker::Tracker() {
    today = Date();
    removed = nullptr;
}


Tracker::Tracker(Date const& _date) {
    today = _date;
    removed = nullptr;
}


Tracker::Tracker(Tracker const& other) {
    today = other.today;
    removed = nullptr;
}


Tracker &Tracker::operator=(Tracker const& other) {
    if (this != &other) {
        today = other.today;
        removed = nullptr;
    }
    return *this;
}


Tracker::~Tracker() {
    delete[] removed;
    removedCount = 0;
}


int Tracker::getRemovedIndex(const Date &date) {
    for (int i = 0; i < removedCount; i++) {
        if (removed[i].getDate() == date) {
            return i;
        }
    }
    return -1;
}


void Tracker::addSlotRemoved() {
    DateIndexer* temp = new DateIndexer[removedCount + 1];

    for (int i = 0; i < removedCount; i++) {
        temp[i] = removed[i];
    }

    delete[] removed;
    removed = temp;
    temp = nullptr;
}


Date* Tracker::getToday() {
    return &today;
}


void Tracker::setToday(Date const & date) {
    today = date;
}


void Tracker::addRemoved(Product *product, const Date &dateRemoved) {
    int index = getRemovedIndex(dateRemoved);
    if (index == -1) {
        addSlotRemoved();
        removed[removedCount].setDate(dateRemoved);
        removed[removedCount].addProduct(product);
        removedCount++;
        return;
    }
}

void Tracker::searchInInterval(Date const& from, Date const& to,
                      DynArray<Product*>& stocked, DynArray<Product*>& cleanedUp) {
    for (int i = 0; i < removedCount; i++) {
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

