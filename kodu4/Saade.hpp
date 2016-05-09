#ifdef TESTING
#define private public
#define protected public
#endif

#ifndef SAADE_H
#define SAADE_H

#include <string>
#include <map>

typedef std::pair<std::string, double> TimeRange;

class Saade {
private:
    std::string name;
    std::string date;
    TimeRange runTime;
protected:
    bool isRepeat = false;
public:
    Saade(std::string name, std::string date);

    void setName(std::string);
    void setDate(std::string);
    void setRunTime(std::string start, std::string end, bool nextDay = false);
    virtual const std::string getName();
    const std::string getDate();
    TimeRange getRunTime();
    const std::string getStartTime();
    double getLength();
    bool isRepeatingShow();

    virtual TimeRange getOriginalRunTime();
};

class Kordussaade : public Saade {
private:
    TimeRange originalRunTime;
public:
    Kordussaade(std::string name, std::string date);
    Kordussaade(std::string name, std::string date, TimeRange originalRunTime);
    const std::string getName() override;
    TimeRange getOriginalRunTime() override;
};

#endif
