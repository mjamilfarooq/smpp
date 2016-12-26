/*
 * client.h
 *
 *  Created on: Dec 23, 2016
 *      Author: jamil
 */

#ifndef UTILS_NETWORK_TCP_CLIENT_H_
#define UTILS_NETWORK_TCP_CLIENT_H_


#include <string.h>

#include <string>
#include <memory>

#include "../packet.h"

namespace utils {
namespace network {
namespace tcp {



class client {
	std::string ip;
	uint16_t port;
	int socket_id;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	const uint32_t buffer_size;

public:
	client(std::string, uint16_t, uint32_t = 1024);
	bool connect();
	buffer_type read();
	bool write(buffer_type);
	void run();
	~client();
};


} /* namespace tcp */
} /* namespace utils */
}
#endif /* UTILS_NETWORK_TCP_CLIENT_H_ */
