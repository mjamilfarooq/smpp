//============================================================================
// Name        : mysmpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "pdu/submit_sm.h"
#include "pdu/data_sm.h"

using namespace std;

int main() {

	smpp::pdu::data_sm pck;
	smpp::pdu::submit_sm sm;

	pck.destination_addr.npi = smpp::address::NPI_DATA;
	pck.destination_addr.npi = smpp::address::NPI_ERMES;


	smpp::pdu::ussd_service_op so(123);

	cout<<so.value[0];

	cout << "!!!Hello World!!! "<<sizeof(sm.destination_addr.addr) << endl; // prints !!!Hello World!!!
	return 0;
}
