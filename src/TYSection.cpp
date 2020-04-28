#include "TYSection.h"
#include <boost/regex.hpp>
#include "DayType.h"

void TYSection::_processLine(const std::string& line) {
    static const boost::regex expDayType("(\\w{2})\\s+(\\S.+?)\r");
    boost::smatch match;
    boost::regex_search(line, match, expDayType);
    manager->dayTypes.emplace_back(match[1], match[2]);
}
