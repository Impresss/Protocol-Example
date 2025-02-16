cmake_minimum_required(VERSION 3.5)

project(Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Client
    main.cpp
    ocp_protocol.h
)


install(TARGETS Client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
