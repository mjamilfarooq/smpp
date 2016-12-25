/*
 * submit_sm.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_SUBMIT_SM_H_
#define SMPP_PDU_SUBMIT_SM_H_

#include "../smpp/pdu/pdu.h"

namespace smpp{

	namespace pdu {

		/*
		 * @brief submit_sm for sending short message
		 */
		struct submit_sm: public pdu {
			char service_type[6];

			smpp::address::address<21> source_addr;
			smpp::address::address<21> destination_addr;

			uint8_t esm_struct;
			uint8_t protocol_id;
			uint8_t priority_flag;

			char schedule_delivery_time [17];
			char validity_period [17];

			uint8_t registered_delivery;
			uint8_t replace_if_present_flag;
			uint8_t data_coding;
			uint8_t sm_default_msg_id;
			uint8_t sm_length;
			char short_message[225];

			//Message submission TLVs


			submit_sm():
				pdu(SUBMIT_SM) {
			}

			virtual ~submit_sm(){

			}
		};


		struct submit_sm_resp: public pdu {
			char message_id[65];
			//Message submission Response TLVs
			submit_sm_resp():
				pdu(SUBMIT_SM_RESP) {

			}

			virtual ~submit_sm_resp() {

			}
		};


	};

};



#endif /* SMPP_PDU_SUBMIT_SM_H_ */
