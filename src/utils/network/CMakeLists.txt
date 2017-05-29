add_subdirectory(tcp)

set(NETWORK_SOURCES 
    ${TCP_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/packet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/connection.h
    PARENT_SCOPE)