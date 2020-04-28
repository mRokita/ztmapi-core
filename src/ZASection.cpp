#include "ZASection.h"

/**
 * Extract stop groups from the ZA section.
 * Groups in the regular expresion: [id, group nme, region id, region name]
 * @param line A string like this one: "6635   Dziekanów Polski Wschód,            DP  DZIEKANÓW POLSKI"
 */
void ZASection::_processLine(const std::string &line) {
    static const boost::u32regex expStopGroup = boost::make_u32regex("(\\d{4})\\s+([\\d[:L*:]].+?),?\\s+([\\d[:L*:]-]{2})\\s+([[:L*:]].+)\r");

    boost::smatch match;
    if (boost::u32regex_search(line, match, expStopGroup)) {
        manager->stopGroups.emplace_back(match[1], match[2], match[3], match[4]);
    } else {
        throw CouldNotParseLineException(line);
    }
}