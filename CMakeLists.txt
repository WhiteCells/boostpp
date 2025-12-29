cmake_minimum_required(VERSION 3.10)

project(boostpp LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

set(BOOSTPP_SRC
    # main.cc
    include/async_request.cc
)

add_executable(${PROJECT_NAME} ${BOOSTPP_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE 
    /home/cells/dev/cpp-project/boostpp/3rd/boost
)

target_link_directories(${PROJECT_NAME} PRIVATE
    /home/cells/dev/cpp-project/boostpp/3rd/boost/stage/lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
)
