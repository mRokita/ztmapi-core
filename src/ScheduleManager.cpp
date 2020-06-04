#include "ScheduleManager.h"
#include <boost/locale.hpp>

void ScheduleManager::processSchedule() {
    std::string line;
    std::ifstream scheduleFile(getScheduleFileName());

    std::shared_ptr<MainSection> section = std::make_shared<MainSection>(this);
    while (std::getline(scheduleFile, line)){
        boost::smatch match;
        static const boost::regex expOpenSection(
                R"(\s*(?<open_or_close>\*|#)(?<section_key>\w\w)\s*(?<num_lines>\d*))"); /**< Wyrażenie naturalne pobierające początek lub koniec sekcji. */
		// * - otwarcie sekcji
		// # - zamknięcie sekcji
        if(boost::regex_search(line, match, expOpenSection)){
            if(match["open_or_close"] == "*"){
                try {
                    section->openSection(match["section_key"]);
                } catch (InvalidSectionException& e) {
                    // Część sekcji jest pomijanych celem szybszego parsowania pliku
                    std::cout << "WARNING: Skipping " << match["num_lines"] << " subsections of section \"" << match["section_key"] << '"' << std::endl;
                    std::string tag;
                    while(tag != match["section_key"]){
                        scheduleFile.ignore(std::numeric_limits<std::streamsize>::max(), scheduleFile.widen('#'));
                        scheduleFile >> tag;
                    }
                    scheduleFile.ignore(128, scheduleFile.widen('\n'));
                }
                continue;
            } else if(match["open_or_close"] == '#'){
                section->closeSection(match["section_key"]);
                continue;
            }
        }
        section->processLine(boost::locale::conv::to_utf<char>(line, "windows-1250"));
    }
}