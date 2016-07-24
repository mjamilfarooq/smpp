/*
 * broadcast_sm.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_BROADCAST_SM_H_
#define PDU_BROADCAST_SM_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

	struct broadcast_sm: public pdu {
				char service_type[6];
				address<21> source_addr;
				char message_id[65];

				uint8_t priority_flag;
				char schedule_delivery_time[17];
				char validity_period[17];

				uint8_t replace_if_present_flag;
				uint8_t data_coding;
				uint8_t sm_default_msg_id;

				//TLV broadcast_area_identifier;
				//TLV boradcast_content_type;
				//TLV broadcast_rep_num;
				//TLV broadcast_frequency_number;

				//Optional TLVs

				broadcast_sm():
					pdu(BROADCAST_SM) {

				}

				virtual ~broadcast_sm() {

				}
			};


			struct broadcast_sm_resp: public pdu {
				char message_id[65];

				//Optional TLVs

				broadcast_sm_resp():
					pdu(BROADCAST_SM_RESP) {

				}

				virtual ~broadcast_sm_resp() {

				}
			};



	};

};
#endif /* PDU_BROADCAST_SM_H_ */
