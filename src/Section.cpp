#include "Section.h"
#include "PRSection.h"
#include "ZASection.h"
#include "TYSection.h"
#include "TransparentSection.h"
#include "KDSection.h"


void Section::openSection(const std::string& sectionKey) {
    if(currentSubSection) {
        // Down to the parent section of the new sub-section
        return this->currentSubSection->openSection(sectionKey);
    }
    if (sectionKey == "TY"){
        currentSubSection = std::make_shared<TYSection>(this->manager);
    } else if (sectionKey == "ZA") {
        currentSubSection = std::make_shared<ZASection>(this->manager);
    } else if (sectionKey == "PR") {
        currentSubSection = std::make_shared<PRSection>(this->manager);
    } else if (sectionKey == "KD") {
        currentSubSection = std::make_shared<KDSection>(this->manager);
    } else if (sectionKey == "ZP") {
        // Parent of PR, no need to parse body.
        currentSubSection = std::make_shared<TransparentSection>(this->manager);
    } else {
        throw InvalidSectionException("No implementation for sectionKey");
    }
    applyToSubSection(currentSubSection);
    currentSubSectionID = sectionKey;
}

void Section::processLine(const std::string &line) {
    if (currentSubSection){
        currentSubSection->processLine(line);
    } else {
        this->_processLine(line);
    }
}