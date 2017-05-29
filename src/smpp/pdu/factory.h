/*
 * factory.h
 *
 *  Created on: Feb 1, 2017
 *      Author: jamil
 */

#ifndef SMPP_PDU_FACTORY_H_
#define SMPP_PDU_FACTORY_H_

#include "unbind.h"
#include "bind_pdu.h"


namespace smpp {
	namespace pdu {
		class factory {
		public:
			static std::unique_ptr<pdu> create(buffer_type buffer) {
				pdu temp;
				buffer = temp.from_buffer(std::move(buffer));
				if ( temp.get_status() != STATUS_SUCCESS ) return nullptr;
				buffer.reset();
				std::unique_ptr<pdu> ret;

				switch ( temp.get_id() ) {

				case BIND_TRANSMITTER_RESP:
					ret = make_unique<bind_transmitter_resp>(std::move(buffer));
					break;
				case BIND_RECEIVER_RESP:
					ret = make_unique<bind_receiver_resp>(std::move(buffer));
					break;

				case UNBIND_RESP:
					ret = make_unique<unbind_resp>(std::move(buffer));
					break;
				case BIND_TRANSCEIVER_RESP:
					ret = make_unique<bind_transceiver_resp>(std::move(buffer));
					break;
				default:
					ret = nullptr;
					break;
				}

				return ret;

			}
		};

	}
}



#endif /* SMPP_PDU_FACTORY_H_ */
