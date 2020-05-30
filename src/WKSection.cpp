#include "WKSection.h"
#include "./schema/Departure.h"

void WKSection::_processLine(const std::string &line) {
    static const boost::u32regex expDeparture = boost::make_u32regex(
            R"((?<course_id>(?<track_id>[\w\d-]+)\/\w+\/(?<course_start_hour>\d{2})\.(?<course_start_minute>\d{2})_*)\s+(?<stop_id>\d{6})\s+(?<day_type>\w{2})\s+(?<departure_hour>\d{1,2})\.(?<departure_minute>\d{2})\s*(?<is_course_start>P?)\s*(?<is_not_public>B)?\s*$)"
    );
    static int departureOrder = 0;
    static std::string lastCourseId = "__course__";
    std::string currentLine = getParent()->getCurrentLine();
    if (!manager->isLineActive(currentLine)) return; // Line not active, no need to parse
    boost::smatch match;

    if (boost::u32regex_search(line, match, expDeparture)) {
        if(manager->getDayType(currentLine) != match["day_type"]){
            return;  // This course is not active today
        }
        std::string courseId;
        courseId.append(manager->getScheduleDate());
        courseId.append("_");
        courseId.append(currentLine);
        courseId.append("_");
        courseId.append(match["course_id"]);
        if(courseId != lastCourseId){
            departureOrder = 0;
            lastCourseId = courseId;
        } else {
            departureOrder ++;
        }

        if (!manager->isCourseRegistered(courseId)) {
            manager->courses.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(courseId),
                    std::forward_as_tuple(
                            courseId,
                            currentLine,
                            match["track_id"],
                            match["course_start_hour"],
                            match["course_start_minute"],
                            match["day_type"]
                    )
            );
        }

        std::string departureId;
        departureId.append(courseId);
        departureId.append(match["stop_id"]);
        departureId.append(match["departure_hour"]);
        departureId.append(match["departure_minute"]);
        departureId.append(std::to_string(departureOrder));

        manager->departures.emplace_back(
                departureId,
                courseId,
                match["stop_id"],
                match["departure_hour"],
                match["departure_minute"], match["is_course_start"],
                match["is_not_public"],
                departureOrder
        );
    } else {
        throw CouldNotParseLineException(line);
    }
}
