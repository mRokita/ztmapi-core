#include "WKSection.h"
#include "./schema/Departure.h"

void WKSection::_processLine(const std::string &line) {
    static const boost::u32regex expDeparture = boost::make_u32regex(
            R"((?<course_id>(?<track_id>[\w\d-]+)\/\w+\/(?<course_start_hour>\d{2})\.(?<course_start_minute>\d{2})_*)\s+(?<stop_id>\d{6})\s+(?<day_type>\w{2})\s+(?<departure_hour>\d{1,2})\.(?<departure_minute>\d{2})\s*(?<is_course_start>P?)\s*(?<is_not_public>B)?\s*$)"
    );
    std::string currentLine = getParent()->getCurrentLine();
    if (!manager->isLineActive(currentLine)) return; // Line not active, no need to parse
    boost::smatch match;
    if (boost::u32regex_search(line, match, expDeparture)) {
        manager->departures.emplace_back(
                currentLine,
                match["course_id"], match["track_id"],
                match["course_start_hour"], match["course_start_minute"],
                match["stop_id"], match["day_type"], match["departure_hour"],
                match["departure_minute"], match["is_course_start"],
                match["is_not_public"]
        );
    } else {
        throw CouldNotParseLineException(line);
    }
}
