//
// Autorzy:
// Michał Rokita, Adamski Maciej
//


#ifndef ZTMAPI_CORE_ZASECTION_H
#define ZTMAPI_CORE_ZASECTION_H
#include "Section.h"

class ZASection : public Section {
    using Section::Section;
protected:
    void _processLine(const std::string& line) override;
};


#endif //ZTMAPI_CORE_ZASECTION_H
