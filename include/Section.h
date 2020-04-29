#ifndef ZTMAPI_CORE_SECTION_H
#define ZTMAPI_CORE_SECTION_H

#include <iomanip>
#include <iostream>
#include <utility>
#include <memory>
#include "ScheduleManager.h"
#include <boost/regex/icu.hpp>

class ScheduleManager;

class InvalidSectionException : public std::exception {
public:
    explicit InvalidSectionException(std::string sectionKey) : sectionKey(std::move(sectionKey)){

    }
    virtual const char* what() const throw() {
        return sectionKey.c_str();
    }
    const std::string sectionKey;
};

class CouldNotParseLineException : public std::exception {
public:
    explicit CouldNotParseLineException(std::string line) : line(std::move(line)){

    }
    virtual const char* what() const throw() {
        return line.c_str();
    }
    const std::string line;
};

class Section {
public:
    explicit Section(ScheduleManager* manager) : manager(manager){
    }

    void processLine(const std::string& line);

    void closeCurrentSubSection(){
        currentSubSection.reset();
        currentSubSectionID = "";
    }

    void openSection(const std::string& sectionKey);

protected:
    /**
     * This function should perform analysis of section body
     */
    virtual void _processLine(const std::string&) = 0;
    ScheduleManager* manager;
private:
    std::unique_ptr<Section> currentSubSection;
    std::string currentSubSectionID;
};


class MainSection : public Section {
    using Section::Section;
protected:
    void _processLine(const std::string& line) override {

    }
};


#endif //ZTMAPI_CORE_SECTION_H
