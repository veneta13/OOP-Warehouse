#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "warehouse.hpp"

#include<sstream>

char const* dummyName1 = "dummy Name1";
char const* dummyName2 = "dummy Name2";
char const* dummyName3 = "dummy Name3";
char const* dummyManufacturer1 = "dummy Manufacturer1";
char const* dummyManufacturer2 = "dummy Manufacturer2";
char const* dummyManufacturer3 = "dummy Manufacturer3";
char const* dummyComment1 = "This is a dummy comment";
char const* dummyComment2 = "This is another dummy comment";
char const* dummyComment3 = "This is dummy comment 3";
Date dummyDate1(12, 3, 2004);
Date dummyDate2(1, 2, 2021);
Date dummyDate3(26, 4, 2020);
Placement dummyPlacement1({1, 2, 3});
Placement dummyPlacement2({7, 8, 9});

TEST_CASE("Dynamic array tests")
{
    SECTION("Constructor with parameter")
    {
        DynArray<const char*> array(3);
        REQUIRE(array.size() == 0);
    }

    SECTION("Copy constructor")
    {
        DynArray<const char*> array(3);
        const char* str = "my string";
        array.push(str);

        REQUIRE(strcmp(array[0], str) == 0);
        REQUIRE(array.size() == 1);

        DynArray<const char*> arrCopy(array);
        REQUIRE(strcmp(arrCopy[0], str) == 0);
        REQUIRE(arrCopy.size() == 1);
    }

    SECTION("Operator =")
    {
        DynArray<const char*> array(3);
        const char* str = "my string";
        array.push(str);

        REQUIRE(strcmp(array[0], str) == 0);
        REQUIRE(array.size() == 1);

        DynArray<const char*> arrCopy = array;
        REQUIRE(strcmp(arrCopy[0], str) == 0);
        REQUIRE(arrCopy.size() == 1);
    }

    SECTION("Operator []")
    {
        DynArray<const char*> array(3);
        const char* str1 = "my string";
        const char* str2 = "other string";

        array.push(str1);
        array.push(str2);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
    }

    SECTION("Operator []")
    {
        DynArray<const char*> array(3);
        const char* str1 = "my string";
        const char* str2 = "other string";

        array.push(str1);
        array.push(str2);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
    }

    SECTION("Insert")
    {
        DynArray<const char*> array(3);
        const char* str1 = "my string";
        const char* str2 = "other string";

        array.insert(str1, 0);
        array.insert(str2, 2);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[2], str2) == 0);
    }

    SECTION("Push")
    {
        DynArray<const char*> array(4);
        const char* str1 = "my string";
        const char* str2 = "other string";
        const char* str3 = "another string";

        array.push(str1);
        array.push(str2);
        array.push(str3);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
        REQUIRE(strcmp(array[2], str3) == 0);
    }

    SECTION("Erase")
    {
        DynArray<const char*> array(4);
        const char* str1 = "my string";
        const char* str2 = "other string";
        const char* str3 = "another string";

        array.push(str1);
        array.push(str2);
        array.push(str3);

        REQUIRE(array.size() == 3);
        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
        REQUIRE(strcmp(array[2], str3) == 0);

        array.erase(2);
        REQUIRE(array.size() == 2);

        array.erase(1);
        REQUIRE(array.size() == 1);

        array.erase(0);
        REQUIRE(array.size() == 0);
    }

    SECTION("Pop")
    {
        DynArray<const char*> array(4);
        const char* str1 = "my string";
        const char* str2 = "other string";
        const char* str3 = "another string";

        array.push(str1);
        array.push(str2);
        array.push(str3);

        REQUIRE(array.size() == 3);
        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
        REQUIRE(strcmp(array[2], str3) == 0);

        array.pop();
        REQUIRE(array.size() == 2);

        array.pop();
        REQUIRE(array.size() == 1);

        array.pop();
        REQUIRE(array.size() == 0);
    }

    SECTION("Swap")
    {
        DynArray<const char*> array(4);
        const char* str1 = "my string";
        const char* str2 = "other string";
        const char* str3 = "another string";

        array.push(str1);
        array.push(str2);
        array.push(str3);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
        REQUIRE(strcmp(array[2], str3) == 0);

        REQUIRE(array.swap(1, 2));
        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str3) == 0);
        REQUIRE(strcmp(array[2], str2) == 0);

        REQUIRE(array.swap(0, 2));
        REQUIRE(strcmp(array[0], str2) == 0);
        REQUIRE(strcmp(array[1], str3) == 0);
        REQUIRE(strcmp(array[2], str1) == 0);

        REQUIRE(!array.swap(0, 3));
        REQUIRE(!array.swap(0, -3));
    }
}

