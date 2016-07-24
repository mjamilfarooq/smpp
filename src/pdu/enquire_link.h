/*
 * enquire_link.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_ENQUIRE_LINK_H_
#define PDU_ENQUIRE_LINK_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

		struct enquire_link: public pdu {
			enquire_link ():
				pdu(ENQUIRE_LINK) {
	
			}

			virtual ~enquire_link() {

			}
		};

		struct enquire_link_resp: public pdu {
			enquire_link_resp ():
				pdu(ENQUIRE_LINK_RESP) {
			}

			virtual ~enquire_link_resp() {

			}
		};

	};

};
#endif /* PDU_ENQUIRE_LINK_H_ */
