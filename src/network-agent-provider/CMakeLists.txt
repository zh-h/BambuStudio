cmake_minimum_required(VERSION 3.13)
project(network_agent_provider)

find_package(Boost 1.70 REQUIRED COMPONENTS
    log
    log_setup
    system
    filesystem
    thread
    date_time
    chrono
    atomic
)

add_executable(network_agent_provider
    NetworkAgentProvider.cpp
)

target_include_directories(network_agent_provider PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(network_agent_provider PRIVATE
    Boost::log
    Boost::log_setup
    Boost::system
    Boost::filesystem
    Boost::thread
    Boost::date_time
    Boost::chrono
    Boost::atomic
)