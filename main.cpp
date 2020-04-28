#include <ctime>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include "include/ScheduleManager.h"
#include "include/DayType.h"
#include "include/StopGroup.h"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <vector>

typedef std::vector<DayType> DayTypeList;
typedef std::vector<StopGroup> StopGroupList;

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
    py::class_<ScheduleManager>("ScheduleManager")
        .def("download_schedule", &ScheduleManager::downloadSchedule)
        .def_readonly("day_types", &ScheduleManager::dayTypes)
        .def_readonly("stop_groups", &ScheduleManager::stopGroups)
        .def("process_schedule", &ScheduleManager::processSchedule);
}
