/*
 * enquire_link.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_ENQUIRE_LINK_H_
#define SMPP_PDU_ENQUIRE_LINK_H_

#include "../smpp/pdu/pdu.h"

#pragma pack(push, 1)

namespace smpp {
	namespace pdu {


		class enquire_link: public pdu {
		private:
			size_t size() {
				return 0;	//only pdu header size
			}

		public:
			enquire_link():
				pdu(ENQUIRE_LINK) {
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
				return buffer;
			}


			/*
			 * @brief populate values of enquire_link from the buffer given in parameter
			 *
			 * @param buffer to be copy from.
			 */
			size_t from_buffer(const uint8_t * buffer) {
				if ( nullptr == buffer ) return 0;
				auto copy_offset = pdu::from_buffer(buffer);
				return copy_offset;
			}

		};


		class enquire_link_resp: public pdu {
		private:
			size_t size() {
				return 0;	//only pdu header size
			}

		public:
			enquire_link_resp():
				pdu(ENQUIRE_LINK_RESP) {
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
				return buffer;
			}


			/*
			 * @brief populate values of enquire_link from the buffer given in parameter
			 *
			 * @param buffer to be copy from.
			 */
			size_t from_buffer(const uint8_t * buffer) {
				if ( nullptr == buffer ) return 0;
				auto copy_offset = pdu::from_buffer(buffer);
				return copy_offset;
			}

		};


	};
};

#pragma pack(pop)
#endif /* SMPP_PDU_ENQUIRE_LINK_H_ */
