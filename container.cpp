#include "container.hpp"

Container::Container() : capacity(0) {}


Container::Container(int capacity) : capacity(capacity) {}


Container::Container(Container const& other) : capacity(other.capacity) {}


Container& Container::operator=(Container const& other) {
    if (this != &other) {
        capacity = other.capacity;
    }
    return *this;
}


Container::~Container() {
    capacity = 0;
}


int Container::getCapacity() const {
    return capacity;
}
