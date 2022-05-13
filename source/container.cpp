#include "container.hpp"

///Default constructor
Container::Container() : capacity(0) {}


/// Constructor with parameters
/// \param capacity the capacity of the container
Container::Container(int capacity) : capacity(capacity) {}


///Copy constructor
/// \param other container to copy
Container::Container(Container const& other) : capacity(other.capacity) {}


/// Copy assignment operator
/// \param other container to copy
/// \return the updated container
Container& Container::operator=(Container const& other) {
    if (this != &other) {
        capacity = other.capacity;
    }
    return *this;
}


///Destructor
Container::~Container() {
    capacity = 0;
}


///Getter for Container capacity
///\return the capacity of the container
int Container::getCapacity() const {
    return capacity;
}
