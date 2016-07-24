/*
 * bind_transceiver.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_BIND_TRANSCEIVER_H_
#define PDU_BIND_TRANSCEIVER_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

		struct bind_transceiver: public pdu {
			char system_id[16];
			char password[9] ;
			char system_type[13];
			uint8_t interface_version;
			uint8_t addr_ton;
			uint8_t addr_npi;
			char address_range[41];
	
			bind_transceiver():
				pdu(BIND_TRANSCEIVER){
			}

			virtual ~bind_transceiver(){

			}
		};

		struct bind_transceiver_resp: public pdu {
			char system_id[16];
			//optional TLVs
			//sc_interface_version TLV SMPP version supported by MC
			bind_transceiver_resp():
				pdu(BIND_TRANSCEIVER_RESP) {
			}

			virtual ~bind_transceiver_resp() {

			}
		};



	};

};
#endif /* PDU_BIND_TRANSCEIVER_H_ */
