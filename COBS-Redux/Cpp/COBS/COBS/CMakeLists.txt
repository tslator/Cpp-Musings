# CMakeList.txt : CMake project for COBS, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (COBS "COBS.cpp" "COBS.h" "main.cpp" "test_vectors.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET COBS PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
