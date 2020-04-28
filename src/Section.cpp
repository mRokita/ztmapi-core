#include "Section.h"
#include "ZASection.h"
#include "TYSection.h"


void Section::openSection(const std::string& sectionKey) {
    if (sectionKey == "TY"){
        currentSubSection = std::make_unique<TYSection>(this->manager);
    } else if (sectionKey == "ZA") {
        currentSubSection = std::make_unique<ZASection>(this->manager);
    } else {
            throw InvalidSectionException("No implementation for sectionKey");
    }
    currentSubSectionID = sectionKey;
}
