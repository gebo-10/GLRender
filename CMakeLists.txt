set_property(GLOBAL PROPERTY USE_FOLDERS On)
cmake_minimum_required(VERSION 3.7)
PROJECT (GLRender)
add_subdirectory(core)
add_subdirectory(component)
SET(SRC_LIST main.cpp)

ADD_EXECUTABLE(main ${SRC_LIST} ${CORE_SRC})
target_link_libraries(main core)