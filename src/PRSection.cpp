#include "PRSection.h"

/**
 * Extract stops from the ZP section.
 * Groups in the regular expresion: [id, group nme, region id, region name]
 * @param line A string like this one: "6635   Dziekanów Polski Wschód,            DP  DZIEKANÓW POLSKI"
 */
void PRSection::_processLine(const std::string &line) {
    // TODO: Move stops to the PR subsection
    static const boost::u32regex expStop = boost::make_u32regex(
            R"((?<id>(?<group_id>\d{4})(?<id_in_group>\d{2}))\s+(?<num_lines>\d+)\s+Ul\.\/Pl\.\:\s+(?<street>[[:L*:]\d].+?)\,?\s+Kier\.\:\s+(?<direction>[[:L*:]\d]?.+?)\,?\s+Y=\s*(?<lat>[\d.]*)[yY.]*\s+X=\s*(?<lon>[\d.]*)[xX.]*\s+ Pu=(?<pu>\d*)\??$)"
    );
    static const boost::u32regex expLines = boost::make_u32regex(
            R"(L\s+(?<num_lines>\d+)\s+-\s+(?<type>.+?):\s+(?<lines>(?:[\w-]{1,3}\^?\s*?)+)\s+$)"
    );
    boost::smatch match;
    if (boost::u32regex_search(line, match, expLines)) {
        // Not used yet
    } else if (boost::u32regex_search(line, match, expStop)) {
        this->manager->stops.emplace_back(match["id"], match["group_id"], match["id_in_group"], match["street"],
                match["direction"], match["lat"], match["lon"]);
    } else {
        throw CouldNotParseLineException(line);
    }
}