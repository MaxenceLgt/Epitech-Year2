CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(LIB_NAME plan)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#find_package(SFML COMPONENTS system window graphics REQUIRED)
#find_package(SDL2 REQUIRED)

#target_include_directories(${PROJECT_SOURCE_DIR}/common) # local include

#include_directories(${PROJECT_SOURCE_DIR}/common) # global include


#add_executable(${LIB_NAME} main.cpp)
add_library(${LIB_NAME} SHARED Plan.cpp)


TARGET_LINK_LIBRARIES(${LIB_NAME} config++)
set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")


add_custom_command(TARGET ${LIB_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${LIB_NAME}>
        ${PROJECT_SOURCE_DIR}/plugins/$<TARGET_FILE_NAME:${LIB_NAME}>)
