/*
 * alert_notification.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_ALERT_NOTIFICATION_H_
#define SMPP_PDU_ALERT_NOTIFICATION_H_

#include "../smpp/pdu/pdu.h"

namespace smpp {
	namespace pdu {


		/*
		 * the alert_notification PDU is sent by the MC to the ESME across a Receiver
		 * or Transceiver session. it is sent when the MC has detected that a particular
		 * mobile subscriber has become available.
		 */
		class alert_notification: public pdu {
		private:
			smpp::address::address<65> source_addr;
			smpp::address::address<65> esme_addr;
	
			//Optional TLV
			ms_availability_status	*availability_status; //this is status of mobile station

			size_t size() {
				return 	sizeof(source_addr)
						+ sizeof(esme_addr)
						+ availability_status == nullptr? 0 : availability_status->size();
			}

		public:
			alert_notification(const uint8_t source_addr_ton,
					const uint8_t source_addr_npi,
					const std::string &source_addr,
					const uint8_t esme_addr_ton,
					const uint8_t esme_addr_npi,
					const std::string &esme_addr):
				pdu(ALERT_NOTIFICATION),
				source_addr(source_addr_ton, source_addr_npi, source_addr),
				esme_addr(esme_addr_ton, esme_addr_npi, esme_addr),
				availability_status(nullptr) {

			}

			alert_notification(const uint8_t source_addr_ton,
					const uint8_t source_addr_npi,
					const std::string &source_addr,
					const uint8_t esme_addr_ton,
					const uint8_t esme_addr_npi,
					const std::string &esme_addr,
					const uint8_t status):
				pdu(ALERT_NOTIFICATION),
				source_addr(source_addr_ton, source_addr_npi, source_addr),
				esme_addr(esme_addr_ton, esme_addr_npi, esme_addr),
				availability_status(new ms_availability_status(status)) {

			}

			~alert_notification() {
				delete availability_status;
			}
		};



	};

};
#endif /* SMPP_PDU_ALERT_NOTIFICATION_H_ */
