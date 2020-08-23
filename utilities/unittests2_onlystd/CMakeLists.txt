PROJECT (unittests2_onlystd)

set (CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(unittests2_onlystd unittests2_onlystd.cxx ../mkEnvironmentVariables.cxx ../mkMemoryRawArrays.cxx ../mkFilesystem.cxx)
