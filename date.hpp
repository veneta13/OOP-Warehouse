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

    bool operator>(Date const& other) const;
    bool operator==(Date const& other) const;
    bool operator!=(Date const& other) const;
    bool operator<(Date const& other) const;
    bool operator<=(Date const& other) const;
    bool operator>=(Date const& other) const;
    bool isValid() const;

private:
    bool valid;
    bool validate() const;
};

#endif
