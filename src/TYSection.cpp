#include "TYSection.h"
#include <boost/regex.hpp>
#include "schema/DayType.h"

void TYSection::_processLine(const std::string& line) {
    boost::u32regex expDayType = boost::make_u32regex("(\\w{2})\\s+(\\S.+?)\r");
    boost::smatch match;
    boost::u32regex_search(line, match, expDayType);
    manager->dayTypes.emplace_back(match[1], match[2]);
}
