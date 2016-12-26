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


using namespace utils::network;
using namespace utils::network::tcp;
using namespace std;

class telnetclient: public client_handler {
public:
	telnetclient(int32_t id, sockaddr_in addr):
		client_handler(id, addr) {
		cout<<"creating telnet client instance!!"<<endl;
	}

	virtual void on_connect() {
		cout<<"telnet connection request!! "<<endl;
		write("hello world!!");
	}

	virtual void on_disconnect() {
		cout<<"telnet disconnected!! "<<endl;
	}

	virtual void read(buffer_type buffer) {
		if ( buffer_null == buffer ) return;
		auto c_str = reinterpret_cast<char *>(buffer.first.get());
		cout<<c_str<<endl;
	}

	virtual size_t write(std::string out) {
		auto buffer = create_buffer(out.length()+1);
		if ( buffer_null == buffer ) return 0;
		auto size = coctet_cpy(reinterpret_cast<char *>(buffer.first.get()), out.c_str(), buffer.second);
		return client_handler::write(buffer);
	};

	virtual ~telnetclient(){}
};

class telnet_connection:public server {
public:
	telnet_connection(const uint32_t port):
		server(port) {
	}

	std::shared_ptr<client_handler> create_client_handler(int client_id, sockaddr_in addr) {
		return std::make_shared<telnetclient>(client_id, addr);
	}
};

BOOST_AUTO_TEST_SUITE(tcp_server_tests)

BOOST_AUTO_TEST_CASE(tcp_server_telnet) {

	BOOST_TEST_CHECKPOINT("Starting");

	telnet_connection telnet_server(49000);

	BOOST_CHECK_MESSAGE( telnet_server.connect() , "Couldn't connect to outbind connection!!" );



	getchar();

	BOOST_CHECK( true );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




