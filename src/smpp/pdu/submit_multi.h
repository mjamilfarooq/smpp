/*
 * submit_multi.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_SUBMIT_MULTI_H_
#define SMPP_PDU_SUBMIT_MULTI_H_

#include "../smpp/pdu/pdu.h"

namespace smpp {
	namespace pdu {

		struct submit_multi: public pdu {

			char service_type[6];
			address<21> source_addr;
			uint8_t number_of_dests;


			struct {
				uint8_t flag;
				address<21> addr;	//if flag is 0x01 SME Address this field will be valid
				char dl_name[21];	//if flag is 0x02 pre decided distribution list at SMC will be used
			} destination_addr;

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

			//Message Submission TLV

			submit_multi():
				pdu(SUBMIT_MULTI) {
			}

			virtual ~submit_multi() {

			}
		};


		struct submit_multi_resp: public pdu {
	
			char message_id[65];
			uint8_t no_unsuccess;	//number of unsuccessful messages

			struct unsuccess_sme {
				address<21> destination_addr;
				uint32_t error_code;
			};

			unsuccess_sme *unsuccess_destination;

			//Message Submission TLVs

			submit_multi_resp():
				pdu(SUBMIT_MULTI_RESP),
				unsuccess_destination(nullptr) {
			}

			virtual ~submit_multi_resp() {

			}
		};




	};

};
#endif /* SMPP_PDU_SUBMIT_MULTI_H_ */
