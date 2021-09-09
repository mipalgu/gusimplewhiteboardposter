#
# Auto-generated cmake build file for gusimplewhiteboardposter
#
cmake_minimum_required(VERSION 3.15.0)
project(gusimplewhiteboardposter C CXX)
enable_testing()
include( GNUInstallDirs )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_definitions()
include_directories($<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/./ $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/gusimplewhiteboardposter> ../../Common /usr/local/include)
link_directories(/usr/local/lib)
add_executable(gusimplewhiteboardposter ../../posix/gu_util/gu_util.cpp ../../posix/gusimplewhiteboard/guwhiteboardgetter.cpp ../../posix/gusimplewhiteboard/guwhiteboardposter.cpp ../../posix/gusimplewhiteboard/guWhiteboard_gugenericwhiteboardobject.cpp ../../posix/gusimplewhiteboard/gugenericwhiteboardobject.cpp ../../posix/gusimplewhiteboard/gusimplewhiteboard.c ../../posix/gusimplewhiteboard/guwhiteboardtypelist_c_typestrings_generated.c gusimplewhiteboardposter.cc)
target_link_libraries(gusimplewhiteboardposter )
install(TARGETS gusimplewhiteboardposter DESTINATION bin)
