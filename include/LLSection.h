//
// Autorzy:
// Michał Rokita, Adamski Maciej
//

#ifndef ZTMAPI_CORE_LLSECTION_H
#define ZTMAPI_CORE_LLSECTION_H
#include "Section.h"

class LLSection : public Section {
    using Section::Section;
public:
    std::string getCurrentLine(){
        return _currentLine;
    }
private:
    std::string _currentLine;
    void _processLine(const std::string &line) override;
};

#endif //ZTMAPI_CORE_LLSECTION_H
