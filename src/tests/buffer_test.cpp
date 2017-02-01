/*
 * network_tests.cpp
 *
 *  Created on: Dec 25, 2016
 *      Author: jamil
 */




#define BOOST_TEST_MODULE network buffer tests
#include <exception>
#include <boost/test/auto_unit_test.hpp>
#include "../utils/network/tcp/client.h"
#include "../smpp/pdu/bind_pdu.h"
#include "../smpp/pdu/unbind.h"
#include "../smpp/pdu/enquire_link.h"

using namespace utils::network;


using namespace std;



BOOST_AUTO_TEST_SUITE(buffer_tests_suit)

buffer_type3 create_buffer (uint32_t size) {
	return buffer_type3(size);
}

BOOST_AUTO_TEST_CASE(coctet_test) {
	BOOST_TEST_CHECKPOINT("Starting");

	coctet<16> system_id("ufone");
	coctet<16> another_id;

	auto buffer = buffer_type(16);
	buffer += system_id;
	buffer.reset();
	another_id += buffer;

	BOOST_CHECK_MESSAGE( strcmp(another_id.get(), "ufone") == 0 , " system_id and another_id doesn't match" );

	BOOST_TEST_CHECKPOINT("Ending");

}

class test_packet: public packet {
	coctet<16> system_id;
	uint32_t command_id;
public:

	test_packet(): command_id(0) {
	}

	test_packet(std::string system_id, uint32_t command_id):
		system_id(system_id),
		command_id(command_id) {
	}

	virtual buffer_type to_buffer() override {
		auto buffer = buffer_type(system_id.length() + sizeof(command_id));

		buffer += system_id;
		buffer += command_id;

		return buffer;
	}

	virtual buffer_type from_buffer(buffer_type buffer) override {

		system_id += buffer;
		command_id += buffer;

		return buffer;
	}

	bool test_systemid(std::string str) {
		return strcmp(str.c_str(), system_id.get()) == 0;
	}

	bool test_commandid(uint32_t command_id) {
		return this->command_id == command_id;
	}

	~test_packet() {}

};

bool handle_exception( std::exception const& ex ) {
	BOOST_TEST_MESSAGE( ex.what() );
	if ( typeid(ex) == typeid(std::logic_error) )
		return true;
	return false;
}

BOOST_AUTO_TEST_CASE(packet_to_and_from_buffer_test) {
	BOOST_TEST_CHECKPOINT("Testing packet copy from buffer");
	std::string test_sysid = "ufone";
	uint32_t test_commid = 0x8F8F8F8F;
	test_packet pack1(test_sysid, test_commid);


	test_packet pack2;
	auto buffer = pack1.to_buffer();
	BOOST_CHECK_MESSAGE( buffer != nullptr , "buffer is null" );
	buffer.reset();
	pack2.from_buffer(std::move(buffer));	//when lvalue buffer is used, use with std::move

	//checking population of coctet from string
	BOOST_CHECK_MESSAGE( pack2.test_systemid(test_sysid) , " system_id doesn't match" );
	BOOST_CHECK_MESSAGE( pack2.test_commandid(test_commid) , "command_id doesn't match" );

	BOOST_TEST_CHECKPOINT("Ending ... Testing packet copy from buffer");
}

