#ifndef ZTMAPI_CORE_WKSECTION_H
#define ZTMAPI_CORE_WKSECTION_H
#include "Section.h"
#include "LLSection.h"

class WKSection : public SubSection<LLSection> {
    using SubSection<LLSection>::SubSection;
public:
    void _processLine(const std::string &string) override;
};


#endif //ZTMAPI_CORE_WKSECTION_H
