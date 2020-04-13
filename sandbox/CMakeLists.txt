cmake_minimum_required(VERSION 3.15)

project(sandbox)

include(FetchContent)
FetchContent_Declare(
  project_essentials
  GIT_REPOSITORY https://github.com/wolfee001/project-essentials.git
  GIT_TAG        origin/master
)
FetchContent_MakeAvailable(project_essentials)
setup_project_essentials()

add_executable(sandbox
    src/sandbox.cpp
)

target_link_libraries(sandbox
    PRIVATE peach
)