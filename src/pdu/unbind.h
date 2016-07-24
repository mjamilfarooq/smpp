/*
 * unbind.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_UNBIND_H_
#define PDU_UNBIND_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

		struct unbind: public pdu {
			unbind():
				pdu(UNBIND) {
			}

			virtual ~unbind() {

			}
		};

		struct unbind_resp: public pdu {
			unbind_resp():
				pdu(UNBIND_RESP){
			}

			virtual ~unbind_resp() {

			}
		};
	



	};

};
#endif /* PDU_UNBIND_H_ */
