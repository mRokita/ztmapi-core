#ifndef ZTMAPI_CORE_KDSECTION_H
#define ZTMAPI_CORE_KDSECTION_H
#include "Section.h"

class KDSection : public Section {
    using Section::Section;
protected:
    void _processLine(const std::string& line) override;
};
#endif //ZTMAPI_CORE_KDSECTION_H
