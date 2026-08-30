
cmake_minimum_required(VERSION 3.16)

project(MegaByte_Finder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    Concurrent
    Widgets
)

qt_standard_project_setup(REQUIRES 6.8)

# ---------------------------------------------------------
# Исполняемый файл
# ---------------------------------------------------------

qt_add_executable(MegaByteFinder
    main.cpp
    app.rc
)

# ---------------------------------------------------------
# Ресурсы приложения
# ---------------------------------------------------------

qt_add_resources(MegaByteFinder "app_resources"
    PREFIX "/"
    FILES
        resources/free-icon.ico
)

# ---------------------------------------------------------
# QML-модуль и C++ исходники
# ---------------------------------------------------------

qt_add_qml_module(MegaByteFinder
    URI MegaByte_Finder
    VERSION 1.0

    QML_FILES
        Main.qml

    SOURCES
        MegaByteFinder.h
        MegaByteFinder.cpp
        WindowsNotification.h
        WindowsNotification.cpp
)

# ---------------------------------------------------------
# Свойства приложения
# ---------------------------------------------------------

set_target_properties(MegaByteFinder PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING
        ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "MegaByteFinder"

)

# ---------------------------------------------------------
# Библиотеки Qt
# ---------------------------------------------------------

target_link_libraries(MegaByteFinder PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Concurrent
    Qt6::Widgets
)

# ---------------------------------------------------------
# Установка
# ---------------------------------------------------------

include(GNUInstallDirs)

install(TARGETS MegaByteFinder
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
