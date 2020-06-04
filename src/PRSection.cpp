//
// Autorzy:
// Michał Rokita, Adamski Maciej
//

#include "PRSection.h"

void PRSection::_processLine(const std::string &line) {
    static const boost::u32regex expStop = boost::make_u32regex(
            R"((?<id>(?<group_id>\d{4})(?<id_in_group>\d{2}))\s+(?<num_lines>\d+)\s+Ul\.\/Pl\.\:\s+(?<street>[[:L*:]\d].+?)\,?\s+Kier\.\:\s+(?<direction>[[:L*:]\d]?.+?)\,?\s+Y=\s*(?<lat>[\d.]*)[yY.]*\s+X=\s*(?<lon>[\d.]*)[xX.]*\s+ Pu=(?<pu>\d*)\??$)"
    ); /**< Wyrażenie naturalne pobierająec szczegółowe dane dla poszczególnych przystanków z sekcji ZP */
    static const boost::u32regex expLines = boost::make_u32regex(
            R"(L\s+(?<num_lines>\d+)\s+-\s+(?<type>.+?):\s+(?<lines>(?:[\w-]{1,3}\^?\s*?)+)\s+$)"
    ); /**< Wyrażenie naturalne pobierające liniie odjeżdzające z danego przystanku */
    boost::smatch match;
    if (boost::u32regex_search(line, match, expLines)) {
        // Zabezpieczenie, póki co nie używane dane
    } else if (boost::u32regex_search(line, match, expStop)) {
        this->manager->stops.emplace_back(match["id"], match["group_id"], match["id_in_group"], match["street"],
                match["direction"], match["lat"], match["lon"]);
    } else {
        throw CouldNotParseLineException(line);
    }
}