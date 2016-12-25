/*
 * address.h
 *
 *  Created on: Dec 24, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_ADDRESS_H_
#define SMPP_PDU_ADDRESS_H_


namespace smpp {
namespace address {
	//SMPP ADDRESS TYPE OF NUMBER
	const static uint8_t TON_UNKNOWN 			= 0b00000000;
	const static uint8_t TON_INTERNATIONAL 		= 0b00000001;
	const static uint8_t TON_NATIONAL 			= 0b00000010;
	const static uint8_t TON_NETWORK_SPECIFIC 	= 0b00000011;
	const static uint8_t TON_SUBSCRIBER_NUMBER 	= 0b00000100;
	const static uint8_t TON_ALPHANUMERIC 		= 0b00000101;
	const static uint8_t TON_ABBREVIATED 		= 0b00000110;

	//SMPP ADDRESS Numeric Plan Indicator
	const static uint8_t NPI_UNKNOWN 		= 0b00000000;
	const static uint8_t NPI_ISDN 			= 0b00000001;
	const static uint8_t NPI_DATA 			= 0b00000011;
	const static uint8_t NPI_TELEX 			= 0b00000100;
	const static uint8_t NPI_LAND_MOBILE 	= 0b00000110;
	const static uint8_t NPI_NATIONAL 		= 0b00001000;
	const static uint8_t NPI_PRIVATE 		= 0b00001001;
	const static uint8_t NPI_ERMES 			= 0b00001010;
	const static uint8_t NPI_INTERNET  		= 0b00001110;
	const static uint8_t NPI_WAP_CLIENT_ID 	= 0b00010010;

	/*
	 * @brief address structure define general source/destination address format used by smpp
	 */
	template <size_t n>
	struct address {
		uint8_t ton;
		uint8_t npi;
		char addr[n];

		address():
			ton(smpp::address::TON_UNKNOWN),
			npi(smpp::address::NPI_UNKNOWN) {
		}

		address(uint8_t ton, uint8_t npi, const std::string & addr):
			ton(ton), npi(npi) {
			::memcpy(this->addr, addr.c_str(), std::min(addr.size()+1, n));
		}

		size_t size() {
			return sizeof(ton)
					+ sizeof(npi)
					+ std::min(strnlen(addr, n)+1, n);
		}

		size_t to_buffer(uint8_t * const buffer) {
			::memcpy(buffer, this, size());
			return size();	//no of bytes copied
		}

		size_t from_buffer(const uint8_t * const buffer) {
			if ( nullptr == buffer ) return 0;
			ton = buffer[0];
			npi = buffer[1];
			strncpy(addr, buffer, std::min(strnlen((char *)buffer, n)+1, n));
		}
	};


};
};


#endif /* SMPP_PDU_ADDRESS_H_ */
