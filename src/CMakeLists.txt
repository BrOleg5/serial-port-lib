add_library(SerialPortLib serialport.cpp serialport.hpp)

# set include dirs
if(WIN32 AND NOT CYGWIN)
  set(DEF_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR})
else()
  set(DEF_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/SerialPort)
endif()
set(INCLUDE_DIR ${DEF_INCLUDE_DIR} CACHE PATH
  "Installation directory for include files")

set_target_properties(SerialPortLib PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      PUBLIC_HEADER serialport.hpp)

target_include_directories(SerialPortLib PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:${INCLUDE_DIR}>)

install(TARGETS SerialPortLib
        EXPORT SerialPortTargets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT lib
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INCLUDE_DIR}" COMPONENT dev)