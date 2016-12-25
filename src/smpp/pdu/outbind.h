/*
 * outbind.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_OUTBIND_H_
#define SMPP_PDU_OUTBIND_H_

#include "../smpp/pdu/pdu.h"

#pragma pack(push, 1)

namespace smpp {
	namespace pdu {

	
		class outbind: public pdu {
		private:
			char system_id[16];
			char password[9];

			size_t size() {
				return sizeof(system_id) + sizeof(password);
			}

		public:
			outbind(const std::string &system_id, const std::string &password):
				pdu(OUTBIND) {
				::memcpy(this->system_id, system_id.c_str(), std::min(system_id.size(), sizeof(this->system_id)));
				::memcpy(this->password, password.c_str(), std::min(password.size(), sizeof(this->password)));
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
			 * @brief populate values of bind_pdu from the buffer given in parameter
			 *
			 * @param buffer to be copy from.
			 */
			size_t from_buffer(const uint8_t * buffer) {
				if ( nullptr == buffer ) return 0;
				auto copy_offset = pdu::from_buffer(buffer);
				::memcpy(this+copy_offset, buffer+copy_offset, size());
				return command_length;
			}

		};


	};
};

#pragma pack(pop)

#endif /* SMPP_PDU_OUTBIND_H_ */
