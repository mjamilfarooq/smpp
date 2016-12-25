/*
 * packet.h
 *
 *  Created on: Dec 24, 2016
 *      Author: jamil
 */

#ifndef UTILS_NETWORK_PACKET_H_
#define UTILS_NETWORK_PACKET_H_

#include <iomanip>
#include <arpa/inet.h>
#include <memory>

namespace utils {
	namespace network {

		using buffer_type = std::pair<std::shared_ptr<uint8_t>, size_t>;
		const auto buffer_null = buffer_type{nullptr, 0};

		inline buffer_type create_buffer(const uint32_t size) {
			return {std::shared_ptr<uint8_t>(new uint8_t[size], std::default_delete<uint8_t []>()), 0};
		}

		/*
		 * copy C-Octet String with maximum limit of string
		 */
		inline size_t coctet_cpy(char *dest, const char *src, uint32_t num) {

			if ( nullptr == src || nullptr == dest ) return 0;

			int i = 0;
			for (; i < num; i++ ) {
				dest[i] = src[i];
				if ( dest[i] == '\0' ) {
					return i+1;
				}
			}
			dest[num-1] = '\0';
			return i;
		}

		class packet {
		public:


			virtual  buffer_type to_buffer() = 0;
			virtual size_t from_buffer(buffer_type) = 0;

			virtual ~packet() {}
		};
	};
};


#endif /* UTILS_NETWORK_PACKET_H_ */
