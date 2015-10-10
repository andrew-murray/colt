project(colt CXX)
cmake_minimum_required(VERSION 2.8)  

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#------------------------------------------------------------------------------
# Boost include
#------------------------------------------------------------------------------

# Possible Boost options
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

add_definitions( -DBOOST_ALL_NO_LIB )
add_definitions( -DBOOST_ALL_DYN_LINK )

find_package(Boost
            1.55.0
            COMPONENTS program_options
					system
					unit_test_framework
            REQUIRED)

if(NOT DEFINED Boost_FOUND OR NOT ${Boost_FOUND})
    message(SEND_ERROR "Failed to find Boost")
    return()
endif()

include_directories(${Boost_INCLUDE_DIR}) 

# Unfortunately, I observed FindBoost seems to set 
# either Release & Debug or just LibraryDir
# so link both

link_directories(${Boost_LIBRARYDIR})
link_directories(${Boost_LIBRARY_DIR_RELEASE})
link_directories(${Boost_LIBRARY_DIR_DEBUG})

file(GLOB BOOST_DLLS "${Boost_LIBRARYDIR}/*.dll")
file(COPY ${BOOST_DLLS} DESTINATION ${PROJECT_BINARY_DIR})
file(GLOB BOOST_DLLS_RELEASE "${Boost_LIBRARY_DIR_RELEASE}/*.dll")
file(COPY ${BOOST_DLLS_RELEASE} DESTINATION ${PROJECT_BINARY_DIR})
file(GLOB BOOST_DLLS_DEBUG "${Boost_LIBRARY_DIR_debug}/*.dll")
file(COPY ${BOOST_DLLS_DEBUG} DESTINATION ${PROJECT_BINARY_DIR})

#------------------------------------------------------------------------------
# Add project main executable
#------------------------------------------------------------------------------

include_directories(${PROJECT_SOURCE_DIR}) 

file(GLOB command_line_template_example
    "colt/example/*.hpp"
    "colt/example/*.h"
    "colt/example/*.cpp"
)

add_executable(${PROJECT_NAME}_example ${command_line_template_example})
target_link_libraries(${PROJECT_NAME}_example ${Boost_PROGRAM_OPTIONS_LIBRARY} ${BOOST_SYSTEM_LIBRARY})

#------------------------------------------------------------------------------
# Add project test executable
#------------------------------------------------------------------------------

file(GLOB command_line_template_test
    "colt/test/*.hpp"
    "colt/test/*.h"
    "colt/test/*.cpp"
)

add_executable("${PROJECT_NAME}_test" ${command_line_template_test})
target_link_libraries("${PROJECT_NAME}_test" ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${BOOST_SYSTEM_LIBRARY})

		
