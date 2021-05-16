cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_COMPILER clang++)

project(dependency-graph)

include(FetchContent)

if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -g3")
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.x
)

# Adding Catch2 here
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()



include(CMakePrintHelpers)
include(ExternalProject)


#find_library(graphviz gvc
     #   HINT /usr/lib/x86_64-linux-gnu/graphviz)
#cmake_print_variables(graphviz)

include(FetchContent)
if(graphviz STREQUAL "graphviz-NOTFOUND")
        message(STATUS "HERE")
        FetchContent_Declare(graphviz
        GIT_REPOSITORY https://gitlab.com/graphviz/graphviz.git
        )
        FetchContent_MakeAvailable(graphviz)
	
endif()

# Source file list declaration
file(GLOB_RECURSE SOURCE_FILES src/core/*.cpp)


# GraphGenerator executable target
add_executable(GraphGenerator apps/graph_generator_main.cpp ${SOURCE_FILES})
target_include_directories(GraphGenerator PRIVATE include)

INCLUDE_DIRECTORIES(SYSTEM "/usr/include/graphviz/")
target_link_libraries(GraphGenerator PUBLIC cgraph gvc)


# target_link_libraries(test gvc)

# src: http://www.stablecoder.ca/2019/03/15/sorting-you-dependency-graph.html
# CMake is compatible with dependency graphs
# In the build folder, run "Make dependecy-graph"
# And it should build a png called dependency-checker

find_program(DOT_EXE "dot")
if(DOT_EXE)
    message(STATUS "dot found: ${DOT_EXE}")
else()
    message(STATUS "dot not found!")
endif()

set(DOT_OUTPUT_TYPE png) #"" CACHE STRING "Build a dependency graph. Options are dot output types: ps, png, pdf..." )

if(DOT_EXE)
    add_custom_target(dependency-graph
        COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} --graphviz=${CMAKE_BINARY_DIR}/graphviz/${PROJECT_NAME}.dot
        COMMAND ${DOT_EXE} -T${DOT_OUTPUT_TYPE} ${CMAKE_BINARY_DIR}/graphviz/${PROJECT_NAME}.dot -o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${DOT_OUTPUT_TYPE}
    )


    add_custom_command(
        TARGET dependency-graph POST_BUILD
        COMMAND ;
        COMMENT
        "Dependency graph generated and located at ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${DOT_OUTPUT_TYPE}"
    )
endif()

# Setting up parse
add_executable(parse apps/parse_main.cpp ${SOURCE_FILES})
target_include_directories(parse PRIVATE include)
target_link_libraries(parse PUBLIC cgraph gvc)

list(APPEND TEST_FILES
                    tests/test_fileexplorer.cpp
                    tests/test_textparser.cpp
                    tests/test_cycledetector.cpp
                    tests/test_graphgen.cpp)


add_executable(test tests/test_main.cpp ${TEST_FILES} ${SOURCE_FILES})
target_include_directories(test PRIVATE include)
target_link_libraries(test PRIVATE catch2)
target_link_libraries(test PUBLIC cgraph gvc)

add_executable(cycle apps/cycle_detector_main.cpp ${SOURCE_FILES})
target_include_directories(cycle PRIVATE include)
target_link_libraries(cycle PUBLIC cgraph gvc)

add_executable(CinderGraphGen apps/cinder_graph_gen_main.cpp ${SOURCE_FILES})
target_include_directories(CinderGraphGen PRIVATE include)
target_link_libraries(CinderGraphGen PUBLIC cgraph gvc)

project(DependencyChecker 
        LANGUAGES CXX
        VERSION 1.0)
