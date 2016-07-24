/*
 * outbind.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_OUTBIND_H_
#define PDU_OUTBIND_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

	
		struct outbind: public pdu {
			char system_id[16];
			char password[9];

			outbind():
				pdu(OUTBIND) {
			}

			virtual ~outbind() {

			}
		};


	};

};
#endif /* PDU_OUTBIND_H_ */
