/*
 * pdu.cpp
 *
 *  Created on: Dec 24, 2016
 *      Author: jamil
 */

#include "pdu.h"

namespace smpp{
	namespace pdu {

	pdu::pdu(uint32_t command_id):
		command_length(size()),
		command_id(command_id),
		command_status(0),
		sequence_number(0) {

	}

	size_t pdu::size() {
		return sizeof(command_length) +
				sizeof(command_id) +
				sizeof(command_status) +
				sizeof(sequence_number);
	}


	buffer_type pdu::to_buffer() {

		auto buffer = create_buffer(command_length);
		if ( nullptr == buffer.first ) {
			//TODO: report this event on console and log
			return buffer_null;
		}

		size_t copy_offset = 0;

		auto dest = buffer.first.get();

		auto data = htonl(command_length);
		auto length = sizeof(command_length);
		std::memcpy(dest + copy_offset, &data, length); copy_offset += length;

		data = htonl(command_id);
		length = sizeof(command_id);
		std::memcpy(dest + copy_offset, &data, length); copy_offset += length;

		data = htonl(command_status);
		length = sizeof(command_status);
		std::memcpy(dest + copy_offset, &data, length); copy_offset += length;

		data = htonl(sequence_number);
		length = sizeof(sequence_number);
		std::memcpy(dest + copy_offset, &data, length); copy_offset += length;

		buffer.second = copy_offset;

		return buffer;
	}


	size_t pdu::from_buffer(buffer_type in) {

		if ( buffer_null == in ) {
			//TODO: report this event on console and log
			return 0;
		}

		auto buffer = in.first.get();
		if ( nullptr == buffer ) {
			return 0;
		}

		auto copy_offset = size_t(0);

		std::memcpy(&command_length, buffer+copy_offset, sizeof(command_length));
		copy_offset += sizeof(command_length);
		command_length = ntohl(command_length);

		std::memcpy(&command_id, buffer+copy_offset, sizeof(command_id));
		copy_offset += sizeof(command_id);
		command_id = ntohl(command_id);

		std::memcpy(&command_status, buffer+copy_offset, sizeof(command_status));
		copy_offset += sizeof(command_status);
		command_status = ntohl(command_status);

		std::memcpy(&sequence_number, buffer+copy_offset, sizeof(sequence_number));
		copy_offset += sizeof(sequence_number);
		sequence_number = ntohl(sequence_number);

		return copy_offset;

	}

	pdu::~pdu() {

	}

	}
}

