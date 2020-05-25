from setuptools import setup, Extension
from sys import version_info

setup(
    name='ztmapi_core',
    version='0.0.9',
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
                  libraries=['boost_python3' + str(min(8, version_info[1])), 'boost_regex', 'boost_locale', 'boost_date_time', 'curlpp', 'curl'],
                  ),
    ]
)
