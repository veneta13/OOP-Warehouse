#include "date.hpp"

Date::Date() {
    day = 0;
    month = 0;
    year = 0;
    valid = false;
}


Date::Date(int day, int month, int year) : day(day), month(month), year(year) {
    valid = validate();
}


Date::Date(Date const& other) {
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
    valid = validate();
}


Date& Date::operator=(Date const& other) {
    if (this != &other) {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
        valid = validate();
    }
    return *this;
}


Date::~Date() {
    day = 0;
    month = 0;
    year = 0;
    valid = false;
}


bool Date::validate() {
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
        else {
            return true;
        }
    }

    if (day > 31) {
        return false;
    }
    return true;
}


bool Date::operator>(Date const& other) {
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


bool Date::operator==(Date const& other) {
    if (this->year == other.year && this->month == other.month && this->day == other.day) {
        return true;
    }
    else {
        return false;
    }
}


bool Date::operator<(Date const& other) {
    if (*this == other || *this > other) {
        return false;
    }
    else {
        return true;
    }
}


bool Date::operator>=(Date const& other) {
    if (*this == other || *this > other) {
        return true;
    }
    else {
        return false;
    }
}


bool Date::operator<=(Date const& other) {
    if (*this == other || *this < other) {
        return true;
    }
    else {
        return false;
    }
}


bool Date::isValid() {
    return valid;
}
