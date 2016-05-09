#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

#include "Saade.hpp"
#include "../kodu2/kodu2.h"

std::pair<std::string, std::string> parseShow(std::ifstream& input) {
    char time[32], show[1024];
    input.get(time, 32, ' ');
    input.ignore(1);
    input.get(show, 1024);
    #ifdef DEBUG
        std::cout << time << ' ' << show << std::endl;
    #endif
    input.ignore(1);
    return std::pair<std::string, std::string>(time, show);
}

std::vector<Saade*>::iterator findMatch(std::vector<Saade*>& shows, std::string name) {
    return std::find_if(shows.begin(), shows.end(), [&name](Saade* show) {
        return show->getName() == name;
    });
}

Saade* getShow(std::pair<std::string, std::string> showPair, std::vector<Saade*>& shows, std::string date) {
    auto show = new Saade(showPair.second, date);
    if (showPair.second.back() == '*') {
        showPair.second.pop_back();
        auto match = findMatch(shows, showPair.second);
        #ifdef DEBUG
            std::cout << "kordus " << showPair.second << std::endl;
        #endif
        if (match != shows.end()) {
            show = new Kordussaade((*match)->getName(), date, (*match)->getRunTime());
        } else {
            show = new Kordussaade(showPair.second, date);
        }
    }
    return show;
}

void parseShowlist(std::ifstream& input, std::vector<Saade*>& shows) {
    auto datePair = parseShow(input);
    auto date = datePair.first + " " + datePair.second;
    auto prevShow = parseShow(input);
    decltype(prevShow) nextShow;

    while(std::isdigit(input.peek())) {
        nextShow = parseShow(input);
        auto show = getShow(prevShow, shows, date);
        show->setRunTime(prevShow.first, nextShow.first);
        shows.push_back(show);
        prevShow = nextShow;
    }

    auto oldDate = date;
    datePair = parseShow(input);
    date = datePair.first + " " + datePair.second;

    nextShow = parseShow(input);
    auto show = getShow(prevShow, shows, oldDate);
    show->setRunTime(prevShow.first, nextShow.first, true);
    shows.push_back(show);

    show = getShow(nextShow, shows, date);
    show->setRunTime(nextShow.first, nextShow.first);
    shows.push_back(show);
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cout << "Need text file as argument" << std::endl;
        return 1;
    }
    std::ifstream input(argv[1]);
    std::vector<Saade*> shows;
    parseShowlist(input, shows);

    #ifdef DEBUG
        auto serv = new Saade("test", "date");
        serv->setRunTime("00:05", "01:00");
        std::cout << serv->getName() << " " << serv->getDate() << " " << serv->getLength() << std::endl;
    #endif

    double allShowsLength = 0, repeatingShowsLength = 0, maxRepeatingShow = 0;
    for (auto iter = shows.begin(); iter != shows.end(); iter++) {
        std::cout << (*iter)->getStartTime() << " " << (*iter)->getName() << " -- " << (*iter)->getLength() << " min" << std::endl;
        allShowsLength += (*iter)->getLength();
        if ((*iter)->isRepeatingShow()) {
            auto showLength = (*iter)->getRunTime().second;
            repeatingShowsLength += showLength;
            if (showLength > maxRepeatingShow) {
                maxRepeatingShow = showLength;
            }
        }

    }
    std::cout << std::endl << "Kõikide saadete kogupikkus (min):\t" << allShowsLength << std::endl;
    std::cout << "Kordussaadete kogupikkus (min):\t\t" << repeatingShowsLength << std::endl;
    std::cout << "Max kordussaate pikkus (min):\t\t" << maxRepeatingShow << std::endl;
    return 0;
}
