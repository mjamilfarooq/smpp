/*
 * network_tests.cpp
 *
 *  Created on: Dec 25, 2016
 *      Author: jamil
 */




#define BOOST_TEST_MODULE network connection tests
#include <boost/test/auto_unit_test.hpp>
#include "../utils/network/tcp/client.h"
#include "../smpp/pdu/bind_pdu.h"
#include "../smpp/pdu/unbind.h"
#include "../smpp/pdu/enquire_link.h"

using namespace utils::network::tcp;
using namespace smpp::pdu;
using namespace std;



BOOST_AUTO_TEST_SUITE(network_tests_suit)


bool enquire_test(client& tcp_connection, uint32_t sequence_number) {
	enquire_link enquire_req(sequence_number);
	if ( true != tcp_connection.write(enquire_req.to_buffer()) ) return false;

	pdu enquire_resp;
	auto buffer = tcp_connection.read();

	if ( buffer_null == buffer) return false;

	if ( 16 != enquire_resp.from_buffer(buffer) ) return false;

	if ( enquire_resp.get_id() != smpp::pdu::ENQUIRE_LINK_RESP ) return false;

	if ( enquire_resp.get_seqnum() != sequence_number ) return false;

	return true;
}

BOOST_AUTO_TEST_CASE(tcp_connection_test) {

	BOOST_TEST_CHECKPOINT("Starting");

	client tcp_connection("127.0.0.1", 2775);

	BOOST_CHECK( tcp_connection.connect() );

	bind_transceiver transceiver("smppclient1", "password");

	tcp_connection.write(transceiver.to_buffer());

	bind_pdu trans_resp;
	trans_resp.from_buffer(tcp_connection.read());


	BOOST_CHECK_MESSAGE( trans_resp.get_id() == smpp::pdu::BIND_TRANSCEIVER_RESP , "command_id : "<<trans_resp.get_id());
	BOOST_CHECK_MESSAGE( trans_resp.get_status() == 0 , "command_status : "<<trans_resp.get_status());
	BOOST_CHECK_MESSAGE( strcasecmp(trans_resp.get_systemid(), "SMPPSim") == 0 , "system_id : "<<trans_resp.get_systemid());

	BOOST_CHECK_MESSAGE( enquire_test(tcp_connection, 1234) , "enquire link test failed!" );


	unbind unbind_req(1234);
	tcp_connection.write(unbind_req.to_buffer());

	pdu unbind_reply;
	auto read_reply = tcp_connection.read();

	BOOST_REQUIRE( read_reply != buffer_null );

	auto cmd_len = ntohl(*reinterpret_cast<uint32_t *>(read_reply.first.get()));
	auto cmd_id = ntohl(*reinterpret_cast<uint32_t *>(read_reply.first.get()+4));
	auto cmd_status = ntohl(*reinterpret_cast<uint32_t *>(read_reply.first.get()+8));
	auto cmd_seq = ntohl(*reinterpret_cast<uint32_t *>(read_reply.first.get()+12));

	BOOST_CHECK_MESSAGE( cmd_len == 16 , "cmd_len: "<<cmd_len );
	BOOST_CHECK_MESSAGE( cmd_id == smpp::pdu::UNBIND_RESP , "cmd_id: "<<cmd_id );
	BOOST_CHECK_MESSAGE( cmd_status == 0 , "cmd_status: "<<cmd_status );
	BOOST_CHECK_MESSAGE( cmd_seq == 1234 , "cmd_seq: "<<cmd_seq );


	unbind_reply.from_buffer(read_reply);

	BOOST_CHECK_MESSAGE( unbind_reply.get_length() == 16 , "unbind_resp length doesn't match 16 = "<<unbind_reply.get_length() );
	BOOST_CHECK_MESSAGE( unbind_reply.get_seqnum() == 1234 , "unbind_resp sequence number doesn't match 1234 = "<<unbind_reply.get_seqnum() );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




