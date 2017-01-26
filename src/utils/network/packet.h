/*
 * packet.h
 *
 *  Created on: Dec 24, 2016
 *      Author: jamil
 */

#ifndef UTILS_NETWORK_PACKET_H_
#define UTILS_NETWORK_PACKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iomanip>
#include <arpa/inet.h>
#include <memory>
#include <iostream>
#include <cstddef>

namespace utils {
	namespace network {

		class buffer_type3 {
			std::unique_ptr<uint8_t, std::default_delete<uint8_t []>> buffer;
			uint32_t size;
			mutable uint32_t pos;
		public:
			buffer_type3():
				size(0),
				buffer(nullptr),
				pos(0) {
			}

			buffer_type3(uint32_t size):
				size(size),
				buffer(new uint8_t[size]),
				pos(0) {
			}

			buffer_type3(const buffer_type3 &) = delete;

			buffer_type3(buffer_type3 &&another):
				size(another.size),
				buffer(std::move(another.buffer)),
				pos(another.pos) {
				another.size = 0;
				another.buffer = nullptr;
			}

			buffer_type3& operator = (const buffer_type3 &) = delete;

			buffer_type3& operator = (buffer_type3 && another) {
				size = another.size; another.size = 0;
				buffer = std::move(another.buffer);	another.buffer = nullptr;
				pos = another.pos; another.pos = 0;
				return *this;
			}

			bool operator==(std::nullptr_t arg) const { return buffer == nullptr; }
			bool operator!=(std::nullptr_t arg) const { return buffer != nullptr; }

			template<typename T>
			const buffer_type3& operator += (const T para) const {
				auto len = sizeof(para);
				static_assert( sizeof(T) <= 4 , "native type parameter with length greater than 4 not supported! ");
				T temp;
				if ( *this != nullptr && size - pos - 1 > len ) {
					switch ( len ) {
					case 1:
						temp = para;
						break;
					case 2:
						temp = htons(para);
						break;
					case 4:
						temp = htonl(para);
						break;
					}
					::memcpy(buffer.get()+pos, &temp, len);
					pos += sizeof(T);
				}
				return *this;
			}

			const buffer_type3& operator += (const char* const type) const {
				if ( type == nullptr ) return *this;
				auto len = strlen(type);
				if ( *this != nullptr &&
						size - pos -1 > len ) {
					::memcpy(buffer.get()+pos, type, strlen(type));
					pos += len;
				}
				return *this;
			}

			uint8_t& operator[](uint32_t index) {
				return *(buffer.get()+index);
			}

		};

		class buffer_type2 {
			uint32_t size;
			uint8_t* buffer;
		public:

			buffer_type2():
				size(0),
				buffer(nullptr) {
			}

			explicit buffer_type2(uint32_t size):
				size(size),
				buffer(nullptr) {
				this->buffer = new uint8_t[this->size];
			}

			buffer_type2(const buffer_type2 &) = delete;	//deleting copy constructor

			buffer_type2(buffer_type2&& other):				//move constructor
				size(other.size),
				buffer(other.buffer) {
				other.size = 0;
				other.buffer = nullptr;
			}

			buffer_type2& operator=(const buffer_type2 &) = delete; //deleting copy assignment as well

			buffer_type2& operator=(buffer_type2&& other) {
				if ( buffer ) {
					delete [] buffer;
					size = 0;
				}
				size = other.size; other.size = 0;
				buffer = other.buffer; other.buffer = nullptr;
				return *this;
			}

			bool operator==(std::nullptr_t arg) { return buffer == nullptr;}
			bool operator!=(std::nullptr_t arg) { return buffer != nullptr;}


			~buffer_type2() {
				if ( buffer ) delete [] buffer;
			}

		};



		using buffer_type = std::pair<std::shared_ptr<uint8_t>, size_t>;
		const auto buffer_null = buffer_type{nullptr, 0};

		inline buffer_type create_buffer(const size_t size) {
			return buffer_type (std::shared_ptr<uint8_t>(new uint8_t[size], std::default_delete<uint8_t []>()), size);
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