TEST_CASE("Date tests")
{
    SECTION("Default constructor")
    {
        Date d1;
        REQUIRE(d1.day == 0);
        REQUIRE(d1.month == 0);
        REQUIRE(d1.year == 0);
    }

    SECTION("Constructor with parameters")
    {
        Date d1(9, 10, 2000);
        REQUIRE(d1.day == 9);
        REQUIRE(d1.month == 10);
        REQUIRE(d1.year == 2000);
    }

    SECTION("Copy constructor")
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

    SECTION("Operator =")
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

    SECTION("Validity")
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

    SECTION("Operator >")
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

    SECTION("Operator <")
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

    SECTION("Operator ==")
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

    SECTION("Operator !=")
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

    SECTION("Operator >=")
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

    SECTION("Operator <=")
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

    SECTION("Operator <<")
    {
        Date d1(10, 1, 2006), d2(10, 1, 2002);
        std::stringstream out;
        out << d1 << " ";
        REQUIRE(out.str() == "10/1/2006 ");
        out << d2;
        REQUIRE(out.str() == "10/1/2006 10/1/2002");
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

    SECTION("Operator <<")
    {
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        const char* answer = "NAME: dummy Name1\n"
        "DETAILS:\n"
        "COUNT: 1\n"
        "MANUFACTURER: dummy Manufacturer1\n"
        "INDEX: 3 SHELF: 2 SECTION: 1\n"
        "EXP: 12/3/2004 STOCK: 1/2/2021\n"
        "NOTES: This is a dummy comment";

        std::stringstream out;
        out << p1;
        REQUIRE(out.str() == answer);
    }
}

TEST_CASE("Container tests")
{
    SECTION("Default constructor")
    {
        Container c1;
        REQUIRE(c1.getCapacity() == 0);
    }

    SECTION("Constructor with parameters")
    {
        Container c1(5);
        REQUIRE(c1.getCapacity() == 5);
    }

    SECTION("Copy constructor")
    {
        Container c1(5);
        Container c2(c1);
        REQUIRE(c1.getCapacity() == 5);
        REQUIRE(c2.getCapacity() == 5);
    }

    SECTION("Operator =") {
        Container c1(10);
        Container c2 = c1;
        REQUIRE(c1.getCapacity() == 10);
        REQUIRE(c2.getCapacity() == 10);
    }
}

TEST_CASE("DateIndexer tests")
{
    SECTION("Default constructor")
    {
        DateIndexer d1;
        REQUIRE(d1.getCapacity() == 5);
        REQUIRE(d1.size() == 0);
        REQUIRE(d1.getDate() == Date());
    }

    SECTION("Constructor with date")
    {
        DateIndexer d1(dummyDate1);
        REQUIRE(d1.getCapacity() == 5);
        REQUIRE(d1.size() == 0);
        REQUIRE(d1.getDate() == dummyDate1);
    }

    SECTION("Copy constructor")
    {
        Product* p1 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate2, dummyPlacement1);

        DateIndexer d1(dummyDate1);
        d1.addProduct(p1);
        REQUIRE(d1.getCapacity() == 5);
        REQUIRE(d1.size() == 1);
        REQUIRE(*d1.getProduct(0) == *p1);
        REQUIRE(d1.getDate() == dummyDate1);

        DateIndexer d2(d1);
        REQUIRE(d2.getCapacity() == 5);
        REQUIRE(d2.size() == 0);
        REQUIRE(d2.getDate() == dummyDate1);
    }

    SECTION("Operator =")
    {
        Product* p1 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate2, dummyPlacement1);

        DateIndexer d1(dummyDate1);
        d1.addProduct(p1);
        REQUIRE(d1.getCapacity() == 5);
        REQUIRE(d1.size() == 1);
        REQUIRE(*d1.getProduct(0) == *p1);
        REQUIRE(d1.getDate() == dummyDate1);

        DateIndexer d2 = d1;
        REQUIRE(d2.getCapacity() == 5);
        REQUIRE(d2.size() == 0);
        REQUIRE(d2.getDate() == dummyDate1);
    }

    SECTION("Resize")
    {
        Product* p1 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate2, dummyPlacement1);
        Product* p2 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate2, dummyPlacement1);
        Product* p3 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate2, dummyPlacement1);
        Product* p4 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate2, dummyPlacement1);
        Product* p5 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate2, dummyPlacement1);
        Product* p6 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate2, dummyPlacement1);

        DateIndexer d1(dummyDate1);
        d1.addProduct(p1);
        d1.addProduct(p2);
        d1.addProduct(p3);
        d1.addProduct(p4);
        d1.addProduct(p5);
        d1.addProduct(p6);

        REQUIRE(d1.getCapacity() == 10);
        REQUIRE(d1.size() == 6);
        REQUIRE(*d1.getProduct(0) == *p1);
        REQUIRE(*d1.getProduct(1) == *p2);
        REQUIRE(*d1.getProduct(2) == *p3);
        REQUIRE(*d1.getProduct(3) == *p4);
        REQUIRE(*d1.getProduct(4) == *p5);
        REQUIRE(*d1.getProduct(5) == *p6);
        REQUIRE(d1.getDate() == dummyDate1);
    }

    SECTION("Set date")
    {
        DateIndexer d1(dummyDate1);
        REQUIRE(d1.getDate() == dummyDate1);

        d1.setDate(dummyDate2);
        REQUIRE(d1.getDate() == dummyDate2);
    }
}

