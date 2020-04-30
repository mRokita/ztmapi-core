#ifndef ZTMAPI_CORE_DEPARTURE_H
#define ZTMAPI_CORE_DEPARTURE_H

#include <boost/lexical_cast.hpp>


class Departure {
public:
    std::string const courseId;
    int stopId;
    short departureHour;
    short departureMinute;
    bool isCourseStart;
    bool isPublic;

    Departure(
            const std::string &courseId,
            const std::string &stopId,
            const std::string &departureHour,
            const std::string &departureMinute,
            const std::string &isCourseStart,
            const std::string &isPublic)
            :
            courseId(std::move(courseId)),
            stopId(std::stoi(stopId)),
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
