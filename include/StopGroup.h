#ifndef ZTMAPI_CORE_STOPGROUP_H
#define ZTMAPI_CORE_STOPGROUP_H
#include <string>
#include <utility>

class StopGroup {
public:
    std::string const id;
    std::string const name;
    std::string const regionId;
    std::string const regionName;

    StopGroup(std::string id, std::string name, std::string regionId, std::string regionName) : id(std::move(id)),
        name(std::move(name)), regionId(std::move(regionId)), regionName(std::move(regionName)){}

    StopGroup() = default;

    StopGroup& operator=(const StopGroup& s){
        return *this; // make immutable for Python TODO: Raise a Python Exception
    }

    bool operator==(const StopGroup& s){
        return s.id == this->id;
    }
};
#endif //ZTMAPI_CORE_STOPGROUP_H
