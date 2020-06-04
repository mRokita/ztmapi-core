//
// Autorzy:
// Michał Rokita, Adamski Maciej
//

#ifndef ZTMAPI_CORE_TRANSPARENTSECTION_H
#define ZTMAPI_CORE_TRANSPARENTSECTION_H
#include "Section.h"

class TransparentSection : public SubSection<Section> {
    using SubSection::SubSection;
private:

    void _processLine(const std::string &string) override {
        // Nothing to do here - this is a transparent section
    }

    void applyToSubSection(std::shared_ptr<Section> subSection) override {
        Section::applyToSubSection(getParent());
    }
};
#endif //ZTMAPI_CORE_TRANSPARENTSECTION_H
