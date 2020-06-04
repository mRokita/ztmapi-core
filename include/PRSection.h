//
// Autorzy:
// Michał Rokita, Adamski Maciej
//

#ifndef ZTMAPI_CORE_PRSECTION_H
#define ZTMAPI_CORE_PRSECTION_H
#include "Section.h"

class PRSection : public Section {
    using Section::Section;
protected:
    void _processLine(const std::string& line) override;
};

#endif //ZTMAPI_CORE_PRSECTION_H
