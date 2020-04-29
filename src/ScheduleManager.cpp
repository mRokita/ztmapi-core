#include "ScheduleManager.h"
#include <boost/locale.hpp>

void ScheduleManager::processSchedule() {
    // TODO: Throw an exception if no schedule has been downloaded yet

    std::string line;
    std::ifstream scheduleFile(getScheduleFileName());

    std::shared_ptr<MainSection> section = std::make_shared<MainSection>(this);
    int i = 0;
    while (std::getline(scheduleFile, line) && i < 4000000){
        boost::smatch match;
        static const boost::regex expOpenSection(R"(\s*(?<open_or_close>\*|#)(?<section_key>\w\w)\s*(?<num_lines>\d*))");
        // match[1] * or # == OPEN or CLOSE
        // match[2] Section ID (two letters)
        if(boost::regex_search(line, match, expOpenSection)){
            // TODO: Lower cyclomatic complexity
            if(match["open_or_close"] == "*"){
                try {
                    std::cout << "OPEN: " << match["section_key"] << std::endl;
                    section->openSection(match["section_key"]);
                } catch (InvalidSectionException& e) {
                    // It's alright
                    std::cout << "WARNING: Skipping " << match["num_lines"] << " lines of section \"" << match["section_key"] << '"' << std::endl;
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
        i++;
    }
}