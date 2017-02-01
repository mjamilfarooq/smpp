add_subdirectory(pdu)
add_subdirectory(session)

add_library(smpp SHARED ${PDU_SOURCES} ${SESSION_SOURCES})

target_link_libraries(smpp utils_network)