TEST_CASE("Tracker tests")
{
    SECTION("Default constructor")
    {
        Tracker t1;
        REQUIRE(*t1.getToday() == Date());
    }

    SECTION("Constructor with today")
    {
        Tracker t1(dummyDate1);
        REQUIRE(*t1.getToday() == dummyDate1);
    }

    SECTION("Copy constructor")
    {
        Tracker t1(dummyDate1);
        Tracker t2(t1);

        REQUIRE(*t1.getToday() == dummyDate1);
        REQUIRE(*t2.getToday() == dummyDate1);
    }

    SECTION("Operator =")
    {
        Tracker t1(dummyDate1);
        Tracker t2 = t1;

        REQUIRE(*t1.getToday() == dummyDate1);
        REQUIRE(*t2.getToday() == dummyDate1);
    }

    SECTION("Today getter and setter")
    {
        Tracker t1(dummyDate1);

        REQUIRE(*t1.getToday() == dummyDate1);
        t1.setToday(dummyDate2);
        REQUIRE(*t1.getToday() == dummyDate2);
    }

    SECTION("Add and search")
    {
        DynArray<Product*> stocked(2), cleanedUp(2);

        Product* p1 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate3, dummyDate1, dummyPlacement1);
        Product* p2 = new Product(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        Tracker t1(dummyDate1);
        t1.addRemoved(p1, dummyDate1);
        t1.searchInInterval(dummyDate1, dummyDate3, stocked, cleanedUp);

        REQUIRE(stocked.size() == 1);
        REQUIRE(cleanedUp.size() == 1);

        REQUIRE(*stocked[0] == *p1);
        REQUIRE(*cleanedUp[0] == *p1);
    }
}

