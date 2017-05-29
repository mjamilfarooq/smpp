/*
 * tcp_server_tests.cpp
 *
 *  Created on: Dec 26, 2016
 *      Author: jamil
 */




#define BOOST_TEST_MODULE smpp session tests
#include <boost/test/auto_unit_test.hpp>
#include <iostream>

#include "../smpp/session/session.h"

using namespace utils::network::tcp;
using namespace smpp::session;
using namespace std;

BOOST_AUTO_TEST_SUITE(smpp_session_tests)

class smpp_client_session: public session, public client {
public:
	smpp_client_session(const configuration& config):
		session(config),
		client(config.ip, config.port) {
	}


	virtual void run() override {

		while ( true ) {

		}
	}

protected:
	//tcp client overloads
	void on_connect() override final {


		BOOST_CHECK_MESSAGE( bind(dynamic_cast<connection::pointer>(this)) ,
				" override on_connect method for smpp_client_session called " );

//		std::async(std::launch::async, &smpp_client_session::run, this);
	}

	void on_disconnect() override final {
		unbind();
		BOOST_CHECK_MESSAGE( true, " override on_disconnect method for smpp_client_session called " );
	}

	//smpp session overloads
	void on_bind() override final {
		BOOST_CHECK_MESSAGE( true, " override on_bind method for smpp_client_session called " );
	}

	void on_unbind() override final {
		BOOST_CHECK_MESSAGE( true, " override on_unbind method for smpp_client_session called " );
	}


	void on_read(buffer_type buffer, size_t size) override final {

	}

	void on_write(buffer_type buffer, size_t size) override final {

	}

};

BOOST_AUTO_TEST_CASE(session_initiation) {

	BOOST_TEST_CHECKPOINT("Starting");


	configuration config;
	config.type = Type::BOUND_TRX;
	config.ip = "127.0.0.1";
	config.port = 2775;
	config.system_id = "smppclient1";
	config.password = "password";
	config.system_type = "";
	config.type = Type::BOUND_TRX;

	smpp_client_session smpp_session(config);

	BOOST_CHECK_MESSAGE( smpp_session.connect() , "Couldn't connect to outbind connection!!" );



	getchar();

	smpp_session.disconnect();

	BOOST_CHECK( true );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




