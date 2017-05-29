/*
 * tcp_server_tests.cpp
 *
 *  Created on: Dec 26, 2016
 *      Author: jamil
 */




#define BOOST_TEST_MODULE first test
#include <boost/test/auto_unit_test.hpp>
#include <iostream>

#include "../utils/network/tcp/server.h"
#include "../smpp/pdu/outbind.h"


using namespace smpp::pdu;
using namespace utils::network;
using namespace utils::network::tcp;
using namespace std;

class outbind_smpp_client: public client_handler {
public:
	outbind_smpp_client(int32_t id, sockaddr_in addr):
		client_handler(id, addr) {
		cout<<"creating smpp outbind instance!!"<<endl;
	}

	virtual void on_connect() {
		cout<<"smpp outbind connection request!! "<<endl;

	}

	virtual void on_disconnect() {
		cout<<"smpp outbind disconnected!! "<<endl;
	}

	virtual void read(buffer_type buffer) override {
		outbind ob;
		buffer = ob.from_buffer(std::move(buffer));

		cout<<"outbind information (system_id, password): "<<ob.get_systemid()<<", "<<ob.get_password();
	}

	size_t write(std::string out) {
		auto len = out.length()+1;
		auto buffer = buffer_type(len);
		buffer += out.c_str();
		return client_handler::write(std::move(buffer));
	};

	virtual ~outbind_smpp_client(){}
};

class outbind_connection:public server {
public:
	outbind_connection(const uint32_t port):
		server(port) {
	}

	std::shared_ptr<client_handler> create_client_handler(int client_id, sockaddr_in addr) {
		return std::make_shared<outbind_smpp_client>(client_id, addr);
	}
protected:

	void on_connect() override {
		BOOST_TEST_MESSAGE( "In on_connnect for outbind_connection " );
	}

	void on_disconnect() override {
		BOOST_TEST_MESSAGE( "In on_disconnnect for outbind_connection " );
	}
};

BOOST_AUTO_TEST_SUITE(smpp_outbind_tests)

BOOST_AUTO_TEST_CASE(smpp_outbind_telnet) {

	BOOST_TEST_CHECKPOINT("Starting");

	outbind_connection outbind_smpp_connection(2776);

	BOOST_CHECK_MESSAGE( outbind_smpp_connection.connect() , "Couldn't connect to outbind connection!!" );



	getchar();

	BOOST_CHECK( true );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