TEST_CASE("Shelf tests")
{
    SECTION("Default constructor")
    {
        Shelf s1;
        REQUIRE(s1.getCapacity() == 0);
    }

    SECTION("Constructor with parameters")
    {
        Shelf s1(10);
        REQUIRE(s1.getCapacity() == 10);
    }

    SECTION("Copy constructor")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(s1.addProduct(p1, 0, true));

        Shelf s2(s1);
        REQUIRE(s2.getCapacity() == 10);
        REQUIRE(s2[0] == p1);
    }

    SECTION("Operator =")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(s1.addProduct(p1, 0, true));

        Shelf s2 = s1;
        REQUIRE(s2.getCapacity() == 10);
        REQUIRE(s2[0] == p1);
    }

    SECTION("Operator []")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(s1.addProduct(p1, 0, true));
        REQUIRE(s1.addProduct(p2, 1, true));
        REQUIRE(s1[0] == p1);
        REQUIRE(s1[1] == p2);
    }

    SECTION("Add products")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate2, dummyDate2, dummyPlacement2);
        Product p3(dummyName1, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);

        REQUIRE(s1.addProduct(p1).index == 0);
        REQUIRE(s1.addProduct(p2).index == 1);
        REQUIRE(s1.addProduct(p3).index == 2);
    }

    SECTION("Find equal")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate2, dummyDate2, dummyPlacement2);
        Product p3(dummyName1, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);

        REQUIRE(s1.findEqual(dummyName1, dummyDate1) == nullptr);

        REQUIRE(s1.addProduct(p2, 0, true));
        REQUIRE(s1.findEqual(dummyName1, dummyDate1) == nullptr);

        REQUIRE(s1.addProduct(p1, 1, true));
        REQUIRE(*s1.findEqual(dummyName1, dummyDate1) == p1);

        REQUIRE(s1.addProduct(p3, 2, true));
        REQUIRE(*s1.findEqual(dummyName1, dummyDate1) == p1);
    }

    SECTION("Find by name")
    {
        Shelf s1(10);
        REQUIRE(!s1.findByName(dummyName1));
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);

        REQUIRE(s1.addProduct(p1, 0, true));
        REQUIRE(s1.findByName(dummyName1));
    }

    SECTION("Find all by name")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate2, dummyDate2, dummyPlacement2);
        DynArray<Product*> result(5);

        REQUIRE(result.size() == 0);
        s1.findAllByName(dummyName1, result);
        REQUIRE(result.size() == 0);

        REQUIRE(s1.addProduct(p1, 1, true));
        s1.findAllByName(dummyName1, result);
        REQUIRE(result.size() == 1);

        REQUIRE(s1.addProduct(p2, 2, true));
        s1.findAllByName(dummyName1, result);
        REQUIRE(result.size() == 2);
    }

    SECTION("Find all by date")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate2, dummyDate2, dummyPlacement2);
        DynArray<Product*> result(5);

        REQUIRE(result.size() == 0);
        s1.findAllByDate(dummyDate1, result);
        REQUIRE(result.size() == 0);

        REQUIRE(s1.addProduct(p1, 1, true));
        s1.findAllByDate(dummyDate1, result);
        REQUIRE(result.size() == 1);

        REQUIRE(s1.addProduct(p2, 2, true));
        s1.findAllByDate(dummyDate1, result);
        REQUIRE(result.size() == 2);
    }

    SECTION("Remove")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate2, dummyDate2, dummyPlacement2);
        Product p3(dummyName1, dummyManufacturer2, dummyComment1, 3, dummyDate1, dummyDate2, dummyPlacement2);

        REQUIRE(s1.findEqual(dummyName1, dummyDate1) == nullptr);

        REQUIRE(s1.addProduct(p2, 0, true));
        REQUIRE(s1.findEqual(dummyName1, dummyDate1) == nullptr);

        REQUIRE(s1.addProduct(p1, 1, true));
        REQUIRE(*s1.findEqual(dummyName1, dummyDate1) == p1);

        Product* ptr = s1.removeProduct(1, -1);
        REQUIRE(*ptr == p1);
        delete ptr;
        REQUIRE(!s1.findEqual(dummyName1, dummyDate1));

        REQUIRE(s1.addProduct(p3, 2, true));
        REQUIRE(*s1.findEqual(dummyName1, dummyDate1) == p3);

        Product p4(p3);
        p4.setQuantity(2);
        ptr = s1.removeProduct(2, 2);
        REQUIRE(*ptr == p4);
        delete ptr;
        p3.setQuantity(1);
        REQUIRE(*s1.findEqual(dummyName1, dummyDate1) == p3);

        REQUIRE(!s1.removeProduct(2, 5));
        REQUIRE(*s1.findEqual(dummyName1, dummyDate1) == p3);
    }

    SECTION("Operator <<")
    {
        Shelf s1(10);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement2);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate2, dummyDate2, dummyPlacement2);

        REQUIRE(s1.addProduct(p1).index == 0);
        REQUIRE(s1.addProduct(p2).index == 1);

        const char* answer = "NAME: dummy Name1\n"
        "DETAILS:\n"
        "COUNT: 1\n"
        "MANUFACTURER: dummy Manufacturer1\n"
        "INDEX: 9 SHELF: 8 SECTION: 7\n"
        "EXP: 12/3/2004 STOCK: 1/2/2021\n"
        "NOTES: This is a dummy comment\n"
        "NAME: dummy Name2\n"
        "DETAILS:\n"
        "COUNT: 1\n"
        "MANUFACTURER: dummy Manufacturer2\n"
        "INDEX: 9 SHELF: 8 SECTION: 7\n"
        "EXP: 1/2/2021 STOCK: 1/2/2021\n"
        "NOTES: This is a dummy comment\n";

        std::stringstream out;
        out << s1;
        REQUIRE(out.str() == answer);
    }
}

