
add_executable(pdu_tests pdu_tests.cpp ${PDU_SOURCES} ${UTILS_SOURCES})
add_executable(network_tests network_tests.cpp ${PDU_SOURCES} ${UTILS_SOURCES})
add_executable(tcp_server_tests tcp_server_tests.cpp ${PDU_SOURCES} ${UTILS_SOURCES})
add_executable(outbind_smpp_tests outbind_smpp_tests.cpp ${PDU_SOURCES} ${UTILS_SOURCES})
add_executable(buffer_test buffer_test.cpp ${PDU_SOURCES} ${UTILS_SOURCES})

target_link_libraries(pdu_tests boost_atomic boost_log_setup boost_log boost_system pthread rt boost_thread boost_unit_test_framework utils_network smpp)
target_link_libraries(network_tests boost_atomic boost_log_setup boost_log boost_system pthread rt boost_thread boost_unit_test_framework utils_network smpp)
target_link_libraries(tcp_server_tests boost_atomic boost_log_setup boost_log boost_system pthread rt boost_thread boost_unit_test_framework utils_network smpp)
target_link_libraries(outbind_smpp_tests boost_atomic boost_log_setup boost_log boost_system pthread rt boost_thread boost_unit_test_framework utils_network smpp)
target_link_libraries(buffer_test boost_atomic boost_log_setup boost_log boost_system pthread rt boost_thread boost_unit_test_framework utils_network smpp)

install(TARGETS pdu_tests network_tests tcp_server_tests
		RUNTIME DESTINATION ../bin)
