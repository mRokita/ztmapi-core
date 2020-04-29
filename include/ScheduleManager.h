#ifndef ZTMAPI_CORE_SCHEDULEMANAGER_H
#define ZTMAPI_CORE_SCHEDULEMANAGER_H


#include "Section.h"
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <fstream>
#include <vector>
#include "DayType.h"
#include "StopGroup.h"
#include "Stop.h"
#include <map>

class ScheduleManager {
public:
    const unsigned short SCHEDULE_ID_LENGTH = 7;
    const unsigned short DATE_LENGTH = 11;
    std::vector<DayType> dayTypes;
    std::vector<StopGroup> stopGroups;
    std::vector<Stop> stops;

    explicit ScheduleManager(tm* date){
        this->_scheduleId = new char[SCHEDULE_ID_LENGTH];
        this->_scheduleDate = new char[DATE_LENGTH];
        strftime(this->_scheduleId, SCHEDULE_ID_LENGTH, "%y%m%d", date);
    }

    /**
     * Set the timezone to Poland/Warsaw and apply today's date
     * @return ScheduleManager with _scheduleId for today
     */
    ScheduleManager(){
        char env[] = "TZ=CET";
        putenv(env);
        time_t now;
        time(&now);
        this->_scheduleId = new char[SCHEDULE_ID_LENGTH];
        this->_scheduleDate = new char[DATE_LENGTH];
        struct tm* tm = localtime(&now);
        // TODO: download for previous day if no avail for today
        tm->tm_mday += 1;
        strftime(this->_scheduleId, SCHEDULE_ID_LENGTH, "%y%m%d", tm);
        strftime(this->_scheduleDate, DATE_LENGTH, "%Y-%m-%d", tm);
    }


    /**
     * Download the compressed schedule to schedule.7z, then extract the schedule file.
     */
    void downloadSchedule(){
        std::ofstream scheduleFile("schedule.7z", std::ios::binary);
        if (scheduleFile.is_open()) {
            std::cout << "Downloading " << getDownloadUrl() << "..." << std::endl;
            try {
                curlpp::Cleanup myCleanup;
                scheduleFile << curlpp::options::Url(getDownloadUrl());
                scheduleFile.close();
                extractSchedule();
            } catch (curlpp::RuntimeError &e) {
                throw e;
            } catch (curlpp::LogicError &e) {
                throw e;
            }
        }
    }

    /**
     * Process the downloaded schedule
     */
    void processSchedule();

    /**
     * Get schedule date in yyyy-mm-dd format
     */
    char* getScheduleDate(){
        return _scheduleDate;
    }

    /**
     * Should be only used inside KDSection::_processLine()
     * Assigns a day type to a line.
     */
    void setDayType(const std::string& line, const std::string& dayType){
        _lineToDayType[line] = dayType;
    }

    bool isLineActive(const std::string& line){
        return _lineToDayType.find(line) != _lineToDayType.end();
    }

    /**
     * Get line's day type for today
     */
    std::string getDayType(const std::string& line){
        return _lineToDayType[line];
    }

private:
    char* _scheduleId;
    char* _scheduleDate;
    std::map<std::string, std::string> _lineToDayType;

    /**
     * Get schedule file name in "RA%y%m%d.TXT" format
     * @return schedule file name
     */
    std::string getScheduleFileName(){
        std::string fileName("RA");
        fileName.append(_scheduleId);
        fileName.append(".TXT");
        return fileName;
    }

    /**
     * Get the download url for compressed schedule (RA%y%m%d.TXT)
     * @return download url
     */
    std::string getDownloadUrl(){
        std::string url("ftp://rozklady.ztm.waw.pl/RA");
        url.append(this->_scheduleId);
        url.append(".7z");
        return url;
    }

    /**
     * Extract the schedule file from schedule.7z
     * Currently the best option to do that on Linux is using a system call.
     */
    static void extractSchedule(){
        system("7z e schedule.7z -y");
    }
};

#endif //ZTMAPI_CORE_SCHEDULEMANAGER_H
