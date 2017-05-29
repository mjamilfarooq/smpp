//============================================================================
// Name        : mysmpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "smpp/pdu/alert_notification.h"
#include "smpp/pdu/bind_pdu.h"
#include "smpp/pdu/data_sm.h"
#include "smpp/pdu/outbind.h"
#include "smpp/pdu/submit_sm.h"
#include "smpp/pdu/unbind.h"
#include "utils/network/tcp/client.h"

using namespace std;
using namespace smpp::pdu;


int main() {

	smpp::pdu::data_sm pck;
	smpp::pdu::submit_sm sm;

	pck.destination_addr.npi = smpp::address::NPI_DATA;
	pck.destination_addr.npi = smpp::address::NPI_ERMES;

	smpp::pdu::bind_transmitter trns("system_id", "password");
//	smpp::pdu::bind_transmitter abc;

	smpp::pdu::ussd_service_op so(123);

	smpp::pdu::outbind out("system_id", "password");
	smpp::pdu::unbind_resp ub;

	alert_notification alert(0, 0, "abcd", 0, 0, "efgh");

	cout<<so.value[0];

	cout << "!!!Hello World!!! "<<sizeof(sm.destination_addr.addr) << endl; // prints !!!Hello World!!!

	utils::tcp::client smpp_client("127.0.0.1", 2775);

	if ( smpp_client.connect() ) {
		std::cout<<"connected to smpp server"<<std::endl;
		smpp::pdu::bind_transceiver transceiver("smppclient1", "password");
		auto buffer = std::unique_ptr<uint8_t []>(transceiver.to_buffer());
		smpp_client.write(std::move(buffer), transceiver.size());
	}

	return 0;
}

