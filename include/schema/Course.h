#ifndef ZTMAPI_CORE_COURSE_H
#define ZTMAPI_CORE_COURSE_H

#include <boost/lexical_cast.hpp>

class Course {
public:

    std::string const id;
    std::string const lineId;
    std::string const trackId;
    short startHour;
    short startMinute;
    std::string const dayType;

    Course(std::string id,
           std::string lineId,
           std::string trackId,
           const std::string &startHour,
           const std::string &startMinute,
           std::string dayType)
            :
            id(std::move(id)),
            lineId(std::move(lineId)),
            trackId(std::move(trackId)),
            startHour(boost::lexical_cast<short>(startHour)),
            startMinute(boost::lexical_cast<short>(startMinute)),
            dayType(std::move(dayType)) {}

    Course() = default;

    Course &operator=(const Course &c) {
        return *this; // make immutable for Python TODO: Raise a Python Exception
    }

    bool operator==(const Course &c) {
        return c.id == this->id;
    }
};


#endif //ZTMAPI_CORE_COURSE_H
