#ifndef ZTMAPI_CORE_DEPARTURE_H
#define ZTMAPI_CORE_DEPARTURE_H

#include <boost/lexical_cast.hpp>


class Departure {
public:
    std::string const lineId;
    std::string const courseId;
    std::string const trackId;
    short courseStartHour;
    short courseStartMinute;
    int stopId;
    std::string const dayType;
    short departureHour;
    short departureMinute;
    bool isCourseStart;
    bool isPublic;

    Departure(
            std::string lineId,
            std::string courseId,
            std::string trackId,
            const std::string &courseStartHour,
            const std::string &courseStartMinute,
            const std::string &stopId,
            std::string dayType,
            const std::string &departureHour,
            const std::string &departureMinute,
            const std::string &isCourseStart,
            const std::string &isPublic)
            :
            lineId(std::move(lineId)),
            courseId(std::move(courseId)),
            trackId(std::move(trackId)),
            courseStartHour(boost::lexical_cast<short>(courseStartHour)),
            courseStartMinute(boost::lexical_cast<short>(courseStartMinute)),
            stopId(std::stoi(stopId)),
            dayType(std::move(dayType)),
            departureHour(boost::lexical_cast<short>(departureHour)),
            departureMinute(boost::lexical_cast<short>(departureMinute)),
            isCourseStart(isCourseStart == "P"),
            isPublic(isPublic != "B") {}

    Departure() = default;

    Departure &operator=(const Departure &d) {
        return *this; // make immutable for Python TODO: Raise a Python Exception
    }

    bool operator==(const Departure &d) {
        return d.courseId == this->courseId
               && d.departureHour == this->departureHour
               && d.departureMinute == this->departureMinute;
    }
};


#endif //ZTMAPI_CORE_DEPARTURE_H
