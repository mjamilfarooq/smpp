/*
 * connection.h
 *
 *  Created on: Jan 29, 2017
 *      Author: jamil
 */

#ifndef UTILS_NETWORK_CONNECTION_H_
#define UTILS_NETWORK_CONNECTION_H_

#include "packet.h"

namespace utils {
	namespace network {
		class connection {
		public:
			using pointer = connection *;

			virtual bool connect() = 0;
			virtual void disconnect() = 0;
			virtual ~connection() = 0;

			virtual bool write(buffer_type) = 0;
			virtual buffer_type read() = 0;

		protected:
			virtual void on_connect() = 0;
			virtual void on_disconnect() = 0;
			virtual void on_read(buffer_type, size_t) = 0;
			virtual void on_write(buffer_type, size_t) = 0;
		};

		inline connection::~connection() {
		}
	}
}



#endif /* UTILS_NETWORK_CONNECTION_H_ */
