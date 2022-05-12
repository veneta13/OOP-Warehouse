#include "date.hpp"

/// Default constructor
Date::Date() {
    day = 0;
    month = 0;
    year = 0;
    valid = false;
}


/// Constructor with parameters
/// \param day the day
/// \param month the month
/// \param year the year
Date::Date(int day, int month, int year) : day(day), month(month), year(year) {
    valid = validate();
}


/// Copy constructor
/// \param other date to copy
Date::Date(Date const& other) {
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
    valid = validate();
}


/// Copy assignment operator
/// \param other date to copy
/// \return the updated date
Date& Date::operator=(Date const& other) {
    if (this != &other) {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
        valid = validate();
    }
    return *this;
}


/// Destructor
Date::~Date() {
    day = 0;
    month = 0;
    year = 0;
    valid = false;
}


/// Validate the date
/// \return if the date is valid
bool Date::validate() const {
    if (day < 1 || month < 1 || day > 31 || month > 12 || year < 0) {
        return false;
    }

    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) {
                return false;
            }
            return true;
        }
        if (day > 28) {
            return false;
        }
        return true;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false;
        }
        return true;
    }

    if (day > 31) {
        return false;
    }
    return true;
}


/// Compare dates with greater than operator
/// \param other date to compare the current date to
/// \return if the current date is after the other
bool Date::operator>(Date const& other) const {
    if (this->year > other.year) {
        return true;
    }
    if (this->year < other.year) {
        return false;
    }
    if (this->month > other.month) {
        return true;
    }
    if (this->month < other.month) {
        return false;
    }
    if (this->day > other.day) {
        return true;
    }
    if (this->day < other.day) {
        return false;
    }
    return false;
}


/// Compare dates with equality operator
/// \param other date to compare the current date to
/// \return if the current date is the same as the other
bool Date::operator==(Date const& other) const {
    if (this->year == other.year && this->month == other.month && this->day == other.day) {
        return true;
    }
    return false;
}


/// Compare dates with inequality operator
/// \param other date to compare the current date to
/// \return if the current date is not the same as the other
bool Date::operator!=(Date const& other) const {
    return !operator==(other);
}


/// Compare dates with less than operator
/// \param other date to compare the current date to
/// \return if the current date is before the other
bool Date::operator<(Date const& other) const {
    if (*this == other || *this > other) {
        return false;
    }
    return true;
}


/// Compare dates with greater than or equal operator
/// \param other date to compare the current date to
/// \return if the current date is after or the same as the other
bool Date::operator>=(Date const& other) const {
    if (*this == other || *this > other) {
        return true;
    }
    return false;
}


/// Compare dates with less than or equal operator
/// \param other date to compare the current date to
/// \return if the current date is before or the same as the other
bool Date::operator<=(Date const& other) const {
    if (*this == other || *this < other) {
        return true;
    }
    return false;
}


/// Getter for valid
/// \return the value of valid
bool Date::isValid() const {
    return valid;
}


/// Stream insertion operator
/// \param out output stream
/// \param d date
/// \return the stream with date put in
std::ostream& operator<<(std::ostream& out, Date const& d) {
    out << d.day << "/" << d.month << "/" << d.year;
    return out;
}
