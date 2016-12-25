/*
 * client.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: jamil
 */

#include "client.h"


namespace utils {
namespace network {
namespace tcp {

	client::client(std::string ip, uint16_t port, uint32_t buffer_size):
			ip(ip),
			port(port),
			socket_id(0),
			server(nullptr),
			buffer_size(buffer_size) {
		bzero(&serv_addr, sizeof(serv_addr));
	}

	bool client::connect() {
		if ( ( socket_id = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ) return false;
	//			BOOST_THROW_EXCEPTION(test_exception{}<<boost::errinfo_errno(errno));

		if ( (server = gethostbyname(ip.c_str())) == NULL ) return false;
	//			BOOST_THROW_EXCEPTION(test_exception{}<<boost::errinfo_errno(errno));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(port);
		bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);


		if ( ::connect(socket_id,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) return false;
	//			BOOST_THROW_EXCEPTION(test_exception{}<<boost::errinfo_errno(errno));

		return true;
	}

	buffer_type client::read() {
		auto buffer = create_buffer(buffer_size);
		auto size = ::read(socket_id, buffer.first.get(), buffer_size);

		if ( size > 0 ) {
			return buffer;
		}

		return buffer_null;
	}

	bool client::write(buffer_type buffer) {

		if ( -1 == ::write(socket_id, buffer.first.get(), buffer.second) ) return false;
		return true;
	}

	void client::run() {

	}

	client::~client() {
		close(socket_id);
	}

} /* namespace tcp */
} /* namespace utils */
}
