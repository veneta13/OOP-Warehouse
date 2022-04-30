#ifndef __PRODUCT
#define __PRODUCT
#include "date.hpp"
#include "placement.hpp"

class Product {
    char* name;
    char* manufacturer;
    char* comment;

    int quantity;

    Date expirationDate;
    Date stockedDate;

    Placement placement;
};

#endif
