#ifndef KODU2
#define KODU2

#include <string>
#include <algorithm>

#define DEBUG 0
#define WRONG_FORMAT -1

/** timeString full format is expected to be h:mm:ss.xxx or h:mm:ss,xxx
 * h, mm and xxx can be excluded, first part of string can be of any length, the rest 2 (except milliseconds for 3)
 */

typedef struct racer_t {
    std::string name, time;
} Racer;

bool splitTimeString(std::string timeString, std::vector<std::string>& components);

bool checktime(std::string timeString);

double ctime(std::string timeString, char unit = 's');

std::string stime(const double seconds);

#endif
