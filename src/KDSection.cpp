#include "KDSection.h"
#include <boost/regex.hpp>
#include "DayType.h"

void KDSection::_processLine(const std::string& line) {
    static const boost::u32regex expDate = boost::make_u32regex(R"((?<date>\d{4}-\d{2}-\d{2})\s+\d+$)");
    static const boost::u32regex expLine =  boost::make_u32regex(R"((?<line>\w{1,3})\s+ (?<day_type>\w{2}))");
    static bool active = false; // That's a functional programming inspired trick - no need to add a member to the class

    boost::smatch match;
    if(active && boost::u32regex_search(line, match, expLine)){
        manager->setDayType(match["line"], match["day_type"]);
    } else if (boost::u32regex_search(line, match, expDate)) {
        active = match["date"] == manager->getScheduleDate();
    }
}
