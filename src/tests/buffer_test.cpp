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

using namespace utils::network;

using namespace std;



BOOST_AUTO_TEST_SUITE(buffer_tests_suit)

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
		auto mybuffer = buffer_type3(10000);
		auto another = buffer_type3();

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

		//copy data += test
		another += uint32_t(1);
		another += int32_t(2);
		another += int8_t(4);
		another += uint8_t(8);
//		another += int64_t(16);
//		another += uint64_t(32);

		{
			uint32_t a = 0;
			::memcpy(&a, &another[0], sizeof(a));
			BOOST_CHECK_MESSAGE( a == 1, "uint32_t value assigned is comparable to 1");
		}

		{
			int32_t a = 0;
			::memcpy(&a, &another[4], sizeof(a));
			BOOST_CHECK_MESSAGE( a == 2, "int32_t value assigned is comparable to 2");
		}

		{
			int8_t a = 0;
			::memcpy(&a, &another[8], sizeof(a));
			BOOST_CHECK_MESSAGE( a == 4, "int8_t value assigned is comparable to 4");
		}

		{
			uint8_t a = 0;
			::memcpy(&a, &another[9], sizeof(a));
			BOOST_CHECK_MESSAGE( a == 8, "uint32_t value assigned is comparable to 8");
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




	}


	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




