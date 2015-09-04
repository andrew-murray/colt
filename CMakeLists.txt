project(colt CXX)
cmake_minimum_required(VERSION 2.8)  

#------------------------------------------------------------------------------
# Boost include
#------------------------------------------------------------------------------

# Possible Boost options
# set(Boost_USE_STATIC_LIBS OFF) 
# set(Boost_USE_MULTITHREADED ON)  
# set(Boost_USE_STATIC_RUNTIME OFF) 

# This is really annoying, is this going to always be necessary now?
# Disable any boost linking, header-only should be fine
add_definitions(-DBOOST_ALL_NO_LIB=1)

add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
find_package(BOOST REQUIRED)

include_directories(${Boost_INCLUDE_DIR}) 

#------------------------------------------------------------------------------
# Add project main executable
#------------------------------------------------------------------------------

file(GLOB command_line_template_src
    "colt/src/*.hpp"
    "colt/src/*.h"
    "colt/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${command_line_template_src})

# currently use boost header-only
# target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

#------------------------------------------------------------------------------
# Add project test executable
#------------------------------------------------------------------------------

file(GLOB command_line_template_test
    "colt/test/*.hpp"
    "colt/test/*.h"
    "colt/test/*.cpp"
)

add_executable("${PROJECT_NAME}_test" ${command_line_template_test})

# currently use boost header-only
# target_link_libraries("${PROJECT_NAME}_test" ${Boost_LIBRARIES})
