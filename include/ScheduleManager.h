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
	 * Ustawia strefę czasową na Polska/Warszawa i dzisiejszą datę.
     */
    ScheduleManager(){
        char env[] = "TZ=CET";
        putenv(env);
        _scheduleDate = day_clock::local_day();
        _scheduleFileDate = day_clock::local_day();
    }

    ScheduleManager(int year, int month, int day){
        char env[] = "TZ=CET";
        putenv(env);
        _scheduleDate = date(year, month, day);
        _scheduleFileDate =  date(year, month, day);
    }

    ~ScheduleManager(){
    }

    /**
	 * Pobiernie plików rozkładowych i dekompresja.
	 * Pobiera pliki rozkładowe z zewnętrznego API w formacie 7z, a następnie je dekompresuje.
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
     * Proces parsowania pliku rozkładowego.
     */
    void processSchedule();

    /**
	 * Zwraca datę rozkładu w formacie yyyy-mm-dd.
	 * @return Data
     */
    std::string getScheduleDate(){
        date_facet *df = new date_facet("%Y-%m-%d");
        std::stringstream s;
        s.imbue(std::locale(s.getloc(), df));
        s << _scheduleDate;
        return s.str();
    }

    /**
     * Zwraca datę pliku rozkładoweg w formacie yyyy-mm-dd.
	 * @return Data
     */
    std::string getScheduleFileDate(){
        date_facet *df = new date_facet("%y%m%d");
        std::stringstream s;
        s.imbue(std::locale(s.getloc(), df));
        s << _scheduleFileDate;
        return s.str();
    }

    /**
	 * Przypisuje typ dnia do danej linii.
	 * Używane jedynie w sekcji KD, która zawiera typ dnia każdej linii.
	 * @param line Wybrana linia
	 * @param dayType Typ dnia
     */
    void setDayType(const std::string& line, const std::string& dayType){
        _lineToDayType[line] = dayType;
    }

    /**
	 * Sprawdzenie czy kurs został już zarejestrowany
	 * @param courseId Unikalne id kursu generowane z sekcji WK
     * @return Czy kurs już zarejestrowany
     */
    bool isCourseRegistered(const std::string& courseId){
        return courses.find(courseId) != courses.end();
    }


	/**
	 * Sprawdzenie czy dana linia kursuje w aktualnym dniu.
	 * @param line Wybrana linia
	 * @return Czy dana linia kursuje
	 */
    bool isLineActive(const std::string& line){
        return _lineToDayType.find(line) != _lineToDayType.end();
    }

    /**
	 * Pobranie typu dnia dla wybranej linii.
     * @oaram line Wybrana linia
	 * @return Typ dnia
     */
    std::string getDayType(const std::string& line){
        return _lineToDayType[line];
    }

private:
    date _scheduleDate;
    date _scheduleFileDate;
    std::map<std::string, std::string> _lineToDayType;

    /**
	 * Wygenerowanie nazwy pliku rozkładowego dla danego dnia.
     * Nazwa pliku w formacie "RA%y%m%d.TXT".
     * @return Nazwa pliku rozkładowego
     */
    std::string getScheduleFileName(){
        std::string fileName("RA");
        fileName.append(this->getScheduleFileDate());
        fileName.append(".TXT");
        return fileName;
    }

    /**
	 * Wygenerowanie linku URL do pobrania pliku rozkładowego na dany dzień.
     * (RA%y%m%d.TXT)
     * @return Link URL
     */
    std::string getDownloadUrl(){
        std::string url("ftp://rozklady.ztm.waw.pl/RA");
        url.append(this->getScheduleFileDate());
        url.append(".7z");
        return url;
    }

    /**
     * Dekompresja i rozpakowanie pliku 7z
	 * Wykorzystuje wywołanie systemowe LINUX
     */
    static void extractSchedule(){
        system("7z e schedule.7z -y");
    }
};

#endif //ZTMAPI_CORE_SCHEDULEMANAGER_H