TEST_CASE("Section tests")
{
    SECTION("Default constructor")
    {
        Section c1;
        REQUIRE(c1.getCapacity() == 0);
    }

    SECTION("Constructor with parameters")
    {
        Section c1(2);
        REQUIRE(c1.getCapacity() == 2);
    }

    SECTION("Copy constructor")
    {
        Section c1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1.setShelfCapacity(1, 3));

        REQUIRE(c1[0].addProduct(p1).index == 0);
        REQUIRE(c1[1].addProduct(p2).index == 0);

        Section c2(c1);

        REQUIRE(c2.getCapacity() == 2);
        REQUIRE(c2.findByName(dummyName1));
        REQUIRE(c2.findByName(dummyName2));
    }

    SECTION("Operator =")
    {
        Section c1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1.setShelfCapacity(1, 3));

        REQUIRE(c1[0].addProduct(p1).index == 0);
        REQUIRE(c1[1].addProduct(p2).index == 0);

        Section c2 = c1;

        REQUIRE(c2.getCapacity() == 2);
        REQUIRE(c2.findByName(dummyName1));
        REQUIRE(c2.findByName(dummyName2));
    }

    SECTION("Operator []")
    {
        Section c1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1.setShelfCapacity(1, 3));

        REQUIRE(c1[0].addProduct(p1).index == 0);
        REQUIRE(c1[1].addProduct(p2).index == 0);

        REQUIRE(c1[0][0] == p1);
        REQUIRE(c1[1][0] == p2);
    }

    SECTION("Set shelf capacity")
    {
        Section c1(2);
        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1[0].getCapacity() == 2);
        REQUIRE(c1.setShelfCapacity(1, 3));
        REQUIRE(c1[1].getCapacity() == 3);
        REQUIRE(!c1.setShelfCapacity(2, 3));
    }

    SECTION("Find equal")
    {
        Section c1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName1, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p3(dummyName2, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1.setShelfCapacity(1, 3));

        REQUIRE(c1[0].addProduct(p1).index == 0);
        REQUIRE(c1[1].addProduct(p3).index == 0);

        REQUIRE(!c1.findEqual(dummyName2, dummyDate2));
        REQUIRE(*c1.findEqual(dummyName1, dummyDate1) == p1);

        REQUIRE(c1[1].addProduct(p2).index == 1);
        REQUIRE(*c1.findEqual(dummyName1, dummyDate1) == p1);
    }

    SECTION("Find by name")
    {
        Section c1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName1, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p3(dummyName2, dummyManufacturer1, dummyComment1, 0, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1.setShelfCapacity(1, 3));

        REQUIRE(c1[0].addProduct(p1).index == 0);
        REQUIRE(c1[1].addProduct(p2).index == 0);

        REQUIRE(c1.findByName(dummyName1));
        REQUIRE(!c1.findByName(dummyName2));

        REQUIRE(c1[1].addProduct(p3).index == 1);
        REQUIRE(!c1.findByName(dummyName2));
    }

    SECTION("Find all by name")
    {
        DynArray<Product*> result(5);
        Section c1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName1, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p3(dummyName2, dummyManufacturer1, dummyComment1, 0, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1.setShelfCapacity(1, 3));

        REQUIRE(result.size() == 0);

        REQUIRE(c1[0].addProduct(p1).index == 0);
        REQUIRE(c1[1].addProduct(p2).index == 0);

        c1.findAllByName(dummyName1, result);
        REQUIRE(result.size() == 2);

        REQUIRE(c1[1].addProduct(p3).index == 1);

        c1.findAllByName(dummyName1, result);
        REQUIRE(result.size() == 4);
    }

    SECTION("Find all by date")
    {
        DynArray<Product*> result(5);
        Section c1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName1, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p3(dummyName2, dummyManufacturer1, dummyComment1, 0, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1.setShelfCapacity(1, 3));

        REQUIRE(result.size() == 0);

        REQUIRE(c1[0].addProduct(p1).index == 0);
        REQUIRE(c1[1].addProduct(p2).index == 0);

        c1.findAllByDate(dummyDate1, result);
        REQUIRE(result.size() == 2);

        REQUIRE(c1[1].addProduct(p3).index == 1);

        c1.findAllByDate(dummyDate2, result);
        REQUIRE(result.size() == 4);
    }

    SECTION("Remove product")
    {
        Section c1(1);
        Product p1(dummyName1, dummyManufacturer2, dummyComment1, 8, dummyDate1, dummyDate2, dummyPlacement2);
        REQUIRE(c1.setShelfCapacity(0, 3));

        Placement res = c1.addProduct(p1);
        REQUIRE(res.index == 0);
        REQUIRE(res.section == 0);

        REQUIRE(c1.findByName(dummyName1));

        Product* ptr = c1.removeProduct(0, 0, -1);
        REQUIRE(*ptr == p1);
        delete ptr;

        REQUIRE(!c1.findByName(dummyName1));
    }

    SECTION("Operator <<")
    {
        Section c1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName1, dummyManufacturer2, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);

        const char* answer = "NAME: dummy Name1\n"
        "DETAILS:\n"
        "COUNT: 1\n"
        "MANUFACTURER: dummy Manufacturer1\n"
        "INDEX: 3 SHELF: 2 SECTION: 1\n"
        "EXP: 12/3/2004 STOCK: 1/2/2021\n"
        "NOTES: This is a dummy comment\n"
        "NAME: dummy Name1\n"
        "DETAILS:\n"
        "COUNT: 1\n"
        "MANUFACTURER: dummy Manufacturer2\n"
        "INDEX: 3 SHELF: 2 SECTION: 1\n"
        "EXP: 12/3/2004 STOCK: 1/2/2021\n"
        "NOTES: This is a dummy comment\n";

        REQUIRE(c1.setShelfCapacity(0, 2));
        REQUIRE(c1.setShelfCapacity(1, 3));

        REQUIRE(c1[0].addProduct(p1).index == 0);
        REQUIRE(c1[1].addProduct(p2).index == 0);

        std::stringstream out;
        out << c1;
        REQUIRE(out.str() == answer);
    }
}

