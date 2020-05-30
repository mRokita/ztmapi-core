#include "ZASection.h"

/**
 * Extract stop groups from the ZA section.
 * Groups in the regular expresion: [id, group name, region id, region name]
 * @param line A string like this one: "6635   Dziekanów Polski Wschód,            DP  DZIEKANÓW POLSKI"
 */
void ZASection::_processLine(const std::string &line) {
    static const boost::u32regex expStopGroup = boost::make_u32regex(
            R"((?<id>\d{4})\s+(?<group_name>[\d[:L*:]].+?),?\s+(?<region_id>[\d[:Lu:]-]{2})\s+(?<region_name>[[:Lu:]].+?)$)"
    );

    boost::smatch match;
    if (boost::u32regex_search(line, match, expStopGroup)) {
        manager->stopGroups.emplace_back(match["id"], match["group_name"], match["region_id"], match["region_name"]);
    } else {
        throw CouldNotParseLineException(line);
    }
}