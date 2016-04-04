#ifdef TESTING
#define private public
#define protected public
#endif

#ifndef TEENUS_H
#define TEENUS_H

#include <string>
#include <map>

typedef enum Day {
    Invalid = -1,
    None = 0,
    Monday = 'E',
    Tuesday = 'T',
    Wednesday = 'K',
    Thursday = 'N',
    Friday = 'R',
    Saturday = 'L',
    Sunday = 'P'
} Day;

Day getDay(char);

std::pair<Day, Day> parseDayRange(std::string);

typedef struct TimeRange {
    double start, end;
} TimeRange;

class Teenus {
private:
    std::string name;
    std::map<Day, TimeRange> openTimes;
    void initOpenTimes(TimeRange);
    void setOpenTime(Day, TimeRange);
public:
    Teenus(std::string serviceName);
    Teenus(std::string, double, double);
    Teenus(std::string, std::string, double, double);

    const std::string nimi();
    void paev(char, double, double);
    double tunnid(void);
    bool onavatud(void);
    bool operator> (Teenus&);
};

#endif
