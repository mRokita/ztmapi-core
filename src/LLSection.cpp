#include "LLSection.h"

void LLSection::_processLine(const std::string &line) {
    static const boost::u32regex expLine = boost::make_u32regex(
            R"((Linia\:\s*(?<line>[\w-]+)\s*\-\s+(?<line_type>.+?)\s*$))");
    boost::smatch match;
    if(boost::u32regex_search(line, match, expLine)){
        _currentLine = match["line"];
        std::cout << "Parsing line " << _currentLine << std::endl;
        manager->lines.emplace_back(match["line"], match["line_type"]);
    } else {
        throw CouldNotParseLineException(line);
    }
}