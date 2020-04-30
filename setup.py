from setuptools import setup, Extension

setup(
    name='ztmapi_core',
    version='0.0.2',
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
                  libraries=['boost_python37', 'boost_regex', 'boost_locale', 'curlpp', 'curl'],
                  ),
    ]
)
