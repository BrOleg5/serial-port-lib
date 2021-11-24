cmake_minimum_required(VERSION 3.0)

project(SerialPort VERSION 1.0 DESCRIPTION "Library to communicate by serial port.")

# set cmake config install dirs
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/SerialPort)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

include(GNUInstallDirs)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_subdirectory(src)

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE SerialPort)

# Create the SerialPortConfig.cmake and SerialPortConfigVersion.cmake files
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(cmake/SerialPortConfig.cmake.in
               "${PROJECT_BINARY_DIR}/cmake/SerialPortConfig.cmake" @ONLY)

# ... for the install tree
set(CONF_INCLUDE_DIRS "\${SERIALPORT_CMAKE_DIR}/${CMAKE_INSTALL_INCLUDEDIR}")
configure_file(cmake/SerialPortConfig.cmake.in
               "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cmake/SerialPortConfig.cmake" @ONLY)

# ... for both
configure_file(cmake/SerialPortConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/cmake/SerialPortConfigVersion.cmake" @ONLY)

# Install the SerialPortConfig.cmake and SerialPortConfigVersion.cmake files
install(FILES
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cmake/SerialPortConfig.cmake"
        "${PROJECT_BINARY_DIR}/cmake/SerialPortConfigVersion.cmake"
        DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT SerialPortTargets
        DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)