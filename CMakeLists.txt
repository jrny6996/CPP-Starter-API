
cmake_minimum_required(VERSION 3.14)
project(CrowApp)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch CrowCpp
include(FetchContent)

FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.3.0
)

FetchContent_MakeAvailable(crow)

# Find required packages (Boost and OpenSSL)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)


# Add your executable
add_executable(Server src/main.cpp)

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
  GIT_TAG 7.10.4  
)

FetchContent_MakeAvailable(libpqxx)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 12.1.0  
)
FetchContent_MakeAvailable(fmt)


# find_package(sodium REQUIRED)


# Link Crow and OpenSSL
target_link_libraries(Server PRIVATE Crow::Crow OpenSSL::SSL OpenSSL::Crypto libpqxx::pqxx fmt::fmt)
target_include_directories(Server PRIVATE ${boost_redis_SOURCE_DIR}/include)

configure_file(
    ${CMAKE_SOURCE_DIR}/src/tailwind.config.js
    ${CMAKE_BINARY_DIR}/tailwind.config.js
    COPYONLY
)

configure_file(
    ${CMAKE_SOURCE_DIR}/.env
    ${CMAKE_BINARY_DIR}/.env
    COPYONLY
)

configure_file(
    ${CMAKE_SOURCE_DIR}/src/watch_fs.sh
    ${CMAKE_BINARY_DIR}/watch.sh
    COPYONLY
)



add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/templates
        ${CMAKE_CURRENT_BINARY_DIR}/templates
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/static
        ${CMAKE_CURRENT_BINARY_DIR}/static
    COMMENT "Copying templates and static directories"
)

# Make sure the executable depends on the resources being copied
add_dependencies(Server copy_resources)