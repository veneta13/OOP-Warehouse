#ifndef __DATE
#define __DATE

#include <iostream>

struct Date {
    int day;
    int month;
    int year;

    Date();
    Date(int day, int month, int year);
    Date(Date const& other);
    Date& operator=(Date const& other);
    ~Date();

    bool operator>(Date const& other) const;
    bool operator==(Date const& other) const;
    bool operator!=(Date const& other) const;
    bool operator<(Date const& other) const;
    bool operator<=(Date const& other) const;
    bool operator>=(Date const& other) const;
    bool isValid() const;

    friend std::ostream& operator<<(std::ostream& out, Date const& d);

private:
    bool valid;
    bool validate() const;
};

#endif
