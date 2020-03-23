#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <fstream>
#include <ctime>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>


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
    ScheduleManager(){
        char env[] = "TZ=CET";
        putenv(env);
        time_t now;
        time(&now);
        this->_scheduleId = new char[SCHEDULE_ID_LENGTH];
        strftime(this->_scheduleId, SCHEDULE_ID_LENGTH, "%y%m%d", localtime(&now));
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

BOOST_PYTHON_MODULE(ztmapi_core){
    namespace py = boost::python;
    py::class_<ScheduleManager>("ScheduleManager")
            .def("download_schedule", &ScheduleManager::downloadSchedule);
}
