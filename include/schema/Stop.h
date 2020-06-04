//
// Autorzy:
// Michał Rokita, Adamski Maciej
//

#ifndef ZTMAPI_CORE_STOP_H
#define ZTMAPI_CORE_STOP_H

#include <utility>

class Stop {
public:
    int id;
    int groupId;
    std::string const idInGroup;
    std::string const street;
    std::string const direction;
    float lat;
    float lon;

    static float parseCord(const std::string& id, const std::string& cordStr){
        float cord;
        try {
            cord = std::stof(cordStr);
        } catch (std::invalid_argument& e){
            cord = 0.f;
            std::cout << "Couldn't parse coordinate for stop " << id
                      << "(Received: \"" << cord << "\")" << std::endl;
        }
        return cord;
    }

    Stop(const std::string& id,
         const std::string& groupId,
         std::string idInGroup,
         std::string street,
         std::string direction,
         const std::string& lat,
         const std::string& lon)
            :
            id(stoi(id)),
            groupId(stoi(groupId)),
            idInGroup(std::move(idInGroup)),
            street(std::move(street)),
            direction(std::move(direction)),
            lat(Stop::parseCord(id, lat)),
            lon(Stop::parseCord(id, lon)){}

    Stop() = default;

    Stop &operator=(const Stop &s) {
        return *this; // make immutable for Python TODO: Raise a Python Exception
    }

    bool operator==(const Stop &s) const {
        return s.id == this->id;
    }
};

#endif //ZTMAPI_CORE_STOP_H
