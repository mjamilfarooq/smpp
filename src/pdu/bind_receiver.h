/*
 * bind_receiver.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_BIND_RECEIVER_H_
#define PDU_BIND_RECEIVER_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {

		struct bind_receiver: public pdu {
			char system_id[16];
			char password[9] ;
			char system_type[13];
			uint8_t interface_version;
			uint8_t addr_ton;
			uint8_t addr_npi;
			char address_range[41];
	
			bind_receiver():
				pdu(BIND_RECEIVER){
			}

			virtual ~bind_receiver(){

			}
		};

		struct bind_receiver_resp: public pdu {
			char system_id[16];
			//optional TLVs
			//sc_interface_version TLV SMPP version supported by MC
			bind_receiver_resp():
				pdu(BIND_RECEIVER_RESP) {
			}

			virtual ~bind_receiver_resp(){

			}
		};



	};

};
#endif /* PDU_BIND_RECEIVER_H_ */
