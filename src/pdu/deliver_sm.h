/*
 * deliver_sm.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_DELIVER_SM_H_
#define PDU_DELIVER_SM_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

		struct deliver_sm: public pdu {
			char service_type[6];
			address<21> source_addr;
			address<21> destination_addr;

			uint8_t esm_struct;
			uint8_t protocol_id;
			uint8_t priority_flag;

			char schedule_delivery_time[17];
			char validity_period[17];
	
			uint8_t registered_delivery;
			uint8_t replace_if_present_flag;
			uint8_t data_coding;
			uint8_t sm_default_msg_id;
			uint8_t sm_length;
			char short_message[255];

			//TLV

			deliver_sm():
				pdu(DELIVER_SM) {
			}

			virtual ~deliver_sm() {

			}

		};


		struct deliver_sm_resp: public pdu {
			char message_id[65];
			//TLV
			deliver_sm_resp():
				pdu(DELIVER_SM_RESP) {

			}

			virtual ~deliver_sm_resp() {

			}
		};



	};

};
#endif /* PDU_DELIVER_SM_H_ */
