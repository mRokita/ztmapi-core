#include <ctime>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include "include/ScheduleManager.h"
#include "schema/DayType.h"
#include "schema/StopGroup.h"
#include "schema/Stop.h"
#include "schema/Line.h"
#include "schema/Course.h"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <vector>

typedef std::vector<DayType> DayTypeList;
typedef std::vector<StopGroup> StopGroupList;
typedef std::vector<Stop> StopList;
typedef std::vector<Line> LineList;
typedef std::vector<Departure> DepartureList;
typedef std::map<std::string, Course> CourseMap;

BOOST_PYTHON_MODULE(ztmapi_core){
        namespace py = boost::python;
    py::class_<DayType>("DayType")
            .def_readonly("id", &DayType::id)
            .def_readonly("name", &DayType::name);
    py::class_<DayTypeList>("DayTypeList")
                .def(py::vector_indexing_suite<DayTypeList>());
    py::class_<StopGroup>("StopGroup")
            .def_readonly("id", &StopGroup::id)
            .def_readonly("name", &StopGroup::name)
            .def_readonly("region_id", &StopGroup::regionId)
            .def_readonly("region_name", &StopGroup::regionName);
    py::class_<StopGroupList>("StopGroupList")
            .def(py::vector_indexing_suite<StopGroupList>());
    py::class_<Stop>("Stop")
            .def_readonly("id", &Stop::id)
            .def_readonly("group_id", &Stop::groupId)
            .def_readonly("id_in_group", &Stop::idInGroup)
            .def_readonly("street", &Stop::street)
            .def_readonly("direction", &Stop::direction)
            .def_readonly("lat", &Stop::lat)
            .def_readonly("lon", &Stop::lon);
    py::class_<StopList>("StopList")
            .def(py::vector_indexing_suite<StopList>());
    py::class_<Line>("Line")
            .def_readonly("id", &Line::id)
            .def_readonly("type", &Line::type);
    py::class_<LineList>("LineList")
            .def(py::vector_indexing_suite<LineList>());
    py::class_<Departure>("Departure")
            .def_readonly("id", &Departure::id)
            .def_readonly("course_id", &Departure::courseId)
            .def_readonly("stop_id", &Departure::stopId)
            .def_readonly("departure_hour", &Departure::departureHour)
            .def_readonly("departure_minute", &Departure::departureMinute)
            .def_readonly("is_course_start", &Departure::isCourseStart)
            .def_readonly("is_public", &Departure::isPublic)
            .def_readonly("order", &Departure::order);
    py::class_<DepartureList>("DepartureList")
            .def(py::vector_indexing_suite<DepartureList>());
    py::class_<Course>("Course")
            .def_readonly("id", &Course::id)
            .def_readonly("line_id", &Course::lineId)
            .def_readonly("track_id", &Course::trackId)
            .def_readonly("start_hour", &Course::startHour)
            .def_readonly("start_minute", &Course::startMinute)
            .def_readonly("day_type", &Course::dayType);
    py::class_<CourseMap>("CourseDict")
            .def(py::map_indexing_suite<CourseMap>());
    py::class_<ScheduleManager>("ScheduleManager")
        .def(py::init<>())
        .def(py::init<int, int, int>())
        .def("download_schedule", &ScheduleManager::downloadSchedule)
        .def_readonly("day_types", &ScheduleManager::dayTypes)
        .def_readonly("stop_groups", &ScheduleManager::stopGroups)
        .def_readonly("stops", &ScheduleManager::stops)
        .def_readonly("lines", &ScheduleManager::lines)
        .def_readonly("courses", &ScheduleManager::courses)
        .def_readonly("departures", &ScheduleManager::departures)
        .def("process_schedule", &ScheduleManager::processSchedule);
}
