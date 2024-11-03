# CMakeList.txt : CMake project for leetcode, include source and define
# project specific logic here.
#

file(GLOB solutions "solutions/*.cpp" "solutions/*.h")
file(GLOB tests "tests/*.cpp" "tests/*.h")


# Add source to this project's executable.
# add_executable (leetcode ${solutions})


add_subdirectory(deps/Catch2)
# These tests can use the Catch2-provided main
add_executable(tests ${solutions} ${tests})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# These tests need their own main
#add_executable(custom-main-tests test.cpp test-main.cpp)
#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tests PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
