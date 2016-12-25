/*
 * bind_pdu.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_BIND_PDU_H_
#define SMPP_PDU_BIND_PDU_H_

#include "pdu.h"


namespace smpp {
	namespace pdu {

	class bind_pdu: public pdu {
		char system_id[16];
		char password[9] ;
		char system_type[13];
		uint8_t interface_version;
		uint8_t addr_ton;
		uint8_t addr_npi;
		char address_range[41];

		size_t size();

	public:

		bind_pdu() = default;
		bind_pdu(const uint32_t,
				const std::string,
				const std::string,
				const std::string = "",
				const uint8_t = smpp::SMPP_VERSION_0x33,
				const uint8_t = smpp::address::TON_UNKNOWN,
				const uint8_t = smpp::address::NPI_UNKNOWN,
				const std::string = "");

		virtual buffer_type to_buffer();
		virtual size_t from_buffer(buffer_type);


		char* get_systemid();
		char* get_password();
		char* get_systemtype();
		uint8_t get_interface_version();
		uint8_t get_addr_ton();
		uint8_t get_addr_npi();
		char* get_address_range();

//		void set_systemid(std::string);
//		void set_password(std::string);
//		void set_systemtype();
//		void set_interface_version();
//		void set_addr_ton();
//		void set_addr_npi();
//		void set_address_range();


	};

	inline char* bind_pdu::get_systemid() {
		return system_id;
	}

	inline char* bind_pdu::get_password() {
		return password;
	}

	inline char* bind_pdu::get_systemtype() {
		return system_type;
	}

	uint8_t bind_pdu::get_interface_version() {
		return interface_version;
	}

	uint8_t bind_pdu::get_addr_ton() {
		return addr_ton;
	}

	uint8_t bind_pdu::get_addr_npi() {
		return addr_npi;
	}

	char* bind_pdu::get_address_range() {
		return address_range;
	}

	class bind_pdu_resp: public pdu {
	private:

		char system_id[16];				//< system id passed during bind_pdu request
		sc_interface_version *version;	//< optional interface version TLV passed by SMSC

		size_t size();

	public:

		bind_pdu_resp() = default;
		/*
		 * @brief construct bind transmitter resp packet
		 *
		 * @param system_id is the id given in bind_pdu request packet
		 *
		 */
		bind_pdu_resp(const uint32_t, const std::string &);

		/*
		 * @brief construct bind transmitter resp packet
		 *
		 * @param system_id is the id given in bind_pdu request packet
		 *
		 * @param version is the version of the smpp protocol for communication 0x33, 0x34 or 0x50
		 */
		bind_pdu_resp(const uint32_t, const std::string &, const uint8_t);


		/*
		 * @brief converts pdu to buffer caller must delete memory after use
		 *
		 * @return pointer to uint8_t type or nullptr if function fails.
		 */
		virtual buffer_type to_buffer();


		/*
		 * @brief populate values of bind_pdu from the buffer given in parameter
		 *
		 * @param buffer to be copy from.
		 *
		 * @number of bytes successfully copied from buffer
		 */
		size_t from_buffer(buffer_type);

		char* get_systemid();

		sc_interface_version* get_version();

		/*
		 * @brief deletes the only optional TLV
		 */
		~bind_pdu_resp();

	};

	inline char* bind_pdu_resp::get_systemid() {
		return system_id;
	}

	inline sc_interface_version* bind_pdu_resp::get_version() {
		return version;
	}

#define BIND_PDU(name, value) \
	class name: public bind_pdu { \
	public: \
		name() = default; \
		name(const std::string &system_id, \
				const std::string &password, \
				const std::string &system_type = "", \
				const uint8_t interface_version = smpp::SMPP_VERSION_0x33, \
				const uint8_t addr_ton = smpp::address::TON_UNKNOWN, \
				const uint8_t addr_npi = smpp::address::NPI_UNKNOWN, \
				const std::string &address_range = ""): \
					bind_pdu(value, system_id, password, system_type, interface_version, addr_ton, addr_npi, address_range) { \
		} \
	};


#define BIND_PDU_RESP(name, value) \
	class name: public bind_pdu_resp { \
	public: \
		name():bind_pdu_resp(value,"") { } \
		name(const std::string &system_id): \
				bind_pdu_resp(value, system_id) { \
		} \
		name(const std::string &system_id, const uint8_t version): \
			bind_pdu_resp(value, system_id, version) { \
		} \
	};

BIND_PDU(bind_transmitter, BIND_TRANSMITTER);
BIND_PDU(bind_receiver, BIND_RECEIVER);
BIND_PDU(bind_transceiver, BIND_TRANSCEIVER);
BIND_PDU_RESP(bind_transmitter_resp, BIND_TRANSMITTER_RESP);
BIND_PDU_RESP(bind_receiver_resp, BIND_RECEIVER_RESP);
BIND_PDU_RESP(bind_transceiver_resp, BIND_TRANSCEIVER_RESP);



	};

};


#endif /* SMPP_PDU_BIND_PDU_H_ */
