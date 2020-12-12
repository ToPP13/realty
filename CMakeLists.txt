cmake_minimum_required(VERSION 3.2)


if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(realty VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(realty VERSION 0.0.1)
endif ()

# Load settings for an external project.
find_package (Threads REQUIRED)
find_package (Boost COMPONENTS system regex REQUIRED)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)


# Copy a file to another location and modify its contents.
configure_file(version.h.in version.h)


add_executable(rclss rclss.cpp )
add_executable(rclst rclst.cpp )
# Add an executable to the project using the specified source files.


# Set propertiess to a target.
set_target_properties(realty PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Add include directories to a target.
# CMAKE_BINARY_DIR - The path to the top level of the build tree.
target_include_directories(rclss PRIVATE "${CMAKE_BINARY_DIR}" ${Boost_INCLUDE_DIRS})
target_include_directories(rclst PRIVATE "${CMAKE_BINARY_DIR}" ${Boost_INCLUDE_DIRS})

# Add include directories to the build.

target_link_libraries(rclss PRIVATE dl pthread ${Boost_LIBRARIES})
target_link_libraries(rclst PRIVATE dl pthread ${Boost_LIBRARIES})

# Add compile options to a target.
if (MSVC)
    target_compile_options(rclss PRIVATE
        /W4
    )
    target_compile_options(rclst PRIVATE
            /W4
            )
else ()    
    target_compile_options(rclss PRIVATE
        -Wall -Wextra  -pedantic -Werror
    )
    target_compile_options(rclst PRIVATE
            -Wall -Wextra  -pedantic -Werror
            )
endif()



# Load and run CMake code from a file or module.
install(TARGETS realty RUNTIME DESTINATION bin)

# Set a CMake, cache or environment variable to a given value.
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT martynovich@protei.ru)

include(CPack)

