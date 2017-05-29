

add_subdirectory(network)
add_subdirectory(thread_pool)

add_library(utils_network SHARED ${NETWORK_SOURCES})