TEST_CASE("Warehouse tests")
{
    SECTION("Default constructor")
    {
        Warehouse w1;
        REQUIRE(w1.getCapacity() == 0);
    }

    SECTION("Constructor with parameters")
    {
        Warehouse w1(2);
        REQUIRE(w1.getCapacity() == 2);
    }

    SECTION("Copy constructor")
    {
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 2, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 2));
        REQUIRE(w1[0].setShelfCapacity(1, 3));
        REQUIRE(w1[1].setShelfCapacity(0, 4));
        REQUIRE(w1[1].setShelfCapacity(1, 5));

        REQUIRE(w1[0].addProduct(p1).index == 0);
        REQUIRE(w1[1].addProduct(p2).index == 0);

        Warehouse w2(w1);

        REQUIRE(w2.getCapacity() == 2);
        REQUIRE(w2[0].getCapacity() == 2);
        REQUIRE(w2[1].getCapacity() == 2);

        REQUIRE(w2[0][0].getCapacity() == 2);
        REQUIRE(w2[0][1].getCapacity() == 3);
        REQUIRE(w2[1][0].getCapacity() == 4);
        REQUIRE(w2[1][1].getCapacity() == 5);

        REQUIRE(w2[0][0][0] == p1);
        REQUIRE(w2[1][0][0] == p2);
    }

    SECTION("Operator =")
    {
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 2, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 2));
        REQUIRE(w1[0].setShelfCapacity(1, 3));
        REQUIRE(w1[1].setShelfCapacity(0, 4));
        REQUIRE(w1[1].setShelfCapacity(1, 5));

        REQUIRE(w1[0].addProduct(p1).index == 0);
        REQUIRE(w1[1].addProduct(p2).index == 0);

        Warehouse w2 = w1;

        REQUIRE(w2.getCapacity() == 2);
        REQUIRE(w2[0].getCapacity() == 2);
        REQUIRE(w2[1].getCapacity() == 2);

        REQUIRE(w2[0][0].getCapacity() == 2);
        REQUIRE(w2[0][1].getCapacity() == 3);
        REQUIRE(w2[1][0].getCapacity() == 4);
        REQUIRE(w2[1][1].getCapacity() == 5);

        REQUIRE(w2[0][0][0] == p1);
        REQUIRE(w2[1][0][0] == p2);
    }

    SECTION("Operator []")
    {
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 2, dummyDate1, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 2));
        REQUIRE(w1[0].setShelfCapacity(1, 3));
        REQUIRE(w1[1].setShelfCapacity(0, 4));
        REQUIRE(w1[1].setShelfCapacity(1, 5));

        REQUIRE(w1[0].addProduct(p1).index == 0);
        REQUIRE(w1[1].addProduct(p2).index == 0);

        REQUIRE(w1[0][0][0] == p1);
        REQUIRE(w1[1][0][0] == p2);
    }

    SECTION("Set section capacity")
    {
        Warehouse w1(3);

        REQUIRE(w1[0].getCapacity() == 0);
        REQUIRE(w1[1].getCapacity() == 0);
        REQUIRE(w1[2].getCapacity() == 0);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 3));
        REQUIRE(w1.setSectionCapacity(2, 4));
        REQUIRE(!w1.setSectionCapacity(3, 3));

        REQUIRE(w1[0].getCapacity() == 2);
        REQUIRE(w1[1].getCapacity() == 3);
        REQUIRE(w1[2].getCapacity() == 4);
    }

    SECTION("Operator <<")
    {
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment2, 2, dummyDate2, dummyDate2, dummyPlacement1);
        Product p3(dummyName2, dummyManufacturer3, dummyComment1, 6, dummyDate2, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 1));
        REQUIRE(w1[0].setShelfCapacity(1, 1));
        REQUIRE(w1[1].setShelfCapacity(0, 2));

        REQUIRE(w1.addProduct(p2, 1, 0, 0));
        REQUIRE(w1.restock(p3));
        REQUIRE(w1[1][0][1] == p3);

        const char* answer = "NAME: dummy Name2\n"
        "DETAILS:\n"
        "COUNT: 2\n"
        "MANUFACTURER: dummy Manufacturer2\n"
        "INDEX: 0 SHELF: 0 SECTION: 1\n"
        "EXP: 1/2/2021 STOCK: 1/2/2021\n"
        "NOTES: This is another dummy comment\n"
        "NAME: dummy Name2\n"
        "DETAILS:\n"
        "COUNT: 6\n"
        "MANUFACTURER: dummy Manufacturer3\n"
        "INDEX: 1 SHELF: 0 SECTION: 1\n"
        "EXP: 1/2/2021 STOCK: 1/2/2021\n"
        "NOTES: This is a dummy comment\n"
        "\n----- COUNT: 8\n";

        std::stringstream out;
        out << w1;
        REQUIRE(out.str() == answer);
    }

    SECTION("Find equal")
    {
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 2, dummyDate2, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 2));
        REQUIRE(w1[0].setShelfCapacity(1, 3));
        REQUIRE(w1[1].setShelfCapacity(0, 4));
        REQUIRE(w1[1].setShelfCapacity(1, 5));

        REQUIRE(!w1.findEqual(dummyName1, dummyDate1));
        REQUIRE(!w1.findEqual(dummyName2, dummyDate2));

        REQUIRE(w1[0].addProduct(p1).index == 0);
        REQUIRE(w1[1].addProduct(p2).index == 0);

        REQUIRE(!w1.findEqual(dummyName1, dummyDate2));
        REQUIRE(!w1.findEqual(dummyName2, dummyDate1));

        REQUIRE(w1.findEqual(dummyName1, dummyDate1));
        REQUIRE(w1.findEqual(dummyName2, dummyDate2));
    }

    SECTION("Find all by name")
    {
        DynArray<Product *> result(5);
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 2, dummyDate2, dummyDate2, dummyPlacement1);
        Product p3(dummyName2, dummyManufacturer2, dummyComment1, 2, dummyDate2, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 2));
        REQUIRE(w1[0].setShelfCapacity(1, 3));
        REQUIRE(w1[1].setShelfCapacity(0, 4));
        REQUIRE(w1[1].setShelfCapacity(1, 5));

        w1.findAllByName(dummyName1, result);
        REQUIRE(result.size() == 0);

        w1.findAllByName(dummyName2, result);
        REQUIRE(result.size() == 0);

        REQUIRE(w1[0].addProduct(p1).index == 0);
        REQUIRE(w1[1].addProduct(p2).index == 0);

        w1.findAllByName(dummyName1, result);
        REQUIRE(result.size() == 1);

        w1.findAllByName(dummyName2, result);
        REQUIRE(result.size() == 2);

        REQUIRE(w1[0].addProduct(p3).index == 1);

        w1.findAllByName(dummyName2, result);
        REQUIRE(result.size() == 4);
    }

    SECTION("Find all by date")
    {
        DynArray<Product *> result(5);
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment1, 2, dummyDate2, dummyDate2, dummyPlacement1);
        Product p3(dummyName2, dummyManufacturer2, dummyComment1, 2, dummyDate2, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 2));
        REQUIRE(w1[0].setShelfCapacity(1, 3));
        REQUIRE(w1[1].setShelfCapacity(0, 4));
        REQUIRE(w1[1].setShelfCapacity(1, 5));

        w1.findAllByDate(dummyDate1, result);
        REQUIRE(result.size() == 0);

        w1.findAllByDate(dummyDate2, result);
        REQUIRE(result.size() == 0);

        REQUIRE(w1[0].addProduct(p1).index == 0);
        REQUIRE(w1[1].addProduct(p2).index == 0);

        w1.findAllByDate(dummyDate1, result);
        REQUIRE(result.size() == 1);

        w1.findAllByDate(dummyDate2, result);
        REQUIRE(result.size() == 3);

        REQUIRE(w1[0].addProduct(p3).index == 1);

        w1.findAllByDate(dummyDate2, result);
        REQUIRE(result.size() == 6);
    }

    SECTION("Remove product")
    {
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 3, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment2, 5, dummyDate2, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 1));
        REQUIRE(w1[0].setShelfCapacity(1, 1));
        REQUIRE(w1[1].setShelfCapacity(0, 2));

        REQUIRE(w1.addProduct(p1, 1, 0, 0));
        REQUIRE(w1.restock(p2));
        REQUIRE(w1[0][0][0] == p2);

        REQUIRE(!w1.removeProduct(5, 0, 0, -1));
        REQUIRE(!w1.removeProduct(0, 5, 0, -1));
        REQUIRE(!w1.removeProduct(0, 0, 5, -1));

        Product p3(p1), p4(p1);
        p3.setQuantity(2);
        p4.setQuantity(1);
        Product* ptr = w1.removeProduct(1, 0, 0, 1);
        REQUIRE(*ptr == p1);
        delete ptr;
        REQUIRE(w1[1][0][0] == p4);

        ptr = w1.removeProduct(0, 0, 0, -1);
        REQUIRE(*ptr == p2);
        delete ptr;
        REQUIRE(w1[0][0][0].getQuantity() == 0);
    }

    SECTION("Restock product")
    {
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment2, 2, dummyDate2, dummyDate2, dummyPlacement1);
        Product p3(dummyName2, dummyManufacturer3, dummyComment1, 6, dummyDate2, dummyDate2, dummyPlacement1);
        Product p4(dummyName3, dummyManufacturer3, dummyComment3, 2, dummyDate2, dummyDate1, dummyPlacement1);
        Product p5(dummyName3, dummyManufacturer1, dummyComment2, 5, dummyDate3, dummyDate3, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 1));
        REQUIRE(w1[0].setShelfCapacity(1, 1));
        REQUIRE(w1[1].setShelfCapacity(0, 2));

        REQUIRE(w1.addProduct(p2, 1, 0, 0));
        REQUIRE(w1.restock(p3));
        REQUIRE(w1[1][0][1] == p3);
        REQUIRE(w1[1][0][1].getIndex() == 1);
        REQUIRE(w1[1][0][1].getShelf() == 0);
        REQUIRE(w1[1][0][1].getSection() == 1);

        REQUIRE(w1.restock(p1));
        REQUIRE(w1[0][0][0] == p1);
        REQUIRE(w1[0][0][0].getIndex() == 0);
        REQUIRE(w1[0][0][0].getShelf() == 0);
        REQUIRE(w1[0][0][0].getSection() == 0);

        REQUIRE(w1.restock(p4));
        REQUIRE(w1[0][1][0] == p4);
        REQUIRE(w1[0][1][0].getIndex() == 0);
        REQUIRE(w1[0][1][0].getShelf() == 1);
        REQUIRE(w1[0][1][0].getSection() == 0);

        REQUIRE(!w1.restock(p5));
        REQUIRE(!w1.findEqual(dummyName3, dummyDate3));
    }

    SECTION("Cleanup")
    {
        Warehouse w1(2);
        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
        Product p2(dummyName2, dummyManufacturer2, dummyComment2, 2, dummyDate2, dummyDate2, dummyPlacement1);
        Product p3(dummyName3, dummyManufacturer3, dummyComment3, 6, dummyDate3, dummyDate2, dummyPlacement1);

        REQUIRE(w1.setSectionCapacity(0, 2));
        REQUIRE(w1.setSectionCapacity(1, 2));

        REQUIRE(w1[0].setShelfCapacity(0, 1));
        REQUIRE(w1[0].setShelfCapacity(1, 1));
        REQUIRE(w1[1].setShelfCapacity(0, 2));

        REQUIRE(w1.restock(p1));
        REQUIRE(w1.restock(p2));
        REQUIRE(w1.restock(p3));

        const char* answer = "NAME: dummy Name1\n"
        "DETAILS:\n"
        "COUNT: 1\n"
        "MANUFACTURER: dummy Manufacturer1\n"
        "INDEX: 0 SHELF: 0 SECTION: 0\n"
        "EXP: 12/3/2004 STOCK: 1/2/2021\n"
        "NOTES: This is a dummy comment\n"
        "NAME: dummy Name3\n"
        "DETAILS:\n"
        "COUNT: 6\n"
        "MANUFACTURER: dummy Manufacturer3\n"
        "INDEX: 0 SHELF: 0 SECTION: 1\n"
        "EXP: 26/4/2020 STOCK: 1/2/2021\n"
        "NOTES: This is dummy comment 3\n";

        std::stringstream out;
        w1.cleanup(out, dummyDate3);
        REQUIRE(out.str() == answer);
    }

    SECTION("Take out product")
    {
//        Warehouse w1(2);
//        Product p1(dummyName1, dummyManufacturer1, dummyComment1, 1, dummyDate1, dummyDate2, dummyPlacement1);
//        Product p2(dummyName2, dummyManufacturer2, dummyComment2, 2, dummyDate2, dummyDate2, dummyPlacement1);
//        Product p3(dummyName3, dummyManufacturer3, dummyComment3, 6, dummyDate3, dummyDate2, dummyPlacement1);
//
//        REQUIRE(w1.setSectionCapacity(0, 2));
//        REQUIRE(w1.setSectionCapacity(1, 2));
//
//        REQUIRE(w1[0].setShelfCapacity(0, 1));
//        REQUIRE(w1[0].setShelfCapacity(1, 1));
//        REQUIRE(w1[1].setShelfCapacity(0, 2));
//
//        REQUIRE(w1.restock(p1));
//        REQUIRE(w1.restock(p2));
//        REQUIRE(w1.restock(p3));
//
//        std::stringstream inY("y");
//        std::stringstream inN("n");
//        std::stringstream out;
//
//        REQUIRE(w1.findEqual(dummyName1, dummyDate1));
//        REQUIRE(w1.takeOutProduct(out, inY, dummyName1, 2));
//        REQUIRE(!w1.findEqual(dummyName1, dummyDate1));
//
//        REQUIRE(w1.findEqual(dummyName2, dummyDate2));
//        REQUIRE(!w1.takeOutProduct(out, inN, dummyName2, 4));
//        REQUIRE(w1.findEqual(dummyName2, dummyDate2));
//
//        REQUIRE(w1.findEqual(dummyName3, dummyDate3));
//        REQUIRE(w1.takeOutProduct(out, inY, dummyName3, 2));
//        REQUIRE(w1.findEqual(dummyName3, dummyDate3));
//        REQUIRE(w1.takeOutProduct(out, inY, dummyName3, 4));
//        REQUIRE(!w1.findEqual(dummyName3, dummyDate3));
    }
}
