#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "warehouse.hpp"

TEST_CASE("Date tests")
{
    SECTION ("Default constructor")
    {
        Date d1;
        REQUIRE(d1.day == 0);
        REQUIRE(d1.month == 0);
        REQUIRE(d1.year == 0);
    }

    SECTION ("Constructor with parameters")
    {
        Date d1(9, 10, 2000);
        REQUIRE(d1.day == 9);
        REQUIRE(d1.month == 10);
        REQUIRE(d1.year == 2000);
    }

    SECTION ("Copy constructor")
    {
        Date d1(9, 10, 2001);
        Date d2(d1);
        REQUIRE(d1.day == 9);
        REQUIRE(d1.month == 10);
        REQUIRE(d1.year == 2001);
        REQUIRE(d2.day == 9);
        REQUIRE(d2.month == 10);
        REQUIRE(d2.year == 2001);
    }

    SECTION ("Operator =")
    {
        Date d1(20, 4, 2015);
        Date d2 = d1;
        REQUIRE(d1.day == 20);
        REQUIRE(d1.month == 4);
        REQUIRE(d1.year == 2015);
        REQUIRE(d2.day == 20);
        REQUIRE(d2.month == 4);
        REQUIRE(d2.year == 2015);
    }

    SECTION ("Validity")
    {
        Date d1(-1, 2, 2015);
        REQUIRE(!d1.isValid());

        Date d2(2, 0, 2015);
        REQUIRE(!d2.isValid());

        Date d3(3, 1, -3);
        REQUIRE(!d3.isValid());

        Date d4(32, 10, 2001);
        REQUIRE(!d4.isValid());

        Date d5(10, 13, 2005);
        REQUIRE(!d5.isValid());

        Date d6(29, 2, 2003);
        REQUIRE(!d6.isValid());

        Date d7(31, 4, 2004);
        REQUIRE(!d7.isValid());

        Date d8(29, 2, 2008);
        REQUIRE(d8.isValid());

        Date d9(15, 3, 2005);
        REQUIRE(d9.isValid());

        Date d10(31, 10, 2009);
        REQUIRE(d10.isValid());
    }

    SECTION ("Operator >")
    {
        Date d1(10, 1, 2006), d2(10, 1, 2002);
        REQUIRE(d1 > d2);
        REQUIRE(!(d2 > d1));

        Date d3(10, 4, 2006), d4(10, 3, 2006);
        REQUIRE(d3 > d4);
        REQUIRE(!(d4 > d3));

        Date d5(11, 5, 2006), d6(10, 5, 2006);
        REQUIRE(d5 > d6);
        REQUIRE(!(d6 > d5));

        Date d7(3, 5, 2006), d8(10, 6, 1895);
        REQUIRE(d7 > d8);
        REQUIRE(!(d8 > d7));

        REQUIRE(!(d7 > d7));
    }

    SECTION ("Operator <")
    {
        Date d1(10, 1, 2006), d2(10, 1, 2002);
        REQUIRE(d2 < d1);
        REQUIRE(!(d1 < d2));

        Date d3(10, 4, 2006), d4(10, 3, 2006);
        REQUIRE(d4 < d3);
        REQUIRE(!(d3 < d4));

        Date d5(11, 5, 2006), d6(10, 5, 2006);
        REQUIRE(d6 < d5);
        REQUIRE(!(d5 < d6));

        Date d7(3, 5, 2006), d8(10, 6, 1895);
        REQUIRE(d8 < d7);
        REQUIRE(!(d7 < d8));

        REQUIRE(!(d7 < d7));
    }

    SECTION ("Operator ==") 
    {
        Date d1(10, 1, 2006);
        Date d2 = d1;

        REQUIRE(d1 == d2);
        REQUIRE(d1 == d1);
        REQUIRE(d2 == d2);

        Date d3(12, 12, 2012), d4(13, 12, 2012);
        REQUIRE(!(d3 == d4));

        Date d5(12, 12, 2012), d6(12, 11, 2012);
        REQUIRE(!(d5 == d6));

        Date d7(12, 12, 2012), d8(12, 12, 2013);
        REQUIRE(!(d7 == d8));
    }

    SECTION ("Operator !=") 
    {
        Date d1(10, 1, 2006);
        Date d2 = d1;

        REQUIRE(!(d1 != d2));
        REQUIRE(!(d1 != d1));
        REQUIRE(!(d2 != d2));

        Date d3(12, 12, 2012), d4(13, 12, 2012);
        REQUIRE(d3 != d4);

        Date d5(12, 12, 2012), d6(12, 11, 2012);
        REQUIRE(d5 != d6);

        Date d7(12, 12, 2012), d8(12, 12, 2013);
        REQUIRE(d7 != d8);
    }

    SECTION ("Operator >=")
    {
        Date d1(10, 1, 2006), d2(10, 1, 2002);
        REQUIRE(d1 >= d2);
        REQUIRE(!(d2 >= d1));

        Date d3(3, 5, 2006), d4(10, 6, 1895);
        REQUIRE(d3 >= d4);
        REQUIRE(!(d4 >= d3));

        Date d5(11, 5, 2006);
        Date d6 = d5;
        REQUIRE(d5 >= d6);
        REQUIRE(d6 >= d5);
    }

    SECTION ("Operator <=")
    {
        Date d1(10, 1, 2006), d2(10, 1, 2002);
        REQUIRE(!(d1 <= d2));
        REQUIRE(d2 <= d1);

        Date d3(3, 5, 2006), d4(10, 6, 1895);
        REQUIRE(!(d3 <= d4));
        REQUIRE(d4 <= d3);

        Date d5(11, 5, 2006);
        Date d6 = d5;
        REQUIRE(d5 <= d6);
        REQUIRE(d6 <= d5);
    }
}

TEST_CASE("Placement tests") 
{
    SECTION("Default")
    {
        Placement p1;
        REQUIRE(p1.index == -1);
        REQUIRE(p1.shelf == -1);
        REQUIRE(p1.section == -1);
    }

    SECTION("Placement with parameters")
    {
        Placement p1({2, 3, 4});
        REQUIRE(p1.index == 4);
        REQUIRE(p1.shelf == 3);
        REQUIRE(p1.section == 2);
    }

    SECTION("Change members")
    {
        Placement p1({2, 3, 4});
        REQUIRE(p1.index == 4);
        REQUIRE(p1.shelf == 3);
        REQUIRE(p1.section == 2);


        p1.index = 5;
        REQUIRE(p1.index == 5);
        REQUIRE(p1.shelf == 3);
        REQUIRE(p1.section == 2);

        p1.shelf = 9;
        REQUIRE(p1.index == 5);
        REQUIRE(p1.shelf == 9);
        REQUIRE(p1.section == 2);

         p1.section = 7;
        REQUIRE(p1.index == 5);
        REQUIRE(p1.shelf == 9);
        REQUIRE(p1.section == 7);
    }
}

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
