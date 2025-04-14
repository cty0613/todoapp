cmake_minimum_required(VERSION 3.19)
project(todoapp LANGUAGES CXX)

include_directories("cmake-build-debug/${PROJECT_NAME}_autogen/include")
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(todoapp
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    model/reminder.h model/reminder.cpp
    model/todo.h model/todo.cpp
    model/reminder.h model/reminder.cpp
    data/todo.json
)

target_link_libraries(todoapp
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS todoapp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET todoapp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
