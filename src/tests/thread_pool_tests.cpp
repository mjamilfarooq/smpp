/*
 * tcp_server_tests.cpp
 *
 *  Created on: Dec 26, 2016
 *      Author: jamil
 */




#define BOOST_TEST_MODULE first test
#include <boost/test/auto_unit_test.hpp>
#include <iostream>

#include "../utils/thread_pool/thread_pool.h"


using namespace utils;
using namespace std;


//bool check_exception(std::system_error const &e) { return e.what() == "example"; }

BOOST_AUTO_TEST_SUITE(thread_pool_tests)

class task{
	int a;
	float b;
public:
	task(int a, float b): a(a), b(b) {

	}

	void operator()(){
		cout<<"a is "<<a<<" b is "<<b<<endl;
	}


};

BOOST_AUTO_TEST_CASE(thread_pool_testcase1) {

	BOOST_TEST_CHECKPOINT("Starting");


	thread_pool<task> pool(3);
	task a(1, 3.1);
	task b(2, 4.1);
	task c(3, 5.1);

	pool.push(a);
	pool.push(b);
	pool.push(c);


	getchar();
//	telnet_connection telnet_server(49000);
////	BOOST_CHECK_EXCEPTION(telnet_server.connect() , std::system_error, check_exception );
//	telnet_server.connect();
//	BOOST_CHECK_EXCEPTION( telnet_server.wait() , std::system_error, [](std::system_error const &e){
//		std::cout<<e.what()<<e.code()<<e.code().message()<<std::endl;
//		return e.code().value() > 0;
//	});
////	BOOST_CHECK_MESSAGE( result , "Couldn't connect to outbind connection!!" );
//
//
//
//	getchar();
//
//	BOOST_CHECK( true );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




