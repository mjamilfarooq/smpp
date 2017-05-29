/*
 * session.cpp
 *
 *  Created on: Jan 29, 2017
 *      Author: jamil
 */

#include "session.h"

using namespace smpp::pdu;

namespace smpp {
namespace session {



session::session(const configuration& config):
	_state(STATE_CLOSED),
	config(config),
	sequence_number(1),
	tcp_connection(nullptr) {

}



bool session::bind(connection::pointer socket_connection) {

	if ( socket_connection ) _state = state::STATE_OPEN;	//network connection is established
	else return false;

	this->tcp_connection = socket_connection;
	std::unique_ptr<pdu::pdu> bind_request;
	if ( config.type == Type::BOUND_TX ) {

	} else if ( config.type == Type::BOUND_RX ) {

	} else if ( config.type == Type::BOUND_TRX ) {
		bind_request = make_unique<bind_transceiver>(
				config.system_id,
				config.password,
				sequence_number++,
				config.system_type,
				config.smpp_version,
				config.addr_ton,
				config.addr_npi,
				config.address_range);
	} else if ( config.type == Type::OUTBOUND ) {

	} else {
		tcp_connection->disconnect();
		return false;
	}



	if ( !tcp_connection->write(bind_request->to_buffer()) )
		return false;

	request_map[bind_request->get_seqnum()] = std::move(bind_request);

	auto response = factory::create(tcp_connection->read());
	if ( response == nullptr ) {
		std::cout<<"response not received!!!"<<std::endl;
		return false;
	}

	if ( response->get_status() != pdu::STATUS_SUCCESS ) {
		std::cout<<"bind unsuccessful!!!!"<<std::endl;
		return false;
	}

	on_bind();	//callback function will only be called if entire bind operation is successfull
	return true;
}

void session::process_response(std::shared_ptr<pdu::pdu> request, std::shared_ptr<pdu::pdu> response) {

}

void session::on_bind() {

}

void session::unbind() {

	auto unbind_request = pdu::unbind(sequence_number++);
	tcp_connection->write(unbind_request.to_buffer());


	auto response = pdu::factory::create(tcp_connection->read());

	if ( 	*response == pdu::UNBIND_RESP &&	//if packet received is unbind_resp packet
			response->get_seqnum() == unbind_request.get_seqnum() &&	//sequence number is same as sent in unbind_request packet
			response->get_status() == pdu::STATUS_SUCCESS ) {	//and status is success
		on_unbind();	//callback function will only be called if entrie unbind operation is successfull
	}

}

state session::get_state() {
	return _state;
}

void session::run() {
	while (true) {
		auto received = pdu::factory::create(tcp_connection->read());

		if ( received->is_response() ) {
			auto response = std::move(received);
			auto is_exist = request_map.find(response->get_seqnum());
			if ( is_exist != request_map.end() ) {
				auto request = is_exist->second;
				process_response(request, std::move(response));
			}

		}


	}
}

session::~session() {
	// TODO Auto-generated destructor stub
}

} /* namespace session */
} /* namespace smpp */
