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

    void processLine(const std::string& line){
        boost::smatch match;
        static const boost::regex expOpenSection(".*?(\\*|#)(\\w\\w)");
        // match[1] * or # == OPEN or CLOSE
        // match[2] Section ID (two letters)
        if(boost::regex_search(line, match, expOpenSection)){
            // TODO: Lower cyclomatic complexity
            try {
                if(match[1] == "*"){ // Open new section
                    this->openSection(match[2]);
                    return;
                } else { // #, close section it is the current subsection
                    if(match[2] == currentSubSectionID){
                        this->closeCurrentSubSection();
                        return;
                    }
                }
            } catch (InvalidSectionException& e) {
                // It's alright
                std::cout << "WARNING: No implementation for section \"" << match[2] << '"' << std::endl;
            }
        }

        if (currentSubSection){
            currentSubSection->processLine(line);
        } else {
            this->_processLine(line);
        }
    }

    void closeCurrentSubSection(){
        currentSubSection.reset();
        std::cout << "CLOSE TY" << std::endl;
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
