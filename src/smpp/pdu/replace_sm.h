/*
 * replace_sm.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_REPLACE_SM_H_
#define SMPP_PDU_REPLACE_SM_H_

#include "../smpp/pdu/pdu.h"

namespace smpp {
	namespace pdu {

	


		struct replace_sm: public pdu {
			char message_id[65];
			address<21> source_addr;

			char schedule_delivery_time[17];
			char validity_period[17];

			uint8_t registered_delivery;
			uint8_t sm_default_msg_id;

			uint8_t sm_length;
			char short_message[255];

			//message replace request TLVs

			replace_sm():
				pdu(REPLACE_SM) {

			}

			virtual ~replace_sm() {

			}
		};


		struct replace_sm_resp: public pdu {
			replace_sm_resp():
				pdu(REPLACE_SM_RESP) {

			}

			virtual ~replace_sm_resp() {

			}
		};



	};

};
#endif /* SMPP_PDU_REPLACE_SM_H_ */
