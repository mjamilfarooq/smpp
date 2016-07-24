/*
 * data_sm.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_DATA_SM_H_
#define PDU_DATA_SM_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

		struct data_sm: public pdu {
			char service_type[6];
	
			address<65> source_addr;
			address<65> destination_addr;

			uint8_t esm_struct;
			uint8_t registerd_delivery;
			uint8_t data_coding;

			//Message Submission TLVs

			data_sm():
				pdu(DATA_SM) {

			}

			virtual ~data_sm() {

			}
		};

		struct data_sm_resp: public pdu {
			char message_id[65];
			//Message submission Response TLVs
			data_sm_resp():
				pdu(DATA_SM_RESP) {

			}

			virtual ~data_sm_resp() {

			}
		};



	};

};
#endif /* PDU_DATA_SM_H_ */
