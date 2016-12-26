/*
 * outbind.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_OUTBIND_H_
#define SMPP_PDU_OUTBIND_H_

#include "pdu.h"

#pragma pack(push, 1)

namespace smpp {
	namespace pdu {

	
		class outbind: public pdu {
		private:
			char system_id[16];
			char password[9];

			size_t size() {
				return pdu::size()
				+ std::min(strlen(system_id)+1, sizeof(system_id))
				+ std::min(strlen(password)+1, sizeof(password));
			}

		public:
			outbind() = default;

			outbind(const std::string &system_id, const std::string &password):
				pdu(OUTBIND) {
				coctet_cpy(this->system_id, system_id.c_str(), std::min(system_id.length()+1, sizeof(this->system_id)));
				coctet_cpy(this->password, system_id.c_str(), std::min(password.length()+1, sizeof(this->password)));
			}

			/*
			 * @brief converts pdu to buffer caller must delete memory after use
			 *
			 * @return pointer to uint8_t type or nullptr if function fails.
			 */
			virtual buffer_type to_buffer() override {
				auto buffer = pdu::to_buffer();
				if ( buffer_null == buffer ) {
					//TODO: error handling
					return buffer_null;
				}

				auto copy_offset = pdu::size();

				//copy this structure to buffer
//				::memcpy(buffer+copy_offset, this+copy_offset, size());
				return buffer;
			}


			/*
			 * @brief populate values of bind_pdu from the buffer given in parameter
			 *
			 * @param buffer to be copy from.
			 */
			virtual size_t from_buffer(buffer_type in) override {
				if ( buffer_null == in ) {
					return 0;
				}

				auto copy_offset = pdu::from_buffer(in);
				auto buffer = reinterpret_cast<char *>(in.first.get());
				copy_offset += coctet_cpy(system_id, buffer+copy_offset, sizeof(system_id));
				copy_offset += coctet_cpy(password, buffer+copy_offset, sizeof(password));

				return copy_offset;
			}

			char* get_systemid() {
				return system_id;
			}

			char* get_password() {
				return password;
			}

		};


	};
};

#pragma pack(pop)

#endif /* SMPP_PDU_OUTBIND_H_ */
