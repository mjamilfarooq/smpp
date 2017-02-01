/*
 * bind_pdu.cpp
 *
 *  Created on: Dec 24, 2016
 *      Author: jamil
 */




#include "bind_pdu.h"
#include <iostream>

namespace smpp {
namespace pdu {

	bind_pdu::bind_pdu(buffer_type buffer) {
		from_buffer(std::move(buffer));
	}

	bind_pdu::bind_pdu( const uint32_t bind_type,
			const std::string system_id,
			const std::string password,
			const uint32_t sequence_number,
			const std::string system_type,
			const uint8_t interface_version,
			const uint8_t addr_ton,
			const uint8_t addr_npi,
			const std::string address_range):
				pdu(bind_type, sequence_number),
				system_id(system_id),
				password(password),
				system_type(system_type),
				interface_version(interface_version),
				addr_ton(addr_ton),
				addr_npi(addr_npi),
				address_range(address_range) {


		set_length(size());
	}

	size_t bind_pdu::size() {
		return 	pdu::size() +
				system_id.length() +
				password.length() +
				system_type.length() +
				sizeof(interface_version) +
				sizeof(addr_ton) +
				sizeof(addr_npi) +
				address_range.length();
	}

	/*
	 * @brief converts pdu to buffer caller must delete memory after use
	 *
	 * @return pointer to uint8_t type or nullptr if function fails.
	 */
	buffer_type bind_pdu::to_buffer() {
		auto buffer = pdu::to_buffer();

		buffer += system_id;
		buffer += password;
		buffer += system_type;
		buffer += interface_version;
		buffer += addr_ton;
		buffer += addr_npi;
		buffer += address_range;

		return buffer;
	}


	/*
	 * @brief populate values of bind_pdu from the buffer given in parameter
	 *
	 * @param buffer to be copy from.
	 */
	buffer_type bind_pdu::from_buffer(buffer_type in) {

		auto buffer = pdu::from_buffer(std::move(in));

		std::cout<<" buffer length "<<buffer.length()<<" command length "<<command_length<< std::endl;

		system_id += buffer;
		password += buffer;
		system_type += buffer;
		interface_version += buffer;
		addr_ton += buffer;
		addr_npi += buffer;
		address_range += buffer;

		return buffer;
	}


	bind_pdu_resp::bind_pdu_resp(buffer_type buffer) {
		from_buffer(std::move(buffer));
	}

	bind_pdu_resp::bind_pdu_resp():
		version(nullptr) {
	}

	bind_pdu_resp::bind_pdu_resp(const uint32_t bind_type, const std::string &system_id, const uint32_t sequence_number):
		pdu(bind_type, sequence_number),
		system_id(system_id),
		version(nullptr) {
		set_length(size());
	}


	bind_pdu_resp::bind_pdu_resp(const uint32_t bind_type, const std::string &system_id, const uint8_t version, const uint32_t sequence_number):
		pdu(bind_type, sequence_number),
		system_id(system_id),
		version(new sc_interface_version(version)) {
		set_length(size());
	}

	size_t bind_pdu_resp::size() {
		return 	pdu::size() +
				system_id.length();
	}

	buffer_type bind_pdu_resp::to_buffer() {
		auto buffer = pdu::to_buffer();

		buffer += system_id;
//		buffer += version;	//this requires implementation

		return buffer;
	}

	buffer_type bind_pdu_resp::from_buffer(buffer_type in) {

		auto buffer = pdu::from_buffer(std::move(in));
		system_id += buffer;
//		version.get()

		return buffer;
	}

	bind_pdu_resp::~bind_pdu_resp() {
	}
}
}