BOOST_AUTO_TEST_CASE(packet_implementation_test) {
	BOOST_TEST_CHECKPOINT("Starting");

	std::string test_sysid = "ufone";
	uint32_t test_commid = 0x8F8F8F8F;
	test_packet pack(test_sysid, test_commid);

	//checking population of coctet from string
	BOOST_CHECK_MESSAGE( pack.test_systemid(test_sysid) , " system_id doesn't match" );
	BOOST_CHECK_MESSAGE( pack.test_commandid(test_commid) , "command_id doesn't match" );

	//checking population of coctet and uint32_t from buffer obtained from packet
	auto buffer = pack.to_buffer();
	buffer.reset();
	coctet<16> system_id;
	system_id += buffer;
	uint32_t command_id;
	command_id += buffer;
	uint32_t exception_test;


	BOOST_CHECK_MESSAGE( buffer.length() == (system_id.length() + sizeof(command_id)) , " length of buffer doesn't match the desired length" );
	BOOST_CHECK_MESSAGE( strcmp(test_sysid.c_str(), system_id.get()) == 0 , " copying back system_id from buffer doesn't match" );
	BOOST_CHECK_MESSAGE( command_id == test_commid , "copying back command_id from buffer doesn't match" );
	BOOST_CHECK_EXCEPTION( exception_test += buffer, std::exception, handle_exception );



	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_CASE(buffer_test) {

	BOOST_TEST_CHECKPOINT("Starting");


	//testing with buffer type two memory handled explicitly
	{
		auto mybuffer = buffer_type2(10000);
		auto another = buffer_type2();

		//comparision tests

		BOOST_CHECK_MESSAGE( mybuffer != nullptr, " == allocated memory for buffer 1" );
		BOOST_CHECK_MESSAGE( another == nullptr, " != allocated memory for buffer 2" );

		//move construction test
		auto mvconst = std::move(mybuffer);
		BOOST_CHECK_MESSAGE( mybuffer == nullptr, " move constructor mybuffer should be nullptr" );
		BOOST_CHECK_MESSAGE( mvconst != nullptr, " move constructor mvconst should be  not null" );

		//move assignment test
		another = std::move(mvconst);
		BOOST_CHECK_MESSAGE( mvconst == nullptr, " move constructor mybuffer should be nullptr" );
		BOOST_CHECK_MESSAGE( another != nullptr, " move constructor mvconst should be  not null" );
	}

	//testing buffer_type3 memory handled with unique_ptr as buffer
	{
		auto mybuffer = create_buffer(10000);
		auto another = buffer_type3();

		//comparision tests

		BOOST_CHECK_MESSAGE( mybuffer != nullptr, " == allocated memory for buffer 1" );
		BOOST_CHECK_MESSAGE( another == nullptr, " != allocated memory for buffer 2" );

		//comparision tests with nullptr on the left side
		BOOST_CHECK_MESSAGE( nullptr != mybuffer , " == allocated memory for buffer 1" );
		BOOST_CHECK_MESSAGE( nullptr == another , " != allocated memory for buffer 2" );

		//move construction test
		auto mvconst = std::move(mybuffer);
		BOOST_CHECK_MESSAGE( mybuffer == nullptr, " move constructor mybuffer should be nullptr" );
		BOOST_CHECK_MESSAGE( mvconst != nullptr, " move constructor mvconst should be  not null" );

		//move assignment test
		another = std::move(mvconst);
		BOOST_CHECK_MESSAGE( mvconst == nullptr, " move constructor mybuffer should be nullptr" );
		BOOST_CHECK_MESSAGE( another != nullptr, " move constructor mvconst should be  not null" );

		//copy data += test
		another += uint32_t(1);
		another += int32_t(2);
		another += int8_t(4);
		another += uint8_t(8);
		another += int16_t(-4);
		another += uint16_t(8);
//		another += int64_t(16);
//		another += uint64_t(32);

		{
			uint32_t a = 0;
			::memcpy(&a, &another[0], sizeof(a));
			a = ntohl(a);
			BOOST_CHECK_MESSAGE( a == 1, "uint32_t value assigned isn't comparable to 1");
		}

		{
			int32_t a = 0;
			::memcpy(&a, &another[4], sizeof(a));
			a = ntohl(a);
			BOOST_CHECK_MESSAGE( a == 2, "int32_t value assigned isn't comparable to 2");
		}

		{
			int8_t a = 0;
			::memcpy(&a, &another[8], sizeof(a));
			BOOST_CHECK_MESSAGE( a == 4, "int8_t value assigned isn't comparable to 4");
		}

		{
			uint8_t a = 0;
			::memcpy(&a, &another[9], sizeof(a));
			BOOST_CHECK_MESSAGE( a == 8, "uint32_t value assigned isn't comparable to 8");
		}

		{
			int16_t a = 0;
			::memcpy(&a, &another[10], sizeof(a));
			a = ntohs(a);
			BOOST_CHECK_MESSAGE( a == -4 , "int16_t value assigned isn't comparable to -4");
		}

		{
			uint16_t a = 0;
			::memcpy(&a, &another[12], sizeof(a));
			a = ntohs(a);
			BOOST_CHECK_MESSAGE( a == 8 , "uint16_t value assigned isn't comparable to 8");
		}

//		{
//			int32_t a = 0;
//			::memcpy(&a, &another[10], sizeof(a));
//			BOOST_CHECK_MESSAGE( a == 16, "int32_t value assigned is comparable to 16");
//		}
//
//		{
//			int8_t a = 0;
//			::memcpy(&a, &another[18], sizeof(a));
//			BOOST_CHECK_MESSAGE( a == 32, "int8_t value assigned is comparable to 32");
//		}

		another.reset();

		{
			uint32_t a = 0;
			a += another;
			BOOST_CHECK_MESSAGE( a == 1, "uint32_t value assigned isn't comparable to 1");
		}

		{
			int32_t a = 0;
			a += another;
			BOOST_CHECK_MESSAGE( a == 2, "int32_t value assigned isn't comparable to 2");
		}

		{
			int8_t a = 0;
			a += another;
			BOOST_CHECK_MESSAGE( a == 4, "int8_t value assigned isn't comparable to 4");
		}

		{
			uint8_t a = 0;
			a += another;
			BOOST_CHECK_MESSAGE( a == 8, "uint32_t value assigned isn't comparable to 8");
		}

		{

			int16_t a = 0;
			a += another;
			BOOST_CHECK_MESSAGE( a == -4 , "int16_t value assigned isn't comparable to -4");
		}

		{
			uint16_t a = 0;
			a += another;
			BOOST_CHECK_MESSAGE( a == 8 , "uint16_t value assigned isn't comparable to 8");
		}

	}


	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




