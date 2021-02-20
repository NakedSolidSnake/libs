cmake_minimum_required(VERSION 3.7.0)

project(rasp_rover)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# This one is important
SET(CMAKE_SYSTEM_NAME Linux)

# Specify the cross compiler
#SET(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
#SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

include(GNUInstallDirs)


function(add_test_unit BIN_NAME BIN SOURCE)
  add_executable(${BIN} ${SOURCE})
  set_target_properties(${BIN}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_lib
    )
    add_test(NAME ${BIN_NAME} COMMAND ${BIN})
endfunction()

enable_testing()

# ipc library
add_library(ipc SHARED "")
target_sources(ipc 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/log/log.c
  ${CMAKE_CURRENT_LIST_DIR}/src/file/file.c
  ${CMAKE_CURRENT_LIST_DIR}/src/queue/queue.c
  ${CMAKE_CURRENT_LIST_DIR}/src/signal/signal.c
  ${CMAKE_CURRENT_LIST_DIR}/src/sharedmemory/sharedmemory.c
  ${CMAKE_CURRENT_LIST_DIR}/src/semaphore/semaphore.c
  )
target_include_directories(ipc 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  )

# comm library 
add_library(comm SHARED "")

target_sources(comm 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/server/server_tcp.c
  )
target_include_directories(comm 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  )

# util library 
add_library(util SHARED "")
target_sources(util 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/util/time_meas.c
  )
target_include_directories(util 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  )

# collection
add_library(collection SHARED "")
target_sources(collection 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/collection/list_static.c  
  )
target_include_directories(collection 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  )

# database
add_library(database SHARED "")
target_link_libraries(database PUBLIC mysqlclient)
target_sources(database 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/database/database.c  
  )
target_include_directories(database 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  /usr/include/mysql
  )

# json
add_library(json SHARED "")
target_link_libraries(json PUBLIC json-c)
target_sources(json 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/json/json.c  
  )
target_include_directories(json 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  )

#------------------------------------------------------------------------------------------------------
# Tests
#------------------------------------------------------------------------------------------------------
add_test_unit(time_meas test_time_meas test_lib/test_time_meas.c)
target_link_libraries(test_time_meas PUBLIC util)

add_test_unit(server_tcp test_server_tcp test_lib/test_servertcp.c)
target_link_libraries(test_server_tcp PUBLIC comm)

add_test_unit(semaphore test_semaphore test_lib/test_semaphore.c)
target_link_libraries(test_semaphore PUBLIC ipc)

add_test_unit(static_list test_static_list test_lib/test_list_static.c)
target_link_libraries(test_static_list PUBLIC collection)


#------------------------------------------------------------------------------------------------------
# Install
#------------------------------------------------------------------------------------------------------
install(DIRECTORY include/collection   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/file         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/log          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/queue        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/semaphore    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/server       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/sharedmemory DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/signal       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/util         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/database     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/json     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS  util ipc comm database collection json LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})