#ifndef ZTMAPI_CORE_TYSECTION_H
#define ZTMAPI_CORE_TYSECTION_H
#include "Section.h"

class TYSection : public Section {
    using Section::Section;
protected:
    void _processLine(const std::string& line) override;
};
#endif //ZTMAPI_CORE_TYSECTION_H
