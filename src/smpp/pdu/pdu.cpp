/*
 * pdu.cpp
 *
 *  Created on: Dec 24, 2016
 *      Author: jamil
 */

#include "pdu.h"

namespace smpp{
	namespace pdu {

	pdu::pdu(const uint32_t command_id, const uint32_t sequence_number):
		command_length(size()),
		command_id(command_id),
		command_status(0),
		sequence_number(sequence_number) {

	}

	size_t pdu::size() {
		return sizeof(command_length) +
				sizeof(command_id) +
				sizeof(command_status) +
				sizeof(sequence_number);
	}


	buffer_type pdu::to_buffer() {

		auto buffer = buffer_type(command_length);

		buffer += command_length;
		buffer += command_id;
		buffer += command_status;
		buffer += sequence_number;

		return buffer;
	}


	buffer_type pdu::from_buffer(buffer_type buffer) {

		command_length += buffer;
		command_id += buffer;
		command_status += buffer;
		sequence_number += buffer;

		return buffer;

	}

	pdu::~pdu() {

	}

	}
}

