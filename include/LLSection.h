#ifndef ZTMAPI_CORE_LLSECTION_H
#define ZTMAPI_CORE_LLSECTION_H
#include "Section.h"

class LLSection : public Section {
    using Section::Section;
public:
private:
    void _processLine(const std::string &string) override;
};

#endif //ZTMAPI_CORE_LLSECTION_H
