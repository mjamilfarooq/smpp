/*
 * alert_notification.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_ALERT_NOTIFICATION_H_
#define PDU_ALERT_NOTIFICATION_H_

#include "pdu.h"

namespace smpp {
	namespace pdu {


		/*
		 * the alert_notification PDU is sent by the MC to the ESME across a Receiver
		 * or Transceiver session. it is sent when the MC has detected that a particular
		 * mobile subscriber has become available.
		 */
		struct alert_notification: public pdu {
			uint8_t source_addr_ton;
			uint8_t source_addr_npi;
			char source_addr[65];
			uint8_t esme_addr_ton;
			uint8_t esme_addr_npi;
			char esme_addr[65];
	
			//Optional TLV
			//ms_availability_status	//this is status of mobile station

			alert_notification():
				pdu(ALERT_NOTIFICATION) {

			}

			virtual ~alert_notification() {

			}
		};



	};

};
#endif /* PDU_ALERT_NOTIFICATION_H_ */
