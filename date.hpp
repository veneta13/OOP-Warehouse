#ifndef __DATE
#define __DATE

#include <iostream>

///\brief Represents a specific time by day, month and year
struct Date {
    /// The day of the month
    int day;

    /// The month
    int month;

    /// The year
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
