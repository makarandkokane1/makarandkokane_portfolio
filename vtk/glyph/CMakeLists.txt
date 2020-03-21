PROJECT (glyph3d_example)

cmake_minimum_required(VERSION 3.15)

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

ADD_EXECUTABLE(glyph3d_example
glyph3d_example.cxx
../../utilities/mkEnvironmentVariables.cxx
../../utilities/mkMemoryRawArrays.cxx
../mkVisualizeAlgorithmOutput.cxx
)
