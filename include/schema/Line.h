#ifndef ZTMAPI_CORE_LINE_H
#define ZTMAPI_CORE_LINE_H


class Line {
public:
    std::string const id;
    std::string const type;

    Line(std::string id, std::string type) : id(std::move(id)), type(std::move(type)){}

    Line() = default;

    Line &operator=(const Line &l) {
        return *this; // make immutable for Python TODO: Raise a Python Exception
    }

    bool operator==(const Line &l) const {
        return l.id == this->id;
    }
};


#endif //ZTMAPI_CORE_LINE_H
