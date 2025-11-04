
cmake_minimum_required(VERSION 3.14)
project(CrowApp)

# Use C++17
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch CrowCpp
include(FetchContent)

FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.0+4  # You can choose the latest tag or commit
)

FetchContent_MakeAvailable(crow)

# Find required packages (Boost and OpenSSL)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)


# Add your executable
add_executable(Server src/main.cc)

# Redis
FetchContent_Declare(
  boost_redis
  GIT_REPOSITORY https://github.com/boostorg/redis.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(boost_redis)

# Postgres Driver
FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG 7.9.0  # or latest stable release
)

FetchContent_MakeAvailable(libpqxx)


# Link Crow and OpenSSL
target_link_libraries(Server PRIVATE Crow::Crow OpenSSL::SSL OpenSSL::Crypto pqxx)
target_include_directories(Server PRIVATE ${boost_redis_SOURCE_DIR}/include)

# Copy static and template directories into the build directory
add_custom_command(TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/templates
        ${CMAKE_CURRENT_BINARY_DIR}/templates
)

add_custom_command(TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/static
        ${CMAKE_CURRENT_BINARY_DIR}/static
)
