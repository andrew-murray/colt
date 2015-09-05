project(colt CXX)
cmake_minimum_required(VERSION 2.8)  

#------------------------------------------------------------------------------
# Boost include
#------------------------------------------------------------------------------

# Possible Boost options
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

# For some reason, this capitalized version gets totally
# different behaviour, though it calls the same script.
# Thanks CMAKE! This is in part intentional ... but I can't believe
# this is the best option.
# set(Boost_DEBUG ON)
# set(Boost_FIND_QUIETLY OFF)
# find_package(BOOST
#              1.55.0
#              COMPONENTS program_options
# 						system
#              REQUIRED)
			 
add_definitions( -DBOOST_ALL_NO_LIB )
add_definitions( -DBOOST_ALL_DYN_LINK )
find_package(Boost
            1.55.0
            COMPONENTS program_options
					system
            REQUIRED)

include_directories(${Boost_INCLUDE_DIR}) 
link_directories(${BOOST_LIBRARYDIR})

file(GLOB_RECURSE BOOST_DLLS "${BOOST_LIBRARYDIR}/*.dll")
file(COPY ${BOOST_DLLS} DESTINATION ${PROJECT_BINARY_DIR})

#------------------------------------------------------------------------------
# Add project main executable
#------------------------------------------------------------------------------

include_directories(${PROJECT_SOURCE_DIR}) 

file(GLOB command_line_template_src
    "colt/src/*.hpp"
    "colt/src/*.h"
    "colt/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${command_line_template_src})

# currently use boost header-only
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

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
target_link_libraries("${PROJECT_NAME}_test" ${Boost_LIBRARIES})


		