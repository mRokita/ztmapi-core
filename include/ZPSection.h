#ifndef ZTMAPI_CORE_ZPSECTION_H
#define ZTMAPI_CORE_ZPSECTION_H
#include "Section.h"

class ZPSection : public Section {
    using Section::Section;
protected:
    void _processLine(const std::string& line) override;
};

#endif //ZTMAPI_CORE_ZPSECTION_H
