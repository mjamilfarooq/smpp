/*
 * server.cpp
 *
 *  Created on: Dec 25, 2016
 *      Author: jamil
 */

#include "server.h"

namespace utils {
namespace network {
namespace tcp {

server::server(const int32_t port, const uint32_t packet_size):
		port(port),
		socket_id(0),
		packet_size(packet_size) {
}

bool server::connect() {
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if ( -1 == socket_id ) return false;

	sockaddr_in server;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ( bind(socket_id, (sockaddr *)&server, sizeof(server)) < 0 ) return false;

	if ( -1 == listen(socket_id, 5) ) return false;

	FD_ZERO(&active_fd_set);	//filled with zeros
	FD_SET(socket_id, &active_fd_set);	//setting server socket on active fd set

	//execute multiplexer select function
//	std::async(std::launch::async, &server::select, this);

	new std::thread(&server::select, this);
	return true;

}

void server::select() {

	fd_set read_fd_set;

	while ( true ) {

		read_fd_set = active_fd_set;
		auto ret = ::select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
		if ( -1 == ret ) {
			return;
		}

		for (int i = 0; i < FD_SETSIZE; i++) {
			//if descriptor is not set for read, check the next descriptor
			if ( FD_ISSET(i, &read_fd_set) ) {

				//new connection request on original socket (server)
				if ( socket_id == i ) {
					accept();
					continue;
				}

				//data arriving on already connected socket
				read(i);
			}

		}
	}
}

void server::accept() {

	sockaddr_in client;
	::bzero(&client, sizeof(client));
	uint32_t size = sizeof(sockaddr_in);
	auto client_id = ::accept(socket_id, reinterpret_cast<struct sockaddr *>(&client), &size);
	if ( -1 == client_id ) {
		return;
	}
	FD_SET(client_id, &active_fd_set);	//adding client socket to list of active descriptor
	auto handler = create_client_handler(client_id, client);

	if ( nullptr == handler ) {
		::close(client_id);
		return;
	}

	client_handlers.emplace(client_id, handler);
	handler->on_connect();
}

void server::read(int client_id) {

	auto is_exist = client_handlers.find(client_id);
	if ( is_exist == client_handlers.end() ) {
		close(client_id, false);
		return;
	}

	auto& handler = is_exist->second;

	buffer_type buffer = create_buffer(packet_size);
	auto size = ::read(client_id, buffer.first.get(), packet_size);
	if ( -1 == size ) {
		//must throw network_exception here
		return;
	} else if ( 0 == size ) {
		close(client_id);
	}

	handler->read(buffer);


}

void server::close(int client_id, bool is_exist) {
	if ( is_exist ) {
		client_handlers[client_id]->on_disconnect();
		client_handlers.erase(client_id);
	}
	::close(client_id);
	FD_CLR(client_id, &active_fd_set);
}

void server::close() {
	client_handlers.clear();
	::close(socket_id);
	FD_CLR(socket_id, &active_fd_set);
}

server::~server() {
	close();
}

client_handler::client_handler(int32_t client_id, sockaddr_in addr):
		socket_id(client_id),
		addr(addr) {
}

size_t client_handler::write(buffer_type buffer) {
	return ::write(socket_id, buffer.first.get(), buffer.second);
}

client_handler::~client_handler() {
	::close(socket_id);
}

} /* namespace tcp */
} /* namespace network */
} /* namespace utils */
