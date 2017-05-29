/*
 * session.h
 *
 *  Created on: Jan 29, 2017
 *      Author: jamil
 */

#ifndef SMPP_SESSION_SESSION_H_
#define SMPP_SESSION_SESSION_H_

#include <atomic>
#include <memory>
#include <unordered_map>

#include "../../utils/utils.h"
#include "../../utils/network/network.h"
#include "../pdu/defines.h"



namespace smpp {
namespace session {



#define SMPP_MAXIMUM_PACKET_SIZE 1024

	enum Type {
		BOUND_TX,
		BOUND_RX,
		BOUND_TRX,
		OUTBOUND,
	};


	struct configuration {
		Type type;
		std::string ip;
		uint16_t port;
		std::string system_id;
		std::string password;
		std::string system_type;
		uint8_t smpp_version;
		uint8_t addr_ton;
		uint8_t addr_npi;
		std::string address_range;

		uint32_t enquire_link_timeout;
		uint32_t inactivity_timeout;
		uint32_t transaction_timeout;


	};

	enum state {
		STATE_OPEN,
		STATE_BOUND_TX,
		STATE_BOUND_RX,
		STATE_BOUND_TRX,
		STATE_UNBOUND,
		STATE_CLOSED,
		STATE_OUTBOUND,
	};

	using namespace utils::network;

	class session {

		std::unordered_map<uint32_t, std::shared_ptr<pdu::pdu>> request_map;
		std::mutex mtx;

		const configuration config;
		std::atomic_uint sequence_number;	//must initialize with one
		connection::pointer tcp_connection;

		state _state;

		void process_response(std::shared_ptr<pdu::pdu>, std::shared_ptr<pdu::pdu>);

	public:
		session(const configuration&);
		bool bind(connection::pointer);
		void unbind();
		virtual ~session();
		virtual void run();

		state get_state();

	protected:
		virtual void on_bind() = 0;
		virtual void on_unbind() = 0;

	};

} /* namespace session */
} /* namespace smpp */

#endif /* SMPP_SESSION_SESSION_H_ */
