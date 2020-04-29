#include "Section.h"
#include "ZPSection.h"
#include "ZASection.h"
#include "TYSection.h"


void Section::openSection(const std::string& sectionKey) {
    if (sectionKey == "TY"){
        currentSubSection = std::make_unique<TYSection>(this->manager);
    } else if (sectionKey == "ZA") {
        currentSubSection = std::make_unique<ZASection>(this->manager);
    } else if (sectionKey == "ZP") {
        currentSubSection = std::make_unique<ZPSection>(this->manager);
    } else {
        throw InvalidSectionException("No implementation for sectionKey");
    }
    currentSubSectionID = sectionKey;
}

void Section::processLine(const std::string &line) {
    boost::smatch match;
    static const boost::regex expOpenSection(R"(\s*(\*|#)(\w\w).+)");
    // match[1] * or # == OPEN or CLOSE
    // match[2] Section ID (two letters)
    if(boost::regex_search(line, match, expOpenSection)){
        // TODO: Lower cyclomatic complexity
        try {
            if(match[1] == "*"){ // Open new section
                this->openSection(match[2]);
            } else { // #, close section it is the current subsection
                if(match[2] == currentSubSectionID){
                    this->closeCurrentSubSection();
                }
            }
        } catch (InvalidSectionException& e) {
            // It's alright
            std::cout << "WARNING: No implementation for section \"" << match[2] << '"' << std::endl;
        }
        return;
    }

    if (currentSubSection){
        currentSubSection->processLine(line);
    } else {
        this->_processLine(line);
    }
}