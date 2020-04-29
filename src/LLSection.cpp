#include "LLSection.h"

void LLSection::_processLine(const std::string &line) {
    static const boost::u32regex expLine = boost::make_u32regex(
            R"((Linia\:\s*(?<line>[\w-]+)\s*\-\s+(?<line_type>.+?)\s*$))");
    boost::smatch match;
    if(boost::u32regex_search(line, match, expLine)){
        std::cout << match["line"] << match["line_type"] << "Active: " << manager->isLineActive(match["line"]) << std::endl;
    } else {
        throw CouldNotParseLineException(line);
    }
}