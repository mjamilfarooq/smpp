/*
 * enquire_link.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_ENQUIRE_LINK_H_
#define SMPP_PDU_ENQUIRE_LINK_H_

#include "pdu.h"

#pragma pack(push, 1)

namespace smpp {
	namespace pdu {

		class enquire_link: public pdu {
		public:
			enquire_link(uint32_t sequence_number):
				pdu(ENQUIRE_LINK) {
				set_seqnum(sequence_number);
			}
		};


		class enquire_link_resp: public pdu {
		public:
			enquire_link_resp(uint32_t sequence_number):
				pdu(ENQUIRE_LINK_RESP) {
				set_seqnum(sequence_number);
			}
		};
	};
};

#pragma pack(pop)
#endif /* SMPP_PDU_ENQUIRE_LINK_H_ */
