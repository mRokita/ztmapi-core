#ifndef ZTMAPI_CORE_DAYTYPE_H
#define ZTMAPI_CORE_DAYTYPE_H
#include <string>
#include <utility>

class DayType {
public:
    std::string const id;
    std::string const name;
    DayType(std::string id, std::string name) : id(std::move(id)), name(std::move(name)){}

    DayType() = default;

    DayType& operator=(const DayType& d){
      return *this; // make immutable for Python TODO: Raise a Python Exception
    }

    bool operator==(const DayType& d){
        return d.id == this->id;
    }
};
#endif //ZTMAPI_CORE_DAYTYPE_H
