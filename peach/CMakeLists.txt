cmake_minimum_required(VERSION 3.15)

project(peach)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/implementation/imgui_binding)

include(FetchContent)
FetchContent_Declare(
  project_essentials
  GIT_REPOSITORY https://github.com/wolfee001/project-essentials.git
  GIT_TAG        origin/master
)
FetchContent_MakeAvailable(project_essentials)
setup_project_essentials()

file(GLOB_RECURSE src ${PROJECT_SOURCE_DIR}/src/implementation/*.cpp)
list(FILTER src EXCLUDE REGEX "imgui_binding")

add_library(peach
    ${src}
)

target_include_directories(peach
    PUBLIC src/include
    PUBLIC ${CONAN_INCLUDE_DIRS_SPDLOG}
    PUBLIC ${CONAN_INCLUDE_DIRS_IMGUI}
    PUBLIC ${CONAN_INCLUDE_DIRS_GLAD}
    PRIVATE src/implementation
    PRIVATE ${CONAN_INCLUDE_DIRS}
)

target_link_libraries(peach
    PUBLIC CONAN_PKG::spdlog
    PUBLIC CONAN_PKG::glad
    PUBLIC CONAN_PKG::imgui
    PRIVATE imgui_binding
    PRIVATE CONAN_PKG::fmt
    PRIVATE CONAN_PKG::glm
    PRIVATE CONAN_PKG::stb
    PRIVATE CONAN_PKG::glfw
    PRIVATE peach_warnings
)
