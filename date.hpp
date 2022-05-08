#ifndef __DATE
#define __DATE

struct Date {
    int day;
    int month;
    int year;
    bool valid;

    bool validate();

    Date();
    Date(int day, int month, int year);
    Date(Date const& other);
    Date& operator=(Date const& other);
    ~Date();

    bool operator>(Date const& other);
    bool operator==(Date const& other);
    bool operator<(Date const& other);
    bool operator<=(Date const& other);
    bool operator>=(Date const& other);
    bool isValid();
};

#endif
