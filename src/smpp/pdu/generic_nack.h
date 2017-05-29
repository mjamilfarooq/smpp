/*
 * generic_nack.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_GENERIC_NACK_H_
#define SMPP_PDU_GENERIC_NACK_H_

#include "../smpp/pdu/pdu.h"

namespace smpp {
	namespace pdu {


		/*
		 * generic_nack PDU is used to acknowledge the submission of an unrecognized
		 * or corrupt PDU
		 */
		struct generic_nack: public pdu {
			generic_nack():
				pdu(GENERIC_NACK) {
			}

			virtual ~generic_nack() {

			}
		};



	};

};
#endif /* SMPP_PDU_GENERIC_NACK_H_ */
