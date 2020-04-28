#include "ScheduleManager.h"
#include <boost/locale.hpp>

void ScheduleManager::processSchedule() {
    // TODO: Throw an exception if no schedule has been downloaded yet

    std::string line;
    std::ifstream scheduleFile(getScheduleFileName());

    MainSection section(this);
    int i = 0;
    while (std::getline(scheduleFile, line) && i < 2000){
        section.processLine(boost::locale::conv::to_utf<char>(line, "windows-1250"));
        i++;
    }
}