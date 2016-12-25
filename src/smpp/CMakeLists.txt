add_subdirectory(pdu)

add_library(smpp SHARED ${PDU_SOURCES})

target_link_libraries(smpp utils_network)