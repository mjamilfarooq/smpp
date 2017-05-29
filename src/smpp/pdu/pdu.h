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
#include <string.h>
#include <iostream>

#include "tlv.h"
#include "address.h"
#include "../../utils/utils.h"



using namespace utils::network;

namespace smpp {

	const static uint8_t SMPP_VERSION_0x33 = 0x33;
	const static uint8_t SMPP_VERSION_0x34 = 0x34;
	const static uint8_t SMPP_VERSION_0x50 = 0x50;

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


		const static uint32_t STATUS_SUCCESS		= 0x00000000;
		const static uint32_t STATUS_FAILURE		= !STATUS_SUCCESS;


		class pdu: public packet {
		protected:
			uint32_t command_length;
			uint32_t command_id;
			uint32_t command_status;
			uint32_t sequence_number;

			size_t size() ;

		public:

			using pointer = pdu *;
			pdu() = default;
			pdu(uint32_t, uint32_t);

			void set_length(uint32_t);
			void set_id(uint32_t);
			void set_status(uint32_t);
			void set_seqnum(uint32_t);

			bool operator == (const uint32_t command_id) const ;


			uint32_t get_length();
			uint32_t get_id();
			uint32_t get_status();
			uint32_t get_seqnum();

			virtual buffer_type to_buffer() override;
			virtual buffer_type from_buffer(buffer_type) override;
			virtual ~pdu();


			bool is_response();

		};


		inline bool pdu::operator == (const uint32_t command_id) const {
			return this->command_id == command_id;
		}

		inline void pdu::set_id(uint32_t id) {
			command_id = id;
		}

		inline void pdu::set_length(uint32_t length) {
			command_length = length;
		}

		inline void pdu::set_status(uint32_t status) {
			command_status = status;
		}

		inline void pdu::set_seqnum(uint32_t seqnum) {
			sequence_number = seqnum;
		}


		inline uint32_t pdu::get_id() {
			return command_id;
		}

		inline uint32_t pdu::get_length() {
			return command_length;
		}

		inline uint32_t pdu::get_status() {
			return command_status;
		}

		inline uint32_t pdu::get_seqnum() {
			return sequence_number;
		}

		inline bool pdu::is_response() {
			if ( command_id > 0X80000000 ) return true;
			return false;
		}

	}
}

#endif /* PDU_H_ */
