cmake_minimum_required(VERSION 3.15)

project(imgui_bindings)

include(FetchContent)
FetchContent_Declare(
  project_essentials
  GIT_REPOSITORY https://github.com/wolfee001/project-essentials.git
  GIT_TAG        origin/master
)
FetchContent_MakeAvailable(project_essentials)
standard_setup(17)
set(conan_buildtype ${CMAKE_BUILD_TYPE})
if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    set(conan_buildtype "Release")
endif()
setup_conan(conanfile.txt ${conan_buildtype})

add_library(imgui_binding
    ImGuiGLFW.cpp
    ImGuiOpenGL.cpp
)

target_include_directories(imgui_binding
    PRIVATE ${CONAN_INCLUDE_DIRS}
)

target_link_libraries(imgui_binding
    PRIVATE CONAN_PKG::glad
    PRIVATE CONAN_PKG::imgui
    PRIVATE CONAN_PKG::glfw
)
