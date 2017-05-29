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

	buffer = enquire_resp.from_buffer(std::move(buffer));

	if ( enquire_resp.get_id() != smpp::pdu::ENQUIRE_LINK_RESP ) return false;

	if ( enquire_resp.get_seqnum() != sequence_number ) return false;

	return true;
}

class tcp_client: public client {
public:
	tcp_client():
		client("127.0.0.1", 2775) {
	}

	void run() override {

	}

protected:
	void on_connect() override {
		BOOST_TEST_MESSAGE( "OnConnect Call Inside tcp_client!!" );
	}

	void on_disconnect() override {
		BOOST_TEST_MESSAGE( "OnDisconnect Call Inside tcp_client!!" );
	}
};

BOOST_AUTO_TEST_CASE(tcp_connection_test) {

	BOOST_TEST_CHECKPOINT("Starting");

	tcp_client tcp_connection;

	BOOST_CHECK( tcp_connection.connect() );

	bind_transceiver transceiver("smppclient1", "password", 1);

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

	unbind_reply.from_buffer(tcp_connection.read());

	BOOST_CHECK_MESSAGE( unbind_reply.get_length() == 16 , "unbind_resp length doesn't match 16 = "<<unbind_reply.get_length() );
	BOOST_CHECK_MESSAGE( unbind_reply.get_seqnum() == 1234 , "unbind_resp sequence number doesn't match 1234 = "<<unbind_reply.get_seqnum() );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




