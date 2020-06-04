#include "KDSection.h"
#include "schema/DayType.h"

void KDSection::_processLine(const std::string& line) {
    static const boost::u32regex expDate = boost::make_u32regex(R"(^\s+(?<date>\d{4}-\d{2}-\d{2})\s+\d+$)"); /**< Wyrażenie naturalne do pobierania daty z sekcji KD */
    static const boost::u32regex expLine =  boost::make_u32regex(R"(^\s+(?<line>[\w-]{1,3})\s+(?<day_type>\w{2})$)"); /**< Wyrażenie naturalne do pobierania typu dnia z sekcji KD */
    static bool active = false; 

    boost::smatch match;
    if(active && boost::u32regex_search(line, match, expLine)){
        manager->setDayType(match["line"], match["day_type"]);
    } else if (boost::u32regex_search(line, match, expDate)) {
        active = match["date"] == manager->getScheduleDate();
    } else if (active) {
        throw CouldNotParseLineException(line);
    }
}
