/*
 * tlv.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_TLV_H_
#define PDU_TLV_H_

#include "pdu.h"

#define SMPP_PDU_TLV_SIMPLE(name,tag_value,type) \
		struct name: public tlv { \
			name(type value): \
				tlv(tag_value, sizeof(type), &value) { \
			} \
		};


namespace smpp {
	namespace pdu {

	
		struct tlv {

			// TLV tags constants
			static const uint16_t DEST_ADDR_SUBUNIT 			= 0x0005;
			static const uint16_t DEST_NETWORK_TYPE				= 0x0006;
			static const uint16_t DEST_BEARER_TYPE				= 0x0007;
			static const uint16_t DEST_TELEMATICS_ID			= 0x0008;
			static const uint16_t SOURCE_ADDR_SUBUNIT 			= 0x000D;
			static const uint16_t SOURCE_NETWORK_TYPE			= 0x000E;
			static const uint16_t SOURCE_BEARER_TYPE			= 0x000F;
			static const uint16_t SOURCE_TELEMATICS_ID			= 0x0010;
			static const uint16_t QOS_TIME_TO_LIVE	 			= 0x0017;
			static const uint16_t PAYLOAD_TYPE					= 0x0019;
			static const uint16_t ADDITIONAL_STATUS_INFO_TEXT	= 0x001D;
			static const uint16_t RECEIPTED_MESSAGE_ID			= 0x001E;
			static const uint16_t MS_MSG_WAIT_FACILITIES 		= 0x0030;
			static const uint16_t PRIVACY_INDICATOR				= 0x0201;
			static const uint16_t SOURCE_SUBADDRESS				= 0x0202;
			static const uint16_t DEST_SUBADDRESS				= 0x0203;
			static const uint16_t USER_MESSAGE_REFERENCE 		= 0x0204;
			static const uint16_t USER_RESPONSE_CODE			= 0x0205;
			static const uint16_t SOURCE_PORT					= 0x020A;
			static const uint16_t DEST_PORT						= 0x020B;
			static const uint16_t SAR_MSG_REF_NUM		 		= 0x020C;
			static const uint16_t LANGUAGE_INDICATOR			= 0x020D;
			static const uint16_t SAR_TOTAL_SEGMENTS			= 0x020E;
			static const uint16_t SAR_SEGMENT_SEQNUM			= 0x020F;
			static const uint16_t SC_INTERFACE_VERSION	 		= 0x0210;
			static const uint16_t CALLBACK_NUM_PRES_IND			= 0x0302;
			static const uint16_t CALLBACK_NUM_ATAG				= 0x0303;
			static const uint16_t NUMBER_OF_MESSAGES			= 0x0304;
			static const uint16_t CALLBACK_NUM			 		= 0x0381;
			static const uint16_t DPF_RESULT					= 0x0420;
			static const uint16_t SET_DPF						= 0x0421;
			static const uint16_t MS_AVAILABILITY_STATUS		= 0x0422;
			static const uint16_t NETWORK_ERROR_CODE 			= 0x0423;
			static const uint16_t MESSAGE_PAYLOAD 				= 0x0424;
			static const uint16_t DELIVERY_FAILURE_REASON		= 0x0425;
			static const uint16_t MORE_MESSAGES_TO_SEND			= 0x0426;
			static const uint16_t MESSAGE_STATE					= 0x0427;
			static const uint16_t CONGESSION_STATE				= 0x0428;
			static const uint16_t USSD_SERVICE_OP				= 0x0501;
			static const uint16_t BROADCAST_CHANNEL_INDICATOR	= 0x0600;
			static const uint16_t BROADCAST_CONTENT_TYPE		= 0x0601;
			static const uint16_t BROADCAST_CONTENT_TYPE_INFO	= 0x0602;
			static const uint16_t BROADCAST_MESSAGE_CLASS		= 0x0603;
			static const uint16_t BROADCAST_REP_NUM				= 0x0604;
			static const uint16_t BROADCAST_FREQUENCY_INTERVAL	= 0x0605;
			static const uint16_t BROADCAST_AREA_IDENTIFIER		= 0x0606;
			static const uint16_t BROADCAST_ERROR_STATUS		= 0x0607;
			static const uint16_t BROADCAST_AREA_SUCCESS		= 0x0608;
			static const uint16_t BROADCAST_END_TIME			= 0x0609;
			static const uint16_t BROADCAST_SERVICE_GROUP		= 0x060A;
			static const uint16_t BILL_IDENTIFICATION			= 0x060B;
			static const uint16_t SOURCE_NETWORK_ID				= 0x060D;
			static const uint16_t DEST_NETWORK_ID				= 0x060E;
			static const uint16_t SOURCE_NODE_ID				= 0x060F;
			static const uint16_t DEST_NODE_ID					= 0x0610;
			static const uint16_t DEST_ADDR_NP_RESOLUTION		= 0x0611;
			static const uint16_t DEST_ADDR_NP_INFORMATION		= 0x0612;
			static const uint16_t DEST_ADDR_NP_COUNTRY			= 0x0613;
			static const uint16_t DISPLAY_TIME					= 0x1201;
			static const uint16_t SM_SIGNAL						= 0x1203;
			static const uint16_t MS_VALIDITY					= 0x1204;
			static const uint16_t ALERT_ON_MESSAGE_DELIVERY		= 0x130C;
			static const uint16_t ITS_REPLY_TYPE				= 0x1380;
			static const uint16_t ITS_SESSION_INFO				= 0x1383;


			//variable structure
			uint16_t tag;
			uint16_t length;
			uint8_t *value;

			tlv(uint16_t tag, uint16_t length, uint8_t *value )
				: tag(tag), length(length), value(nullptr) {
				this->value = new uint8_t[this->length];
				::memcpy(this->value, value, this->length);
			}

			~tlv() {
				delete [] value;
			}


			//setters
			template <class T>
			void set(const uint16_t tag, const T single) {
				this->tag = tag;
				length = sizeof(single);
				value = new uint8_t[length];
				::memcpy(value, &single, sizeof(single));
			}

			void set(const uint16_t tag, const std::string &octet_string, const size_t max = 0, const size_t min = 0) {
				this->tag = tag;

				if ( max != 0) length = std::max(std::min(octet_string.size(), max), min);
				else length = std::max(octet_string.size(), min);

				value = new uint8_t[length];
				::memcpy(value, octet_string.c_str(), length);
			}

			void set_additional_status_info_text(const std::string &text) {
				tag = ADDITIONAL_STATUS_INFO_TEXT;
				length = std::min(text.size(), size_t(255));
				value = new uint8_t[length];
				::memcpy(value, text.c_str(), length);
			}


			/*
			 * @brief settings for alert message on delivery this enable default behaviour
			 */
			void set_alert_on_message_delivery() {
				tag = ALERT_ON_MESSAGE_DELIVERY;
				length = 0;
				value = nullptr;
			}

			/*
			 * @brief settings priority for alert message on delivery
			 *
			 * @param priority value from 0 - 3 [default to High] 4 - 255 are reserved
			 */
			void set_alert_on_message_delivery(uint8_t priority) {
				tag = ALERT_ON_MESSAGE_DELIVERY;
				length = 1;
				value = new uint8_t[length];
				value[0] = priority;
			}


			/*
			 * @brief billing identification
			 *
			 * @param billing_format is the billing format tag indicates format of the billing information
			 *
			 * @param actual billing information to be embed as tlv
			 */
			void set_billing_identification(uint8_t billing_format, const std::string &billing_info) {
				tag = BILL_IDENTIFICATION;
				length = std::min(billing_info.size()+1, size_t(1024));
				value = new uint8_t[length];
				value[0] = billing_format;
				::memcpy(value+1, billing_info.c_str(), length-1);
			}

			/*
			 * @brief set the broadcast area identifier
			 *
			 * @param area_format defines the format of the area information
			 *
			 * @param area_info is the string defining the actual area information
			 */
			void set_broadcast_area_identifier(const uint8_t area_format, const std::string &area_info) {
				tag = BROADCAST_AREA_IDENTIFIER;
				length = area_info.size() + 1;
				value = new uint8_t[length];
				value[0] = area_format;
				::memcpy(value+1, area_info.c_str(), length-1);
			}


			/*
			 * @brief set the success rate indicator defined as the number of BTS who accepted the message and the
			 * total number who should accept the message
			 *
			 * @param value should be between 0-100 255 means information not available and all other values are
			 * reserved. for reserved values functions set the value to 255
			 *
			 */
			void set_broadcast_area_success(const uint8_t success_rate_indicator) {
				tag =BROADCAST_AREA_SUCCESS;
				length = 1;
				value = new uint8_t[1];
				value[0] = success_rate_indicator>100 && success_rate_indicator != 255 ? 255: success_rate_indicator;
			}

			/*
			 * @brief provide additional information specific to broadcast content type
			 *
			 * @param string containing type information of broadcast information
			 *
			 */
			void set_broadcast_content_type_info(const std::string &type_info) {
				tag = BROADCAST_CONTENT_TYPE_INFO;
				length = std::min(type_info.size(), size_t(255));
				value = new uint8_t[length];
				::memcpy(value, type_info.c_str(), length);
			}


			/*
			 * @brief set broadcast channel indicator
			 *
			 * @param set 0 = Basic Broadcast Channel 1 = Extended Broadcast Channel
			 */
			void set_broadcast_channel_indicator(const uint8_t indicator) {
				tag = BROADCAST_CHANNEL_INDICATOR;
				length = 1;
				value = new uint8_t[length];
				value[0] = indicator;
			}


			/*
			 * @brief set the broadcast content type
			 *
			 * @param tag 0 = Generic, 1 = GSM, 2 = TDMA, 3 = CDMA
			 *
			 * @param encoding_content_type defines if  tag = Generic and is defines if content is New, Subscriber info etc
			 */
			void set_broadcast_content_type(const uint8_t tag, const uint16_t encoding_content_type = 0) {
				this->tag = BROADCAST_CONTENT_TYPE;
				length = 3;
				value = new uint8_t[length];
				value[0] = tag;
				::memcpy(value+1, &encoding_content_type, sizeof(encoding_content_type));
			}

			/*
			 * @brief broadcast_end_time will set the end time for broadcast
			 *
			 * @param std::string must be in format “YYMMDDhhmmsstnnp” and of size 16
			 * if size is greater than 16 only 16 will be copied and if less then 16 only
			 * those were copied but response of the function is undefined in this case
			 */
			void set_broadcast_end_time(const std::string &end_time) {
				tag = BROADCAST_END_TIME;
				length = 16;
				value = new uint8_t[length];
				::memcpy(value, end_time.c_str(), std::min(end_time.size(), size_t(length)));
			}


			void set_broadcast_error_status(const uint32_t error_status) {
				tag = BROADCAST_ERROR_STATUS;
				length = 4;
				value = new uint8_t[length];
				::memcpy(value, &error_status, length);
			}

			void set_broadcast_frequency_interval(const uint8_t time_units, const uint16_t no_time_units) {
				tag = BROADCAST_FREQUENCY_INTERVAL;
				length = 3;
				value = new uint8_t[length];
				value[0] = time_units;
				::memcpy(value+1, &no_time_units, sizeof(no_time_units));
			}

			void set_broadcast_message_class(const uint8_t message_class) {
				tag = BROADCAST_MESSAGE_CLASS;
				length = 1;
				value = new uint8_t[length];
				value[0] = message_class;
			}

			void set_broadcast_rep_num(const uint16_t repeat) {
				tag = BROADCAST_REP_NUM;
				length = 2;
				value = new uint8_t[length];
				::memcpy(value, &repeat, length);
			}

			void set_broadcast_service_group(const std::string &service_group) {
				tag = BROADCAST_SERVICE_GROUP;
				length = std::min(service_group.size(), size_t(255));
				value = new uint8_t[length];
				::memcpy(value, service_group.c_str(), length);
			}


			void set_callback_num(const uint8_t digit_mode_indicator,
					const uint8_t ton,
					const uint8_t npi,
					const std::string &callback_number) {
				tag = CALLBACK_NUM;
				length = std::min(callback_number.size(), size_t(15)) + 4;
				value = new uint8_t[length];

				value[0] = digit_mode_indicator;
				value[1] = ton;
				value[2] = npi;
				::memcpy(value+3, callback_number.c_str(), length-4);
			}

			void set_callback_num_atag(const uint8_t coding_scheme, const std::string &display) {
				tag = CALLBACK_NUM_ATAG;
				length = 1 + std::min(display.size(), size_t(64));
				value = new uint8_t[length];
				value[0] = coding_scheme;
				::memcpy(value+1, display.c_str(), length-1);
			}

			void set_callback_num_pres_ind(const uint8_t indicator) {
				tag = CALLBACK_NUM_PRES_IND;
				length = 1;
				value = new uint8_t[length];
				value[0] = indicator;
			}

			void set_congestion_state(const uint8_t state) {
				tag = CONGESSION_STATE;
				length = 1;
				value = new uint8_t[length];
				value[0] = state;
			}

			void set_delivery_failure_reason(const uint8_t reason) {
				tag = DELIVERY_FAILURE_REASON;
				length = 1;
				value = new uint8_t[length];
				value[0] = reason;
			}

			void set_dest_addr_np_country(const uint64_t country_code) {
				tag = DEST_ADDR_NP_COUNTRY;
				length = 5;		//TODO: not clear if it will always be 5 byte or can be less also value representation is also not clear
				value = new uint8_t[length];
				::memcpy(value, &country_code, length);
			}


			void set_dest_addr_np_information(const std::string &information) {
				tag = DEST_ADDR_NP_INFORMATION;
				length = 10;
				value = new uint8_t[length];
				::memcpy(value, information.c_str(), length);
			}

			void set_dest_addr_np_resolution(const uint8_t indicator) {
				tag = DEST_ADDR_NP_RESOLUTION;
				length = 1;
				value = new uint8_t[length];
				value[0] = indicator;
			}

			void set_dest_addr_subunit(const uint8_t subunit) {
				tag = DEST_ADDR_SUBUNIT;
				length = 1;
				value = new uint8_t[length];
				value[0] = subunit;
			}

			void set_dest_bearer_type(const uint8_t type) {
				tag = DEST_BEARER_TYPE;
				length = 1;
				value = new uint8_t[length];
				value[0] = type;
			}

			void set_dest_network_id(const std::string &network_id) {
				tag = DEST_NETWORK_ID;
				length = std::max(std::min(network_id.size(), size_t(65)), size_t(7));
				value = new uint8_t[length];
				::memcpy(value, network_id.c_str(), std::min(network_id.size(), size_t(length)));
			}

			void set_dest_network_type(const uint8_t type) {
				tag = DEST_NETWORK_TYPE;
				length = 1;
				value = new uint8_t[length];
				value[0] = type;
			}

			void set_dest_node_id(const std::string &identity) {
				tag = DEST_NODE_ID;
				length = 6;
				value = new uint8_t[length];
				::memcpy(value, identity.c_str(), std::min(identity.size(), size_t(length)));
			}

			void set_dest_subaddress(const uint16_t subaddress_tag, const std::string &subaddress) {
				tag = DEST_SUBADDRESS;
				length = std::max(std::min(subaddress.size(), size_t(23)), size_t(2));
				value = new uint8_t[length];
				::memcpy(value, &subaddress_tag, sizeof(subaddress_tag));
				::memcpy(value+sizeof(subaddress_tag), subaddress.c_str(), std::min(subaddress.size(), size_t(length - sizeof(subaddress_tag))));
			}

			void set_dest_telematics_id(const uint8_t protocol_id) {
				tag = DEST_TELEMATICS_ID;
				length = 2;
				value = new uint8_t[length];
				value[0] = protocol_id;
			}

			void set_dest_port(const uint16_t port) {
				tag = DEST_PORT;
				length = 2;
				value = new uint8_t[length];
				::memcpy(value, &port, length);
			}

			void set_display_time(const uint8_t param) {
				tag = DISPLAY_TIME;
				length = 1;
				value = new uint8_t[length];
				value[0] = param;
			}


			void set_dpf_result(const bool set = true) {
				tag = DPF_RESULT;
				length = 1;
				value = new uint8_t[length];
				value[0] = set ? 1 : 0;	//all other values are reserved
			}

			void set_its_reply_type(const uint8_t reply_type) {
				tag = ITS_REPLY_TYPE;
				length = 1;
				value = new uint8_t[length];
				value[0] = reply_type;
			}

			/*
			 * @brief required for CDMA Interactive Teleservice control information for interactive session between ESME and MS
			 *
			 * @param represent session number
			 *
			 * @param sequence_number is sequence number of dialogue
			 *
			 * @param is_end represent if session has ended
			 */
			void set_its_session_info(const uint8_t session_number, const uint8_t sequence_number, const bool is_end = false) {
				tag = ITS_SESSION_INFO;
				length = 2;
				value = new uint8_t[length];
				value[0] = session_number;
				value[1] = (sequence_number << 1 ) | ( is_end ? 0x01 : 0X00);	//second octet 0th bit is is_end and 1-7th represent sequence number
			}


			void set_language_indicator(const uint8_t lang) {
				tag = LANGUAGE_INDICATOR;
				length = 1;
				value = new uint8_t[length];
				value[0] = lang;
			}

			void set_message_payload(const std::string &payload) {
				tag = MESSAGE_PAYLOAD;
				length = payload.size();
				value = new uint8_t[length];
				::memcpy(value, payload.c_str(), length);
			}

			void set_message_state(const uint8_t state) {
				set(MESSAGE_STATE, state);
			}

			void set_more_messages_to_send(const bool more = true) {
				set(MORE_MESSAGES_TO_SEND, uint8_t(more ? 1 : 0));	//values other than 0 and 1 are reserved
			}

			void set_ms_availability_status(const uint8_t status) {
				set(MS_AVAILABILITY_STATUS, status);
			}

			void set_ms_msg_wait_facilities(const uint8_t message_type, const bool set_indication_active = true ) {
				tag = MS_MSG_WAIT_FACILITIES;
				length = 1;
				value = new uint8_t[length];
				value[0] = (0x03 & message_type) | (set_indication_active? 0x80:0x00);
			}

			void set_ms_validity(const uint8_t validity_behaviour, const uint8_t time_units = 0, const uint16_t no_time_units = 0) {
				tag = MS_VALIDITY;
				length = 1 + (validity_behaviour == 4 ? 3:0);
				value = new uint8_t[length];
				value[0] = validity_behaviour;
				value[1] = time_units;
				::memcpy(value+2, &no_time_units, sizeof(no_time_units));
			}

			void set_network_error_code(const uint8_t network_type, const uint16_t error_code) {
				tag = NETWORK_ERROR_CODE;
				length = 3;
				value = new uint8_t[length];
				value[0] = network_type;
				::memcpy(value+1, &error_code, sizeof(error_code));
			}

			void set_number_of_messages(const uint8_t no_messages) {
				set(NUMBER_OF_MESSAGES, no_messages);
			}

			void set_payload_type(const uint8_t type) {
				set(PAYLOAD_TYPE, type);
			}

			void set_privacy_indicator(const uint8_t level) {
				set(PRIVACY_INDICATOR, level);
			}

			void set_qos_time_to_live(const uint32_t time_sec) {
				set(QOS_TIME_TO_LIVE, time_sec);
			}

			void set_receipted_message_id(const std::string &message_id) {
				set(RECEIPTED_MESSAGE_ID, message_id, 65, 1);
			}

			void set_sar_msg_ref_num(const uint16_t ref_number) {
				set(SAR_MSG_REF_NUM, ref_number);
			}

			void set_sar_segment_seqnum(const uint8_t seq_number) {
				set(SAR_SEGMENT_SEQNUM, seq_number);
			}

			void set_sar_total_segments(const uint8_t total_segments) {
				set(SAR_TOTAL_SEGMENTS, total_segments);
			}

			void set_sc_interface_version(const uint8_t version) {
				set(SC_INTERFACE_VERSION, version);
			}

			void set_set_dpf(const bool delivery_failure_requested) {
				set(SET_DPF, uint8_t(delivery_failure_requested?1:0));
			}

			void set_sm_signal(const uint16_t signal) {
				set(SM_SIGNAL, signal);
			}

			void set_source_addr_subunit(const uint8_t subunit) {
				set(SOURCE_ADDR_SUBUNIT, subunit);
			}

			void set_source_bearer_type(const uint8_t type) {
				set(SOURCE_BEARER_TYPE, type);
			}

			void set_source_network_id(const std::string &id) {
				set(SOURCE_NETWORK_ID, id, 65, 7);
			}

			void set_source_network_type(const uint8_t type) {
				set(SOURCE_NETWORK_TYPE, type);
			}

			void set_source_node_id(const std::string &node_id) {
				set(SOURCE_NODE_ID, node_id, 6, 6);
			}

			void set_source_port(const uint16_t port) {
				set(SOURCE_PORT, port);
			}

			void set_source_subaddress(const uint16_t subaddress_tag, const std::string &subaddress) {
				tag = SOURCE_SUBADDRESS;
				length = std::max(std::min(subaddress.size(), size_t(23)), size_t(2));
				value = new uint8_t[length];
				::memcpy(value, &subaddress_tag, sizeof(subaddress_tag));
				::memcpy(value+sizeof(subaddress_tag), subaddress.c_str(), std::min(subaddress.size(), size_t(length - sizeof(subaddress_tag))));
			}

			void set_source_telematics_id(const uint8_t protocol_id) {
				set(SOURCE_TELEMATICS_ID, protocol_id);
			}

			void set_user_message_reference(const uint16_t reference) {
				set(USER_MESSAGE_REFERENCE, reference);
			}

			void set_user_response_code(const uint8_t response_code) {
				set(USER_RESPONSE_CODE, response_code);
			}

			void set_ussd_service_op(const uint8_t service_op) {
				set(USSD_SERVICE_OP, service_op);
			}




		};

		SMPP_PDU_TLV_SIMPLE(source_telematics_id, SOURCE_TELEMATICS_ID, uint8_t);
		SMPP_PDU_TLV_SIMPLE(user_message_reference, USER_MESSAGE_REFERENCE, uint16_t);
		SMPP_PDU_TLV_SIMPLE(user_response_code, USER_RESPONSE_CODE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(ussd_service_op, USSD_SERVICE_OP, uint8_t);


	};

};
#endif /* PDU_TLV_H_ */
