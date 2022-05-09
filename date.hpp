#ifndef __DATE
#define __DATE

struct Date {
    int day;
    int month;
    int year;

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

private:
    bool valid;
    bool validate();
};

#endif
