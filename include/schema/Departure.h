#ifndef ZTMAPI_CORE_DEPARTURE_H
#define ZTMAPI_CORE_DEPARTURE_H
#include <boost/lexical_cast.hpp>


class Departure {
public:
    std::string const courseId;
    std::string const trackId;
    short const courseStartHour;
    short const courseStartMinute;
    int const stopId;
    std::string const dayType;
    short const departureHour;
    short const departureMinute;
    bool isCourseStart;
    bool isPublic;
    Departure(std::string courseId,
              std::string trackId,
              const std::string& courseStartHour,
              const std::string& courseStartMinute,
              const std::string& stopId,
              std::string dayType,
              const std::string& departureHour,
              const std::string& departureMinute,
              const std::string& isCourseStart,
              const std::string& isPublic)
              :
              courseId(std::move(courseId)),
              trackId(std::move(trackId)),
              courseStartHour(boost::lexical_cast<short>(courseStartHour)),
              courseStartMinute(boost::lexical_cast<short>(courseStartMinute)),
              stopId(std::stoi(stopId)),
              dayType(std::move(dayType)),
              departureHour(boost::lexical_cast<short>(departureHour)),
              departureMinute(boost::lexical_cast<short>(departureMinute)),
              isCourseStart(isCourseStart == "P"),
              isPublic(isPublic != "B"){}
};


#endif //ZTMAPI_CORE_DEPARTURE_H
