#
# Autorzy:
# Michał Rokita, Adamski Maciej
#

from setuptools import setup, Extension
from sys import version_info

BOOST_MINOR_VERSION = str(min(8, version_info[1]))

setup(
    name='ztmapi_core',
    version='0.0.11',
    description='Parsing utilities for ZTM API',
    author='Michał Rokita',
    author_email='mrokita@mrokita.pl',
    include_package_data=True,
    zip_safe=False,
    ext_modules=[
        Extension('ztmapi_core',
                  ['main.cpp', 'src/KDSection.cpp', 'src/PRSection.cpp', 'src/ZASection.cpp', 'src/LLSection.cpp',
                   'src/ScheduleManager.cpp', 'src/Section.cpp', 'src/TYSection.cpp', 'src/WKSection.cpp'],
                  include_dirs=['include/'],
                  libraries=['boost_python3' + BOOST_MINOR_VERSION,
                             'boost_regex',
                             'boost_locale',
                             'boost_date_time',
                             'curlpp',
                             'curl'],
                  ),
    ]
)
