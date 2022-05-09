#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "warehouse.hpp"

TEST_CASE ("Container tests")
{
    SECTION ("Default constructor")
    {
        Container c1;
        REQUIRE(c1.getCapacity() == 0);
    }

    SECTION ("Constructor with parameters")
    {
        Container c1(5);
        REQUIRE(c1.getCapacity() == 5);
    }

    SECTION ("Copy constructor")
    {
        Container c1(5);
        Container c2(c1);
        REQUIRE(c1.getCapacity() == 5);
        REQUIRE(c2.getCapacity() == 5);
    }

    SECTION ("Operator =") {
        Container c1(10);
        Container c2 = c1;
        REQUIRE(c1.getCapacity() == 10);
        REQUIRE(c2.getCapacity() == 10);
    }
}
