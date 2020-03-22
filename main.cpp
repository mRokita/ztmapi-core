#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <fstream>
#include <ctime>


class ScheduleManager {
public:
    const unsigned short SCHEDULE_ID_LENGTH = 7;

    explicit ScheduleManager(tm* date){
        this->_scheduleId = new char[SCHEDULE_ID_LENGTH];
        strftime(this->_scheduleId, SCHEDULE_ID_LENGTH, "%y%m%d", date);
    }

    /**
     * Set the timezone to Poland/Warsaw and apply today's date
     * @return ScheduleManager with _scheduleId for today
     */
    static ScheduleManager forToday(){
        char env[] = "TZ=Poland/Warsaw";
        putenv(env);
        time_t now;
        time(&now);
        return ScheduleManager(localtime(&now));
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
     * Parse the downloaded schedule
     */
    void parseSchedule(){

    }

private:
    char* _scheduleId;

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


int main() {
    ScheduleManager sm = ScheduleManager::forToday();
    sm.downloadSchedule();
    return 0;
}
