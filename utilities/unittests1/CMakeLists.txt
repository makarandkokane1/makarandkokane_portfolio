PROJECT (unittests1)

IF(NOT VTK_BINARY_DIR)
FIND_PACKAGE(VTK)
IF(NOT VTK_DIR)
  MESSAGE(FATAL_ERROR "Please set VTK_DIR.")
ENDIF()
INCLUDE(${VTK_USE_FILE})
ENDIF()

LINK_LIBRARIES(
  ${VTK_LIBRARIES}
)

ADD_EXECUTABLE(unittests1 unittests1.cxx ../mkEnvironmentVariables.cxx ../mkMemoryRawArrays.cxx)
