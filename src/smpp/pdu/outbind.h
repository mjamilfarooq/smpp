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
			coctet<16> system_id;
			coctet<9> password;

			size_t size() {
				return pdu::size()
				+ system_id.size()
				+ password.size();
			}

		public:
			outbind() = default;

			outbind(const std::string &system_id, const std::string &password, const uint32_t sequence_number):
				pdu(OUTBIND, sequence_number),
				system_id(system_id),
				password(password) {
			}

			/*
			 * @brief converts pdu to buffer caller must delete memory after use
			 *
			 * @return pointer to uint8_t type or nullptr if function fails.
			 */
			virtual buffer_type to_buffer() override {
				auto buffer = pdu::to_buffer();

				buffer += system_id;
				buffer += password;

				return buffer;
			}


			/*
			 * @brief populate values of bind_pdu from the buffer given in parameter
			 *
			 * @param buffer to be copy from.
			 */
			virtual buffer_type from_buffer(buffer_type in) override {

				auto buffer = pdu::from_buffer(std::move(in));

				system_id += buffer;
				password += buffer;

				return buffer;
			}

			char* get_systemid() {
				return system_id.get();
			}

			char* get_password() {
				return password.get();
			}

		};


	};
};

#pragma pack(pop)

#endif /* SMPP_PDU_OUTBIND_H_ */
