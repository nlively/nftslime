# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0079 NEW)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(LOCAL_LIB_DIR "C:/Users/noahl/lib")

# Include glfw3
set(GLFW_DIR "${LOCAL_LIB_DIR}/glfw-3.3.9.bin.WIN64")
set(GLFW_INCLUDE_DIR "${GLFW_DIR}/include")
set(GLFW_LIBRARY_DIR "${GLFW_DIR}/lib-vc2022")

# Include PhysX
set(PHYSX_ROOT_DIR "${LOCAL_LIB_DIR}/Physx")
set(PHYSX_INCLUDE_DIRS "${PHYSX_ROOT_DIR}/include" "${PHYSX_ROOT_DIR}/pvdruntime/include")
set(PHYSX_LIBRARY_DIR "${PHYSX_ROOT_DIR}/bin/win.x86_64.vc143.mt/release")
project ("nftslime")



link_directories(${PHYSX_LIBRARY_DIR} ${GLFW_LIBRARY_DIR}) 
include_directories(${GLFW_INCLUDE_DIR} ${PHYSX_INCLUDE_DIRS})
find_library(GLFW_LIB NAMES glfw3 PATHS ${GLFW_LIBRARY_DIR} NO_DEFAULT_PATH)

find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master # or specify a specific commit/tag to lock to a stable version
)

FetchContent_MakeAvailable(stb)


add_executable(nftslime main.cpp)

# Link against STB
target_include_directories(nftslime PRIVATE ${stb_SOURCE_DIR})

# Link against GLFW and PhysX libraries
target_link_libraries(nftslime glfw3 PhysX_64 PVDRuntime_64 ${OPENGL_gl_LIBRARY}) 