/*
 * pdu_tests.cpp
 *
 *  Created on: Dec 24, 2016
 *      Author: jamil
 */




#define BOOST_TEST_MODULE first test
#include <boost/test/auto_unit_test.hpp>

#include "../smpp/pdu/pdu.h"
#include "../smpp/pdu/bind_pdu.h"

using namespace std;



BOOST_AUTO_TEST_SUITE(pdutester)

BOOST_AUTO_TEST_CASE(pdu_instantiation) {

	BOOST_TEST_CHECKPOINT("Starting");
	smpp::pdu::pdu mypdu(smpp::pdu::GENERIC_NACK);

	auto teststatus = 0x12345678;
	auto testsequence = 0x89ABCDEF;
	mypdu.set_status(teststatus);
	mypdu.set_seqnum(testsequence);

	//testing initialization
	BOOST_CHECK( mypdu.get_length() == 16 );
	BOOST_CHECK( mypdu.get_id() == smpp::pdu::GENERIC_NACK );
	BOOST_CHECK( mypdu.get_status() == teststatus );
	BOOST_CHECK( mypdu.get_seqnum() == testsequence );
	BOOST_CHECK( mypdu.get_length() == 16 );

	//testing buffer copy
	auto buffer = mypdu.to_buffer();
	auto start = buffer.first.get();

	auto command_length = ntohl(*((uint32_t *)start + 0));
	auto command_id = ntohl(*((uint32_t *)start + 1));
	auto command_status = ntohl(*((uint32_t *)start + 2));
	auto sequence_number = ntohl(*((uint32_t *)start + 3));

	BOOST_CHECK_MESSAGE( command_length == mypdu.get_length(), "command_length in test pdu "<<mypdu.get_length()<<" command_length in buffer "<<command_length );
	BOOST_CHECK_MESSAGE( command_id == mypdu.get_id(), std::hex<<"command_id in test pdu "<<mypdu.get_id()<<" command_id in buffer "<<command_id );
	BOOST_CHECK_MESSAGE( command_status == mypdu.get_status(), std::hex<<"command_status in test pdu "<<mypdu.get_status()<<" command_status in buffer "<<command_status );
	BOOST_CHECK_MESSAGE( sequence_number == mypdu.get_seqnum(), std::hex<<"sequence_number in test pdu "<<mypdu.get_seqnum()<<" sequence_number in buffer "<<sequence_number );


	//testing pdu generation from buffer
	smpp::pdu::pdu another_pdu(0);
	auto offset = another_pdu.from_buffer(buffer);

	BOOST_CHECK( offset == 16 );
	BOOST_CHECK_MESSAGE( another_pdu.get_length() == mypdu.get_length() , "command length for pdu populated from buffer "<<another_pdu.get_length() );
	BOOST_CHECK( another_pdu.get_id() == mypdu.get_id() );
	BOOST_CHECK( another_pdu.get_status() == mypdu.get_status() );
	BOOST_CHECK( another_pdu.get_seqnum() == mypdu.get_seqnum() );
	BOOST_CHECK( another_pdu.get_length() == 16 );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_CASE(coctet_test)
{
	BOOST_TEST_CHECKPOINT("Starting");

	char system_id[16];

	char* sample1 = "thisissamplestringcontainingmanyvalues";
	char* sample2 = "shorter";

	auto offset = utils::network::coctet_cpy(system_id, sample1, 16);

	BOOST_CHECK( offset == 16 );
	BOOST_CHECK_MESSAGE( strlen(system_id) == 15, "system_id length is: "<<strlen(system_id));
	BOOST_CHECK( system_id[15] == 0 );


	offset = utils::network::coctet_cpy(system_id, sample2, 16);

	BOOST_CHECK( offset == 8 );
	BOOST_CHECK( strlen(system_id) == 7 );
	BOOST_CHECK( system_id[7] == 0 );


	offset = utils::network::coctet_cpy(system_id, nullptr, 16);
	BOOST_CHECK( offset == 0);

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_CASE(bind_pdu_tests)
{
	BOOST_TEST_CHECKPOINT("Starting");

	smpp::pdu::bind_transceiver trans("smppclient1", "password");

	BOOST_CHECK_MESSAGE( strcasecmp(trans.get_systemid(), "smppclient1") == 0 , "system_id : "<<trans.get_systemid());
	BOOST_CHECK_MESSAGE( strcasecmp(trans.get_password(), "password") == 0 , "password : "<<trans.get_password() );
	BOOST_CHECK( strcasecmp(trans.get_systemtype(), "") == 0 );
	BOOST_CHECK( trans.get_interface_version() == smpp::SMPP_VERSION_0x33 );
	BOOST_CHECK( trans.get_addr_ton() == smpp::address::TON_UNKNOWN );
	BOOST_CHECK( trans.get_addr_npi() == smpp::address::NPI_UNKNOWN );
	BOOST_CHECK( strcasecmp(trans.get_address_range(), "") == 0 );

	auto buffer = trans.to_buffer();
	BOOST_CHECK_MESSAGE( buffer.second == trans.get_length() , "length "<<trans.get_length()<<" buffer offset "<<buffer.second );

	smpp::pdu::bind_transceiver another_trans;
	another_trans.from_buffer(buffer);

	BOOST_CHECK_MESSAGE( another_trans.get_id() == smpp::pdu::BIND_TRANSCEIVER , "command_id : "<<another_trans.get_id());
	BOOST_CHECK_MESSAGE( strcasecmp(another_trans.get_systemid(), "smppclient1") == 0 , "system_id : "<<another_trans.get_systemid());
	BOOST_CHECK_MESSAGE( strcasecmp(another_trans.get_password(), "password") == 0 , "password : "<<another_trans.get_password() );
	BOOST_CHECK( strcasecmp(another_trans.get_systemtype(), "") == 0 );
	BOOST_CHECK( another_trans.get_interface_version() == smpp::SMPP_VERSION_0x33 );
	BOOST_CHECK( another_trans.get_addr_ton() == smpp::address::TON_UNKNOWN );
	BOOST_CHECK( another_trans.get_addr_npi() == smpp::address::NPI_UNKNOWN );
	BOOST_CHECK( strcasecmp(another_trans.get_address_range(), "") == 0 );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_CASE(bind_pdu_resp_tests)
{
	BOOST_TEST_CHECKPOINT("Starting");

	smpp::pdu::bind_transceiver_resp trans("smppclient1");

	BOOST_CHECK_MESSAGE( trans.get_id() == smpp::pdu::BIND_TRANSCEIVER_RESP , "command_id : "<<trans.get_id());
	BOOST_CHECK_MESSAGE( strcasecmp(trans.get_systemid(), "smppclient1") == 0 , "system_id : "<<trans.get_systemid() );
	BOOST_CHECK_MESSAGE( trans.get_version() == nullptr , "transceiver version isn't null" );

	auto buffer = trans.to_buffer();

	BOOST_CHECK_MESSAGE( strcasecmp(reinterpret_cast<char *>(buffer.first.get())+16, "smppclient1") == 0 , "system_id from buffer"<<buffer.second );
	BOOST_CHECK_MESSAGE( buffer.second == trans.get_length() , "length "<<trans.get_length()<<" buffer offset "<<buffer.second );

	smpp::pdu::bind_transceiver_resp another_trans;
	auto buff_size = another_trans.from_buffer(buffer);


	BOOST_CHECK_MESSAGE( another_trans.get_id() == smpp::pdu::BIND_TRANSCEIVER_RESP , "command_id : "<<another_trans.get_id());
	BOOST_CHECK_MESSAGE( strcasecmp(another_trans.get_systemid(), "smppclient1") == 0 , "system_id : "<<another_trans.get_systemid());



	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()
