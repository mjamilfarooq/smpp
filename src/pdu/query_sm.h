/*
 * query_sm.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_QUERY_SM_H_
#define PDU_QUERY_SM_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

		struct query_sm: public pdu {
			char message_id[65];
			address<21> source_addr;

			query_sm():
				pdu(QUERY_SM) {

			}

			virtual ~query_sm() {

			}
		};


		struct query_sm_resp: public pdu {
			char message_id[65];
			char final_date[17];

			uint8_t message_state;
			uint8_t error_code;
	
			query_sm_resp():
				pdu(QUERY_SM_RESP) {

			}

			virtual ~query_sm_resp() {

			}
		};



	};

};
#endif /* PDU_QUERY_SM_H_ */
