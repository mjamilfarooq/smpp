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

#define THROW_NOMEMORY_EXCEPTION throw std::logic_error("No memory allocated for buffer")
#define THROW_LENGTH_EXCEED_EXCEPTION throw std::logic_error("operation will involve out of range allocated memory")
		/*
		 * copy C-Octet String with maximum limit of string
		 */
		inline size_t coctet_cpy(uint8_t *dest, const uint8_t *src, uint32_t num) {

			if ( nullptr == src || nullptr == dest ) return 0;

			int i = 0;
			for (; i < num ; i++ ) {
				dest[i] = src[i];
				if ( dest[i] == '\0' ) {
					return i+1;
				}
			}
			dest[num-1] = '\0';
			return i;
		}

		class buffer_type3;


		using buffer_type = buffer_type3;


		template <size_t n>
		class coctet {
			uint8_t _data[n];
		public:

			coctet() = default;

			coctet(std::string str) {
				coctet_cpy(_data, reinterpret_cast<const uint8_t *>(str.c_str()), n);
			}

			coctet& operator += (const buffer_type&);

			const size_t length() const { return std::min(strlen(reinterpret_cast<const char *>(_data))+1, n);}

			const size_t size() const { return n; }

			char* get () { return reinterpret_cast<char *>(_data); }
		};

		class buffer_type3 {

			template <size_t n>
			friend class coctet;

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
				buffer(new uint8_t[size+1]),	//total data plus end of array
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

			size_t length() { return size; }

			bool operator==(const std::nullptr_t arg) const noexcept { return buffer == nullptr; }
			bool operator!=(const std::nullptr_t arg) const noexcept { return buffer != nullptr; }

			friend bool operator == (const std::nullptr_t, const buffer_type3 &) noexcept;
			friend bool operator != (const std::nullptr_t, const buffer_type3 &) noexcept;

			template<typename T>
			const buffer_type3& operator += (const T para) const {
				if ( nullptr == buffer ) THROW_NOMEMORY_EXCEPTION;
				auto len = sizeof(para);
				static_assert( sizeof(T) <= 4 , "native type parameter with length greater than 4 not supported! ");
				T temp;
				if ( size - pos < len ) THROW_LENGTH_EXCEED_EXCEPTION;

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

				return *this;
			}

			template <size_t n>
			const buffer_type3& operator += (coctet<n>& octet) const {
				if ( nullptr == buffer ) THROW_NOMEMORY_EXCEPTION;
				if ( pos + octet.length() > size ) THROW_LENGTH_EXCEED_EXCEPTION;
				::memcpy(buffer.get()+pos, octet.get(), octet.length());
				pos += octet.length();
				return *this;
			}

			const buffer_type3& operator += (const char* type) const {
				if ( nullptr == buffer ) THROW_NOMEMORY_EXCEPTION;
				if ( type == nullptr ) return *this;
				auto len = strlen(type);
				if ( size - pos < len ) THROW_LENGTH_EXCEED_EXCEPTION;

				::memcpy(buffer.get()+pos, type, strlen(type));
				pos += len;

				return *this;
			}


			uint8_t& operator[](uint32_t index) {
				if ( nullptr == buffer ) THROW_NOMEMORY_EXCEPTION;
				return *(buffer.get()+index);
			}

			decltype(buffer)::pointer operator & () noexcept { return buffer.get(); }
			decltype(buffer)::pointer get() const noexcept { return buffer.get(); }

			void reset() noexcept { pos = 0; }

			template <typename T>
			friend T& operator += (T&, const buffer_type3&);

		};

		template <typename T>
		T& operator += (T& val, const buffer_type3& buffer) {

			if ( nullptr == buffer ) THROW_NOMEMORY_EXCEPTION;
			static_assert( sizeof(T) <= 4 , "sizeof datatype must be less or equal to 4");
			auto len = sizeof(val);
			T temp;
			if ( buffer.pos + len > buffer.size ) THROW_LENGTH_EXCEED_EXCEPTION;
			::memcpy(&temp, buffer.buffer.get() + buffer.pos, len);
			switch ( len ) {
			case 1:
				val = temp;
				break;
			case 2:
				val = ntohs(temp);
				break;
			case 4:
				val = ntohl(temp);
				break;
			}
			buffer.pos += len;
			return val;
		}

		template <size_t n>
		coctet<n>& coctet<n>::operator += (const buffer_type& buffer) {
			if ( nullptr == buffer ) THROW_NOMEMORY_EXCEPTION;
			auto max_available_space = buffer.size - buffer.pos;
			coctet_cpy(_data, buffer.get() + buffer.pos, std::min<uint32_t>(n, buffer.size - buffer.pos ));
			buffer.pos += length();
			return *this;
		}

		inline bool operator == (const std::nullptr_t arg, const buffer_type3 &buff) noexcept { return buff == nullptr; }
		inline bool operator != (const std::nullptr_t arg, const buffer_type3 &buff) noexcept { return buff != nullptr; }

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




		class packet {
		public:


			virtual  buffer_type to_buffer() = 0;
			virtual buffer_type from_buffer(buffer_type) = 0;

			virtual ~packet() {}
		};
	};
};


#endif /* UTILS_NETWORK_PACKET_H_ */
