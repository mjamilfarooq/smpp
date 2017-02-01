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
	smpp::pdu::pdu mypdu(smpp::pdu::GENERIC_NACK, 1);

	auto teststatus = uint32_t(0x12345678);
	auto testsequence = 0x89ABCDEF;
	mypdu.set_status(teststatus);
	mypdu.set_seqnum(testsequence);

	//testing initialization
	BOOST_CHECK( mypdu.get_length() == 16 );
	BOOST_CHECK( mypdu.get_id() == smpp::pdu::GENERIC_NACK );
	BOOST_CHECK( teststatus == mypdu.get_status() );
	BOOST_CHECK( mypdu.get_seqnum() == testsequence );
	BOOST_CHECK( mypdu.get_length() == 16 );

	//testing buffer copy
	auto buffer = mypdu.to_buffer();
	buffer.reset();
	uint32_t command_length, command_id, command_status, sequence_number;

	command_length += buffer;
	command_id += buffer;
	command_status += buffer;
	sequence_number += buffer;

	BOOST_CHECK_MESSAGE( command_length == mypdu.get_length(), "command_length in test pdu "<<mypdu.get_length()<<" command_length in buffer "<<command_length );
	BOOST_CHECK_MESSAGE( command_id == mypdu.get_id(), std::hex<<"command_id in test pdu "<<mypdu.get_id()<<" command_id in buffer "<<command_id );
	BOOST_CHECK_MESSAGE( command_status == mypdu.get_status(), std::hex<<"command_status in test pdu "<<mypdu.get_status()<<" command_status in buffer "<<command_status );
	BOOST_CHECK_MESSAGE( sequence_number == mypdu.get_seqnum(), std::hex<<"sequence_number in test pdu "<<mypdu.get_seqnum()<<" sequence_number in buffer "<<sequence_number );


	//testing pdu generation from buffer
	smpp::pdu::pdu another_pdu(0, 1);
	buffer.reset();
	another_pdu.from_buffer(std::move(buffer));

	BOOST_CHECK_MESSAGE( another_pdu.get_length() == mypdu.get_length() , "command length for pdu populated from buffer "<<another_pdu.get_length() );
	BOOST_CHECK( another_pdu.get_id() == mypdu.get_id() );
	BOOST_CHECK( another_pdu.get_status() == mypdu.get_status() );
	BOOST_CHECK( another_pdu.get_seqnum() == mypdu.get_seqnum() );
	BOOST_CHECK( another_pdu.get_length() == 16 );

	BOOST_TEST_CHECKPOINT("Ending");
}


BOOST_AUTO_TEST_CASE(bind_pdu_tests)
{
	BOOST_TEST_CHECKPOINT("Starting");

	smpp::pdu::bind_transceiver trans("smppclient1", "password", 1);

	BOOST_CHECK_MESSAGE( strcasecmp(trans.get_systemid(), "smppclient1") == 0 , "system_id : "<<trans.get_systemid());
	BOOST_CHECK_MESSAGE( strcasecmp(trans.get_password(), "password") == 0 , "password : "<<trans.get_password() );
	BOOST_CHECK( strcasecmp(trans.get_systemtype(), "") == 0 );
	BOOST_CHECK( trans.get_interface_version() == smpp::SMPP_VERSION_0x33 );
	BOOST_CHECK( trans.get_addr_ton() == smpp::address::TON_UNKNOWN );
	BOOST_CHECK( trans.get_addr_npi() == smpp::address::NPI_UNKNOWN );
	BOOST_CHECK( strcasecmp(trans.get_address_range(), "") == 0 );
	BOOST_TEST_MESSAGE( "length of bind_transceiver " << trans.get_length() <<" buffer length " );

	auto buffer = trans.to_buffer();
	buffer.reset();

	smpp::pdu::bind_transceiver another_trans;
	buffer = another_trans.from_buffer(std::move(buffer));
	BOOST_CHECK_MESSAGE( buffer.length() == trans.get_length() , "length "<<trans.get_length()<<" buffer offset "<<buffer.length() );
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

	smpp::pdu::bind_transceiver_resp trans("smppclient1", 1);

	BOOST_CHECK_MESSAGE( trans.get_id() == smpp::pdu::BIND_TRANSCEIVER_RESP , "command_id : "<<trans.get_id());
	BOOST_CHECK_MESSAGE( strcasecmp(trans.get_systemid(), "smppclient1") == 0 , "system_id : "<<trans.get_systemid() );
	BOOST_CHECK_MESSAGE( trans.get_version() != 0 , "transceiver version isn't null" );

	auto buffer = trans.to_buffer();

	BOOST_CHECK_MESSAGE( strcasecmp(reinterpret_cast<char *>(buffer.get())+16, "smppclient1") == 0 , "system_id from buffer"<<buffer.length() );
	BOOST_CHECK_MESSAGE( buffer.length() == trans.get_length() , "length "<<trans.get_length()<<" buffer offset "<<buffer.length() );

	smpp::pdu::bind_transceiver_resp another_trans;
	buffer.reset();
	buffer = another_trans.from_buffer(std::move(buffer));

	BOOST_CHECK_MESSAGE( another_trans.get_length() == strlen("smppclient1")+1+16 , "command_length : "<<another_trans.get_length());
	BOOST_CHECK_MESSAGE( another_trans.get_id() == smpp::pdu::BIND_TRANSCEIVER_RESP , "command_id : "<<another_trans.get_id());
	BOOST_CHECK_MESSAGE( another_trans.get_status() == 0 , "command_status : "<<another_trans.get_status());
	BOOST_CHECK_MESSAGE( another_trans.get_seqnum() == 0 , "sequence_number : "<<another_trans.get_seqnum());
	BOOST_CHECK_MESSAGE( strcasecmp(another_trans.get_systemid(), "smppclient1") == 0 , "system_id : "<<another_trans.get_systemid());

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()
