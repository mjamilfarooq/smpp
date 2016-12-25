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

	bind_pdu::bind_pdu( const uint32_t bind_type,
			const std::string system_id,
			const std::string password,
			const std::string system_type,
			const uint8_t interface_version,
			const uint8_t addr_ton,
			const uint8_t addr_npi,
			const std::string address_range):
				pdu(bind_type),
				interface_version(interface_version),
				addr_ton(addr_ton),
				addr_npi(addr_npi) {

		coctet_cpy(this->system_id, system_id.c_str(), sizeof(this->system_id));
		coctet_cpy(this->password, password.c_str(), sizeof(this->password));
		coctet_cpy(this->system_type, system_type.c_str(), sizeof(this->system_type));
		coctet_cpy(this->address_range, address_range.c_str(), sizeof(this->address_range));

		set_length(size());
	}

	size_t bind_pdu::size() {
		return 	pdu::size() +
				std::min(sizeof(system_id), strlen(system_id)+1) +
				std::min(sizeof(password), strlen(password)+1) +
				std::min(sizeof(system_type), strlen(system_type)+1) +
				sizeof(interface_version) +
				sizeof(addr_ton) +
				sizeof(addr_npi) +
				std::min(sizeof(address_range), strlen(address_range)+1);
	}

	/*
	 * @brief converts pdu to buffer caller must delete memory after use
	 *
	 * @return pointer to uint8_t type or nullptr if function fails.
	 */
	buffer_type bind_pdu::to_buffer() {
		auto buffer = pdu::to_buffer();

		if ( buffer_null == buffer ) {
			//TODO: error handling
			return buffer_null;
		}

		auto copy_offset = pdu::size();
		//copy this structure to buffer

		auto dest = reinterpret_cast<char *>(buffer.first.get());

		copy_offset += coctet_cpy(dest+copy_offset, system_id, std::min(strlen(system_id)+1, sizeof(system_id)));
		copy_offset += coctet_cpy(dest+copy_offset, password, std::min(strlen(password)+1, sizeof(password)));
		copy_offset += coctet_cpy(dest+copy_offset, system_type, std::min(strlen(system_type)+1, sizeof(system_type)));
		::memcpy(dest+copy_offset, &interface_version, sizeof(interface_version));
		copy_offset += sizeof(interface_version);
		::memcpy(dest+copy_offset, &addr_ton, sizeof(addr_ton));
		copy_offset += sizeof(addr_ton);
		::memcpy(dest+copy_offset, &addr_npi, sizeof(addr_npi));
		copy_offset += sizeof(addr_npi);
		copy_offset += coctet_cpy(dest+copy_offset, address_range, std::min(strlen(address_range)+1, sizeof(address_range)));

		buffer.second = copy_offset;

		return buffer;
	}


	/*
	 * @brief populate values of bind_pdu from the buffer given in parameter
	 *
	 * @param buffer to be copy from.
	 */
	size_t bind_pdu::from_buffer(buffer_type in) {

		auto copy_offset = pdu::from_buffer(in);

		if ( 0 == copy_offset ) return 0;

		auto buffer = reinterpret_cast<char *>(in.first.get());

		copy_offset += coctet_cpy(system_id, buffer+copy_offset, sizeof(system_id));
		copy_offset += coctet_cpy(password, buffer+copy_offset, sizeof(password));
		copy_offset += coctet_cpy(system_type, buffer+copy_offset, sizeof(system_type));
		::memcpy(&interface_version, buffer+copy_offset, sizeof(interface_version));
		copy_offset += sizeof(interface_version);
		::memcpy(&addr_ton, buffer+copy_offset, sizeof(addr_ton));
		copy_offset += sizeof(addr_ton);
		::memcpy(&addr_npi, buffer+copy_offset, sizeof(addr_npi));
		copy_offset += sizeof(addr_npi);
		copy_offset += coctet_cpy(address_range, buffer+copy_offset, sizeof(address_range));

		command_length = copy_offset;
		return command_length;
	}

	bind_pdu_resp::bind_pdu_resp(const uint32_t bind_type, const std::string &system_id):
		pdu(bind_type),
		version(nullptr) {
		coctet_cpy(this->system_id, system_id.c_str(), sizeof(this->system_id));
		set_length(size());
	}

	bind_pdu_resp::bind_pdu_resp(const uint32_t bind_type, const std::string &system_id, const uint8_t version):
		pdu(bind_type),
		version(new sc_interface_version(version)) {
		coctet_cpy(this->system_id, system_id.c_str(), sizeof(this->system_id));
		set_length(size());
	}

	size_t bind_pdu_resp::size() {
		return 	pdu::size() +
				std::min(sizeof(system_id), strlen(system_id)+1);
	}

	buffer_type bind_pdu_resp::to_buffer() {
		auto buffer = pdu::to_buffer();
		if ( buffer_null == buffer ) {
			return buffer_null;
		}

		auto copy_offset = pdu::size();
//		//copy this structure to buffer
		auto dest = reinterpret_cast<char *>(buffer.first.get());
		copy_offset += coctet_cpy(dest+copy_offset, system_id, std::min(strlen(system_id)+1, sizeof(system_id)));
		if ( nullptr != version ) copy_offset += version->to_buffer(reinterpret_cast<uint8_t *>(dest)+copy_offset);

		buffer.second = copy_offset;
		return buffer;
	}

	size_t bind_pdu_resp::from_buffer(buffer_type in) {
		if ( buffer_null == in ) return 0;
		auto copy_offset = pdu::from_buffer(in);

		auto buffer = reinterpret_cast<char *>(in.first.get());

		copy_offset += coctet_cpy(system_id, buffer+copy_offset, sizeof(system_id));

//		if ( command_length - copy_offset != sizeof(sc_interface_version(0)) ) { // no sc_interface_version
//			return copy_offset;
//		}
//
//		version = new sc_interface_version(0);
//		copy_offset += version->from_buffer(buffer+copy_offset);
		command_length = copy_offset;
		return command_length;
	}

	bind_pdu_resp::~bind_pdu_resp() {
		if ( nullptr != version ) delete version;
	}
}
}

