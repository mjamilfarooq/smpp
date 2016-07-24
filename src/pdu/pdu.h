/*
 * PDU.h
 *
 *  Created on: Jul 22, 2016
 *      Author: jamil
 */

#ifndef PDU_H_
#define PDU_H_

#include <stdint.h>
#include <cstring>
#include <algorithm>
#include <string>
#include <ctime>
#include <iomanip>

#include <arpa/inet.h>

#include "tlv.h"

namespace smpp {




	/*
	 * @brief address structure define general source/destination address format used by smpp
	 */
	template <size_t n = 1>
	struct address {
		//SMPP ADDRESS TYPE OF NUMBER
		const static uint8_t TON_UNKNOWN 			= 0b00000000;
		const static uint8_t TON_INTERNATIONAL 		= 0b00000001;
		const static uint8_t TON_NATIONAL 			= 0b00000010;
		const static uint8_t TON_NETWORK_SPECIFIC 	= 0b00000011;
		const static uint8_t TON_SUBSCRIBER_NUMBER 	= 0b00000100;
		const static uint8_t TON_ALPHANUMERIC 		= 0b00000101;
		const static uint8_t TON_ABBREVIATED 		= 0b00000110;

		//SMPP ADDRESS Numeric Plan Indicator
		const static uint8_t NPI_UNKNOWN 		= 0b00000000;
		const static uint8_t NPI_ISDN 			= 0b00000001;
		const static uint8_t NPI_DATA 			= 0b00000011;
		const static uint8_t NPI_TELEX 			= 0b00000100;
		const static uint8_t NPI_LAND_MOBILE 	= 0b00000110;
		const static uint8_t NPI_NATIONAL 		= 0b00001000;
		const static uint8_t NPI_PRIVATE 		= 0b00001001;
		const static uint8_t NPI_ERMES 			= 0b00001010;
		const static uint8_t NPI_INTERNET  		= 0b00001110;
		const static uint8_t NPI_WAP_CLIENT_ID 	= 0b00010010;

		uint8_t ton;
		uint8_t npi;
		char addr[n];
	};

	namespace pdu {

		//command_id definitions PDU type
		const static uint32_t GENERIC_NACK          = 0X80000000;
		const static uint32_t BIND_RECEIVER         = 0X00000001;
		const static uint32_t BIND_RECEIVER_RESP    = 0X80000001;
		const static uint32_t BIND_TRANSMITTER      = 0X00000002;
		const static uint32_t BIND_TRANSMITTER_RESP = 0X80000002;
		const static uint32_t BIND_TRANSCEIVER      = 0X00000009;
		const static uint32_t BIND_TRANSCEIVER_RESP = 0X80000009;
		const static uint32_t QUERY_SM              = 0X00000003;
		const static uint32_t QUERY_SM_RESP         = 0X80000003;
		const static uint32_t SUBMIT_SM             = 0X00000004;
		const static uint32_t SUBMIT_SM_RESP        = 0X80000004;
		const static uint32_t DATA_SM             	= 0X00000103;
		const static uint32_t DATA_SM_RESP        	= 0X80000103;
		const static uint32_t DELIVER_SM            = 0X00000005;
		const static uint32_t DELIVER_SM_RESP       = 0X80000005;
		const static uint32_t BROADCAST_SM          = 0X00000111;
		const static uint32_t BROADCAST_SM_RESP     = 0X80000111;
		const static uint32_t OUTBIND				= 0x0000000B;
		const static uint32_t UNBIND                = 0X00000006;
		const static uint32_t UNBIND_RESP           = 0X80000006;
		const static uint32_t REPLACE_SM            = 0X00000007;
		const static uint32_t REPLACE_SM_RESP       = 0X80000007;
		const static uint32_t CANCEL_SM             = 0X00000008;
		const static uint32_t CANCEL_SM_RESP        = 0X80000008;
		const static uint32_t ENQUIRE_LINK          = 0X00000015;
		const static uint32_t ENQUIRE_LINK_RESP     = 0X80000015;
		const static uint32_t SUBMIT_MULTI          = 0X00000021;
		const static uint32_t SUBMIT_MULTI_RESP     = 0X80000021;
		const static uint32_t ALERT_NOTIFICATION	= 0x00000102;


		struct pdu {

		protected:
			uint32_t command_length;
			uint32_t command_id;
			uint32_t command_status;
			uint32_t sequence_number;

			uint32_t copy_offset;	//< internal to functionality for buffer creation

			pdu(uint32_t command_id):
				command_length(sizeof(pdu)),
				command_id(command_id),
				command_status(0),
				sequence_number(0),
				copy_offset(0) {

			}

		public:
			virtual uint8_t * to_buffer() {
				auto ret = new uint8_t(command_length);
				if ( nullptr == ret ) {
					//TODO: report this event on console and log
					return nullptr;
				}

				auto data = htonl(command_length);
				auto length = sizeof(command_length);
				std::memcpy(ret + copy_offset, &data, length); copy_offset += length;

				data = htonl(command_id);
				length = sizeof(command_id);
				std::memcpy(ret + copy_offset, &data, length); copy_offset += length;

				data = htonl(command_status);
				length = sizeof(command_status);
				std::memcpy(ret + copy_offset, &data, length); copy_offset += length;

				data = htonl(sequence_number);
				length = sizeof(sequence_number);
				std::memcpy(ret + copy_offset, &data, length); copy_offset += length;

				return ret;
			}

			virtual bool from_buffer(uint8_t *buffer) {
				if ( nullptr == buffer ) {
					//TODO: report this event on console and log
					return false;
				}

				copy_offset = 0;

				std::memcpy(&command_length, buffer+copy_offset, sizeof(command_length));
				copy_offset += sizeof(command_length);
				command_length = ntohl(command_length);

				std::memcpy(&command_id, buffer+copy_offset, sizeof(command_id));
				copy_offset += sizeof(command_id);
				command_id = ntohl(command_id);

				std::memcpy(&command_status, buffer+copy_offset, sizeof(command_status));
				copy_offset += sizeof(command_status);
				command_length = ntohl(command_status);

				std::memcpy(&sequence_number, buffer+copy_offset, sizeof(sequence_number));
				copy_offset += sizeof(sequence_number);
				sequence_number = ntohl(sequence_number);

				return true;

			}

			virtual ~pdu() {

			}
		};



	};
};

#endif /* PDU_H_ */
