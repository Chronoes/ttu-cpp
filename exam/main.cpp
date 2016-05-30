#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <ctime>
#include <cmath>

using stringPair = std::pair<std::string, std::string>;

class Trip {
protected:
    stringPair times;
    stringPair stops;
    std::string transporter;
public:
    Trip(stringPair times, std::vector<std::string> stopList);\
    double getTravelTime();
    void setTransporter(std::string name);
    std::string getTransporter();
    stringPair getTimes();
    virtual std::string toString();
};

class MultiStopTrip : public Trip {
private:
    std::vector<std::string> intermediateStops;
public:
    MultiStopTrip(stringPair times, std::vector<std::string> stopList);
    std::string toString() override;
};

int ctime(std::string time) {
    int hour = std::atoi(time.substr(0, 2).c_str());
    int minutes = std::atoi(time.substr(3, 2).c_str());
    return hour * 60 + minutes;
}

std::string stime(int time) {
    char result[128];
    std::sprintf(result, "%02d:%02d", (time / 60), (time % 60));
    return result;
}

Trip::Trip(stringPair _times, std::vector<std::string> stopList) : times(_times) {
    stops.first = stopList.front();
    stops.second = stopList.back();
}

void Trip::setTransporter(std::string name) {
    transporter = name;
}

std::string Trip::getTransporter() {
    return transporter;
}

stringPair Trip::getTimes() {
    return times;
}

double Trip::getTravelTime() {
    double start = ctime(times.first), end = ctime(times.second);
    if (end < start) {
        end += 24 * 60;
    }
    return end - start;
}

std::string Trip::toString() {
    return "Väljumisaeg " + times.first +
        " liinil " + stops.first + " - " + stops.second +
        ", sõiduaeg " + stime(getTravelTime()) +
        ", vedaja " + transporter;
}

MultiStopTrip::MultiStopTrip(stringPair times, std::vector<std::string> stopList) : Trip(times, stopList) {
    auto iter = stopList.cbegin();
    iter++;
    auto end = stopList.cend();
    end--;
    while (iter != end) {
        intermediateStops.push_back(*iter);
        iter++;
    }
}

std::string MultiStopTrip::toString() {
    auto iter = intermediateStops.begin();
    std::string allStops(*iter);
    iter++;
    for (; iter != intermediateStops.end(); iter++) {
        allStops += ", " + *iter;
    }
    return Trip::toString() + ", vahepeatused: " + allStops;
}

void parseList(std::string input, std::vector<std::string>& output) {
    std::string tmp("");
    int delim = 0;
    for (auto iter = input.cbegin(); iter != input.cend(); iter++) {
        if (*iter == ' ' || (delim == 1 && *iter == '-')) {
            delim += 1;
            continue;
        }
        if (delim == 3) {
            delim = 0;
            output.push_back(tmp);
            tmp.clear();
        }

        tmp += *iter;
    }
    output.push_back(tmp);
}

int main(int argc, char const *argv[]) {
    std::ifstream input("TallinnTartu.txt");
    std::vector<Trip*> trips;

    while (!input.eof()) {
        std::vector<std::string> stringList;

        char times[128];
        input.get(times, 127, '\t');
        input.ignore(1);
        #ifdef DEBUG
            std::cout << times << " ";
        #endif
        parseList(times, stringList);
        stringPair timePair(stringList.at(0), stringList.at(1));
        stringList.clear();

        char stops[2048];
        input.get(stops, 2047, '\t');
        input.ignore(1);
        #ifdef DEBUG
            std::cout << stops << " ";
        #endif
        parseList(stops, stringList);

        Trip* trip;
        if (stringList.size() > 2) {
            #ifdef DEBUG
                std::cout << "multistop trip" << " ";
            #endif
            trip = new MultiStopTrip(timePair, stringList);
        } else {
            #ifdef DEBUG
                std::cout << "regular trip" << " ";
            #endif
            trip = new Trip(timePair, stringList);
        }
        stringList.clear();

        char transporter[1024];
        input.get(transporter, 1023);
        input.ignore();
        #ifdef DEBUG
            std::cout << transporter << std::endl;
        #endif
        trip->setTransporter(transporter);

        trips.push_back(trip);
        if (input.peek() == EOF) {
            break;
        }
    }
    input.close();

    std::map<std::string, int> transporters;

    int minTravelTime = 24 * 60;

    for (auto iter = trips.begin(); iter != trips.end(); iter++) {
        auto travelTime = (*iter)->getTravelTime();
        if (travelTime < minTravelTime) {
            minTravelTime = travelTime;
        }
        if (transporters.count((*iter)->getTransporter())) {
            transporters[(*iter)->getTransporter()] += 1;
        } else {
            transporters[(*iter)->getTransporter()] = 1;
        }
        std::cout << (*iter)->toString() << std::endl;
    }

    std::vector<std::pair<std::string, int>> sortedTransporters;
    for (auto& pair : transporters) {
        sortedTransporters.push_back(pair);
    }

    auto cmp = [](std::pair<std::string, int> const & a, std::pair<std::string, int> const & b) {
        return a.second != b.second ? a.second > b.second : a.first < b.first;
    };
    std::sort(sortedTransporters.begin(), sortedTransporters.end(), cmp);

    std::cout << std::endl << "Vedajate väljumiste arv" << std::endl;
    for (auto& pair : sortedTransporters) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }


    std::cout << std::endl << "Lühim sõiduaeg: " << stime(minTravelTime) << std::endl;


    time_t timer;
    std::time(&timer);
    struct tm* now = localtime(&timer);
    int currentTime = now->tm_hour * 60 + now->tm_min;

    int nextExitTime = 24 * 60;
    auto iter = trips.begin();
    Trip* nextTrip = *iter;
    for (; iter != trips.end(); iter++) {
        auto exitTime = ctime((*iter)->getTimes().first);
        if (currentTime - exitTime < 0) {
            nextTrip = *iter;
            nextExitTime = exitTime;
            break;
        }
    }

    std::cout << std::endl << "Järgmine väljumine: " << std::fabs(currentTime - nextExitTime) << " minuti pärast" << std::endl;

    std::cout << nextTrip->toString() << std::endl;

    if (nextTrip->getTravelTime() > minTravelTime) {
        std::cout << "Järgmine lühim sõit:" << std::endl;
        int nextMin = 24 * 60;
        for (; iter != trips.end(); iter++) {
            auto currentTripTime = (*iter)->getTravelTime();
            if (currentTripTime - minTravelTime > 0 && currentTripTime - minTravelTime < nextMin) {
                nextMin = currentTripTime - minTravelTime;
                nextTrip = *iter;
            }
        }
        std::cout << nextTrip->toString() << std::endl;
    }


    return 0;
}
