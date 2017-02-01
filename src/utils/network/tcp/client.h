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
#include "../connection.h"

namespace utils {
namespace network {
namespace tcp {

class client: public utils::network::connection {
	std::string ip;
	uint16_t port;
	int socket_id;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	const uint32_t buffer_size;

public:
	client(std::string, uint16_t, uint32_t = 1024);
	bool connect() override final;
	virtual void disconnect();
	buffer_type read() override;
	bool write(buffer_type) override;
	virtual void run() = 0;
	virtual ~client();

protected:
	virtual void on_connect() = 0;
	virtual void on_disconnect() = 0;

	virtual buffer_type on_read(buffer_type, size_t) = 0;
	virtual void on_write(buffer_type, size_t) = 0;
};


} /* namespace tcp */
} /* namespace utils */
}
#endif /* UTILS_NETWORK_TCP_CLIENT_H_ */
