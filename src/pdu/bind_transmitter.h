/*
 * bind_transmitter.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_BIND_TRANSMITTER_H_
#define PDU_BIND_TRANSMITTER_H_

#include "pdu.h"

namespace smpp {



	namespace pdu {

		//session management operations

#pragma pack(push, 1)
		/*
		 *
		 */
		struct bind_transmitter: public pdu {
		private:
			char system_id[16];
			char password[9] ;
			char system_type[13];
			uint8_t interface_version;
			uint8_t addr_ton;
			uint8_t addr_npi;
			char address_range[41];

			virtual size_t size() {
				return 	sizeof(system_id) +
						sizeof(password) +
						sizeof(system_type) +
						sizeof(interface_version) +
						sizeof(addr_ton) +
						sizeof(addr_npi) +
						sizeof(address_range);
			}

		public:
			bind_transmitter(
					const std::string &system_id,
					const std::string &password,
					const std::string &system_type = "",
					const uint8_t interface_version = smpp::SMPP_VERSION_0x33,
					const uint8_t addr_ton = smpp::address::TON_UNKNOWN,
					const uint8_t addr_npi = smpp::address::NPI_UNKNOWN,
					const std::string &address_range = ""):
						pdu(BIND_TRANSMITTER),
						interface_version(interface_version),
						addr_ton(addr_ton),
						addr_npi(addr_npi) {
				::memcpy(this->system_id, system_id.c_str(), std::min(system_id.size(), sizeof(this->system_id)));
				::memcpy(this->password, password.c_str(), std::min(password.size(), sizeof(this->password)));
				::memcpy(this->system_type, system_type.c_str(), std::min(system_type.size(), sizeof(this->system_type)));
				::memcpy(this->address_range, address_range.c_str(), std::min(address_range.size(), sizeof(this->address_range)));

			}

			/*
			 * @brief converts pdu to buffer caller must delete memory after use
			 *
			 * @return pointer to uint8_t type or nullptr if function fails.
			 */
			uint8_t * to_buffer() {

				auto buffer = pdu::to_buffer();
				if ( nullptr == buffer ) {
					//TODO: error handling
					return nullptr;
				}

				auto copy_offset = pdu::size();
				//copy this structure to buffer
				::memcpy(buffer+copy_offset, this+copy_offset, size());
				return buffer;
			}

			/*
			 * @brief populate values of bind_transmitter from the buffer given in parameter
			 *
			 * @param buffer to be copy from.
			 */
			size_t from_buffer(const uint8_t * buffer) {
				if ( nullptr == buffer ) return 0;
				auto copy_offset = pdu::from_buffer(buffer);
				::memcpy(this+copy_offset, buffer+copy_offset, command_length - copy_offset);
				return command_length;
			}


		};

		struct bind_transmitter_resp: public pdu {
		private:
			char system_id[16];
			sc_interface_version *version;	//< optional interface version TLV

			size_t size() {
				return sizeof(system_id) +
						((nullptr == version) ? 0 : version->size());
			}

		public:
			bind_transmitter_resp(const std::string &system_id):
				pdu(BIND_TRANSMITTER_RESP),
				version(nullptr) {
				::memcpy(this->system_id, system_id.c_str(), std::min(system_id.size(), sizeof(this->system_id)));
			}

			bind_transmitter_resp(const std::string &system_id, const uint8_t version):
				pdu(BIND_TRANSMITTER_RESP),
				version(new sc_interface_version(version)) {
				::memcpy(this->system_id, system_id.c_str(), std::min(system_id.size(), sizeof(this->system_id)));
			}


			/*
			 * @brief converts pdu to buffer caller must delete memory after use
			 *
			 * @return pointer to uint8_t type or nullptr if function fails.
			 */
			uint8_t * to_buffer() {

				auto buffer = pdu::to_buffer();
				if ( nullptr == buffer ) return nullptr;

				auto copy_offset = pdu::size();
				//copy this structure to buffer
				::memcpy(buffer+copy_offset, system_id, sizeof(system_id)); copy_offset += sizeof(system_id);
				if ( nullptr != version ) version->to_buffer(buffer+copy_offset);
				return buffer;
			}

			/*
			 * @brief populate values of bind_transmitter from the buffer given in parameter
			 *
			 * @param buffer to be copy from.
			 *
			 * @number of bytes successfully copied from buffer
			 */
			size_t from_buffer(const uint8_t * buffer) {
				if ( nullptr == buffer ) return 0;
				auto copy_offset = pdu::from_buffer(buffer);
				::memcpy(this+copy_offset, buffer+copy_offset, sizeof(system_id)); copy_offset += sizeof(system_id);
				if ( command_length - copy_offset != sizeof(sc_interface_version(0)) ) { // no sc_interface_version
					return copy_offset;
				}

				version = new sc_interface_version(0);
				copy_offset += version->from_buffer(buffer+copy_offset);
				return copy_offset;
			}


			~bind_transmitter_resp() {
				delete version;
			}
		};

#pragma pack(pop)

	};

};



#endif /* PDU_BIND_TRANSMITTER_H_ */
