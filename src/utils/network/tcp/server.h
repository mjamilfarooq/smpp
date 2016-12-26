/*
 * server.h
 *
 *  Created on: Dec 25, 2016
 *      Author: jamil
 */

#ifndef UTILS_NETWORK_TCP_SERVER_H_
#define UTILS_NETWORK_TCP_SERVER_H_

#include <future>
#include <thread>
#include <map>
#include <algorithm>
#include <strings.h>

#include "../packet.h"

namespace utils {
namespace network {
namespace tcp {

class client_handler {
	int32_t socket_id;
	sockaddr_in addr;
public:
	client_handler(int32_t, sockaddr_in);
	virtual void on_connect() = 0;
	virtual void on_disconnect() = 0;
	virtual void read(buffer_type) = 0;
	virtual size_t write(buffer_type);

	virtual ~client_handler();

};

class server {
	uint32_t port;
	int socket_id;
	const uint32_t packet_size;

	fd_set active_fd_set;	//active descriptors on socket


	std::map<int32_t, std::shared_ptr<client_handler>> client_handlers;

	void select();	//poll for event at file descriptors
	void accept();	//instantiate new client connection
	void close(int, bool = true);	//close instance of client connection also if true delete client_handler
	void close(); 	//close server connection
	void read(int);	//read from client file descriptor and call read handler from client_handler
public:
	server(const int32_t, const uint32_t = 1024);
	bool connect();
	virtual std::shared_ptr<client_handler> create_client_handler(const int, sockaddr_in) = 0;
	virtual ~server();

	uint32_t get_packet_size();
};

inline uint32_t server::get_packet_size() {
		return packet_size;
}



} /* namespace tcp */
} /* namespace network */
} /* namespace utils */

#endif /* UTILS_NETWORK_TCP_SERVER_H_ */
