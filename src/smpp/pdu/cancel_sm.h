/*
 * cancel_sm.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_CANCEL_SM_H_
#define SMPP_PDU_CANCEL_SM_H_

#include "../smpp/pdu/pdu.h"

namespace smpp {
	namespace pdu {

		struct cancel_sm: public pdu {
			char service_type[6];
			char message_id[65];

			address<21> source_addr;
			address<21> destination_addr;

			cancel_sm():
				pdu(CANCEL_SM) {
	
			}

			virtual ~cancel_sm() {

			}
		};


		struct cancel_sm_resp: public pdu {
			cancel_sm_resp():
				pdu(CANCEL_SM_RESP) {

			}

			virtual cancel_sm_resp() {

			}
		};



	};

};
#endif /* SMPP_PDU_CANCEL_SM_H_ */
