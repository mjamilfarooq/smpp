/*
 * bind_transmitter.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_BIND_TRANSMITTER_H_
#define PDU_BIND_TRANSMITTER_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

		//session management operations

		/*
		 *
		 */
		struct bind_transmitter: public pdu {
			char system_id[16];
			char password[9] ;
			char system_type[13];
			uint8_t interface_version;
			uint8_t addr_ton;
			uint8_t addr_npi;
			char address_range[41];

			bind_transmitter():
				pdu(BIND_TRANSMITTER) {
			}

			virtual ~bind_transmitter(){

			}
		};

		struct bind_transmitter_resp: public pdu {
			char system_id[16];
			//optional TLVs
			//sc_interface_version TLV SMPP version supported by MC
			bind_transmitter_resp():
				pdu(BIND_TRANSMITTER_RESP) {
			}

			virtual ~bind_transmitter_resp(){

			}
		};



	};

};



#endif /* PDU_BIND_TRANSMITTER_H_ */
