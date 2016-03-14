#ifndef KODU2
#define KODU2

#include <string>
#include <algorithm>

#define DEBUG 0

bool splitTimeString(std::string timeString, std::vector<std::string>& components);

bool checktime(std::string timeString);

double ctime(std::string timeString, char unit = 's');

std::string stime(double seconds);

#endif
