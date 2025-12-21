# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("COBS")
set(CMAKE_GENERATOR_PLATFORM x64)
set(VCPKG_VISUAL_STUDIO_PATH "C:/Program Files/Microsoft Visual Studio/18/Insiders")
set(VCPKG_PLATFORM_TOOLSET "v143")
set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/Microsoft Visual Studio/18/Insiders/VC/vcpkg/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Include sub-projects.
add_subdirectory ("COBS")
