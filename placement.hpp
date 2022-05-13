#ifndef __PLACEMENT
#define __PLACEMENT

///\brief Representation of a product's placement in warehouse
struct Placement {
    /// The section the product is in
    int section = -1;

    /// The shelf the product is on
    int shelf = -1;

    /// The index the product is at
    int index = -1;
};

#endif
