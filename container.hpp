#ifndef __CONTAINER
#define __CONTAINER

#include "product.hpp"
#include "dyn_array.hpp"

#include <iostream>

class Container {
protected:
    int capacity;

public:
    Container();
    Container(int capacity);
    Container(Container const& other);
    Container& operator=(Container const& other);
    ~Container();

    int getCapacity() const;
};

#endif
