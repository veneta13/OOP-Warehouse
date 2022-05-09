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

TEST_CASE("Product tests")
{
    char const* dummyName1 = "dummy Name1";
    char const* dummyName2 = "dummy Name2";
    char const* dummyManufacturer1 = "dummy Manufacturer1";
    char const* dummyManufacturer2 = "dummy Manufacturer2";
    char const* dummyComment1 = "This is a dummy comment";
    char const* dummyComment2 = "This is another dummy comment";
    Date dummyDate1(12, 3, 2004), dummyDate2(17, 9, 2021);
    Placement dummyPlacement1({1, 2, 3});
    Placement dummyPlacement2({7, 8, 9});

    SECTION("Default constructor")
    {
        Product p1;
        REQUIRE(p1.getName() == nullptr);
        REQUIRE(p1.getManufacturer() == nullptr);
        REQUIRE(p1.getComment() == nullptr);
        REQUIRE(p1.getQuantity() == 0);
        REQUIRE(p1.getExpirationDate() == Date());
        REQUIRE(p1.getStockedDate() == Date());
        REQUIRE(p1.getPlacement().index == Placement().index);
    }

    SECTION("Constructor with parameters")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        REQUIRE(strcmp(p1.getName(), dummyName1) == 0);
        REQUIRE(strcmp(p1.getManufacturer(), dummyManufacturer1) == 0);
        REQUIRE(strcmp(p1.getComment(), dummyComment1) == 0);
        REQUIRE(p1.getQuantity() == 1);
        REQUIRE(p1.getExpirationDate() == dummyDate1);
        REQUIRE(p1.getStockedDate() == dummyDate2);
        REQUIRE(p1.getPlacement().index == dummyPlacement1.index);
    }

    SECTION("Copy constructor")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(p1);
        REQUIRE(strcmp(p1.getName(), dummyName1) == 0);
        REQUIRE(strcmp(p1.getManufacturer(), dummyManufacturer1) == 0);
        REQUIRE(strcmp(p1.getComment(), dummyComment1) == 0);
        REQUIRE(p1.getQuantity() == 1);
        REQUIRE(p1.getExpirationDate() == dummyDate1);
        REQUIRE(p1.getStockedDate() == dummyDate2);
        REQUIRE(p1.getPlacement().index == dummyPlacement1.index);

        REQUIRE(strcmp(p2.getName(), dummyName1) == 0);
        REQUIRE(strcmp(p2.getManufacturer(), dummyManufacturer1) == 0);
        REQUIRE(strcmp(p2.getComment(), dummyComment1) == 0);
        REQUIRE(p2.getQuantity() == 1);
        REQUIRE(p2.getExpirationDate() == dummyDate1);
        REQUIRE(p2.getStockedDate() == dummyDate2);
        REQUIRE(p2.getPlacement().index == dummyPlacement1.index);
    }

    SECTION("Operator =")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2 = p1;
        REQUIRE(strcmp(p1.getName(), dummyName1) == 0);
        REQUIRE(strcmp(p1.getManufacturer(), dummyManufacturer1) == 0);
        REQUIRE(strcmp(p1.getComment(), dummyComment1) == 0);
        REQUIRE(p1.getQuantity() == 1);
        REQUIRE(p1.getExpirationDate() == dummyDate1);
        REQUIRE(p1.getStockedDate() == dummyDate2);
        REQUIRE(p1.getPlacement().index == dummyPlacement1.index);

        REQUIRE(strcmp(p2.getName(), dummyName1) == 0);
        REQUIRE(strcmp(p2.getManufacturer(), dummyManufacturer1) == 0);
        REQUIRE(strcmp(p2.getComment(), dummyComment1) == 0);
        REQUIRE(p2.getQuantity() == 1);
        REQUIRE(p2.getExpirationDate() == dummyDate1);
        REQUIRE(p2.getStockedDate() == dummyDate2);
        REQUIRE(p2.getPlacement().index == dummyPlacement1.index);
    }

    SECTION("Setters and getters")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        REQUIRE(strcmp(p1.getName(), dummyName1) == 0);
        REQUIRE(strcmp(p1.getManufacturer(), dummyManufacturer1) == 0);
        REQUIRE(strcmp(p1.getComment(), dummyComment1) == 0);
        REQUIRE(p1.getQuantity() == 1);
        REQUIRE(p1.getExpirationDate() == dummyDate1);
        REQUIRE(p1.getStockedDate() == dummyDate2);
        REQUIRE(p1.getPlacement().index == dummyPlacement1.index);

        p1.setName(dummyName2);
        REQUIRE(strcmp(p1.getName(), dummyName2) == 0);

        p1.setManufacturer(dummyManufacturer2);
        REQUIRE(strcmp(p1.getManufacturer(), dummyManufacturer2) == 0);

        p1.setComment(dummyComment2);
        REQUIRE(strcmp(p1.getComment(), dummyComment2) == 0);

        p1.setQuantity(5);
        REQUIRE(p1.getQuantity() == 5);

        p1.setExpirationDate(dummyDate2);
        REQUIRE(p1.getExpirationDate() == dummyDate2);

        p1.setStockedDate(dummyDate1);
        REQUIRE(p1.getStockedDate() == dummyDate1);

        p1.setPlacement(dummyPlacement2);
        REQUIRE(p1.getPlacement().index == dummyPlacement2.index);
        REQUIRE(p1.getPlacement().shelf == dummyPlacement2.shelf);
        REQUIRE(p1.getPlacement().section == dummyPlacement2.section);

        p1.setIndex(40);
        REQUIRE(p1.getIndex() == 40);

        p1.setShelf(15);
        REQUIRE(p1.getShelf() == 15);

        p1.setSection(30);
        REQUIRE(p1.getSection() == 30);
    }

    SECTION("Same name check")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2 = p1;
        REQUIRE(strcmp(p1.getName(), dummyName1) == 0);
        REQUIRE(strcmp(p2.getName(), dummyName1) == 0);
        REQUIRE(p1.hasSameName(p1));
        REQUIRE(p2.hasSameName(p2));
        REQUIRE(p1.hasSameName(p2));
        REQUIRE(p2.hasSameName(p1));

        p2.setName(dummyName2);
        REQUIRE(strcmp(p2.getName(), dummyName2) == 0);
        REQUIRE(p2.hasSameName(p2));
        REQUIRE(!(p1.hasSameName(p2)));
        REQUIRE(!(p2.hasSameName(p1)));
    }

    SECTION("Operator ==")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2 = p1;
        REQUIRE(p1 == p2);
        REQUIRE(p1 == p1);
        REQUIRE(p2 == p2);

        p2.setName(dummyName2);
        REQUIRE(!(p1 == p2));
    }

    SECTION("Operator >")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate2, dummyDate2, dummyPlacement1);
        Product p2(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        REQUIRE(p1 > p2);
        REQUIRE(!(p2 > p1));

        p2.setName(dummyName2);
        REQUIRE(!(p1 > p2));
        REQUIRE(!(p2 > p1));
    }

    SECTION("Operator <")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate2, dummyDate2, dummyPlacement1);
        REQUIRE(p1 < p2);
        REQUIRE(!(p2 < p1));

        p2.setName(dummyName2);
        REQUIRE(!(p1 < p2));
        REQUIRE(!(p2 < p1));
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
