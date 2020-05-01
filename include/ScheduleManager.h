#ifndef ZTMAPI_CORE_SCHEDULEMANAGER_H
#define ZTMAPI_CORE_SCHEDULEMANAGER_H


#include "Section.h"
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <fstream>
#include <vector>
#include "schema/DayType.h"
#include "schema/Departure.h"
#include "schema/StopGroup.h"
#include "schema/Line.h"
#include "schema/Stop.h"
#include "schema/Course.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include <map>
#include <chrono>

using namespace boost::gregorian;

class ScheduleManager {
public:
    std::vector<DayType> dayTypes;
    std::vector<StopGroup> stopGroups;
    std::vector<Stop> stops;
    std::vector<Line> lines;
    std::vector<Departure> departures;
    std::map<std::string, Course> courses;

    /**
     * Set the timezone to Poland/Warsaw and apply today's date
     * @return ScheduleManager with _scheduleId for today
     */
    ScheduleManager(){
        char env[] = "TZ=CET";
        putenv(env);
        _scheduleDate = day_clock::local_day();
        _scheduleFileDate = std::move(_scheduleDate);
    }

    ~ScheduleManager(){
    }


    /**
     * Download the compressed schedule to schedule.7z, then extract the schedule file.
     */
    void downloadSchedule(){
        std::ofstream scheduleFile("schedule.7z", std::ios::binary);
        bool downloaded=false;
        for (int tries=0; downloaded == false; tries++) {
            std::cout << "Downloading " << getDownloadUrl() << "..." << std::endl;
            try {
                curlpp::Cleanup myCleanup;
                scheduleFile << curlpp::options::Url(getDownloadUrl());
                scheduleFile.close();
                downloaded = true;
                extractSchedule();
            } catch (curlpp::RuntimeError &e) {
                if (tries > 7){
                    throw e;
                } else {
                    std::cout << "No schedule available for this day, trying the day before..." << std::endl;
                    _scheduleFileDate -= days(1);
                }
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
    std::string getScheduleDate(){
        date_facet *df = new date_facet("%Y-%m-%d");
        std::stringstream s;
        s.imbue(std::locale(s.getloc(), df));
        s << _scheduleDate;
        return s.str();
    }

    /**
     * Get schedule date in yyyy-mm-dd format
     */
    std::string getScheduleFileDate(){
        date_facet *df = new date_facet("%y%m%d");
        std::stringstream s;
        s.imbue(std::locale(s.getloc(), df));
        s << _scheduleFileDate;
        return s.str();
    }

    /**
     * Should be only used inside KDSection::_processLine()
     * Assigns a day type to a line.
     */
    void setDayType(const std::string& line, const std::string& dayType){
        _lineToDayType[line] = dayType;
    }

    /**
     * Check if course has been registered already
     * @param courseId unique id of the course generated in WKSection::_processLine
     */
    bool isCourseRegistered(const std::string& courseId){
        return courses.find(courseId) != courses.end();
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
    date _scheduleDate;
    date _scheduleFileDate;
    std::map<std::string, std::string> _lineToDayType;

    /**
     * Get schedule file name in "RA%y%m%d.TXT" format
     * @return schedule file name
     */
    std::string getScheduleFileName(){
        std::string fileName("RA");
        fileName.append(this->getScheduleFileDate());
        fileName.append(".TXT");
        return fileName;
    }

    /**
     * Get the download url for compressed schedule (RA%y%m%d.TXT)
     * @return download url
     */
    std::string getDownloadUrl(){
        std::string url("ftp://rozklady.ztm.waw.pl/RA");
        url.append(this->getScheduleFileDate());
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
