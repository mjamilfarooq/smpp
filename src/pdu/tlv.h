/*
 * tlv.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef PDU_TLV_H_
#define PDU_TLV_H_

#include "pdu.h"


#define SMPP_PDU_TLV_NOVALUE(name, tag_value) \
		struct name: public tlv { \
			name(): \
				tlv(tag_value) { \
			} \
		};


#define SMPP_PDU_TLV_SIMPLE(name,tag_value,type) \
		struct name: public tlv { \
			name(type value): \
				tlv(tag_value, sizeof(type), (uint8_t *)&value) { \
			} \
			\
			type get() { \
				return *reinterpret_cast<type *>(value); \
			} \
		};

#define SMPP_PDU_TLV_STRING(name,tag_value) \
		struct name: public tlv { \
			name(const std::string &value): \
				tlv(tag_value, value) { \
			} \
			\
			std::string get() { \
				return std::string(reinterpret_cast<char *>(value), length); \
			} \
		};


#define SMPP_PDU_TLV_STRING_RANGE(name,tag_value,max,min) \
		struct name: public tlv { \
			name(const std::string &value): \
				tlv(tag_value, value, max, min) { \
			} \
			\
			std::string get() { \
				return std::string(reinterpret_cast<char *>(value), length); \
			} \
		};



namespace smpp {
	namespace pdu {

#pragma pack(push, 1)
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
			static const uint16_t CONGESTION_STATE				= 0x0428;
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

			tlv(): tag(0), length(0), value(nullptr) {

			}

			//some TLV's require only tag and 0 length and no value part
			tlv(uint16_t tag):
				tag(tag), length(0), value(nullptr) {
			}

			tlv(uint16_t tag, uint16_t length, uint8_t *value )
				: tag(tag), length(length), value(nullptr) {
				this->value = new uint8_t[this->length];
				::memcpy(this->value, value, this->length);
			}

			tlv(uint16_t tag, const std::string &value, size_t max, size_t min):
				tag(tag), length(0), value(nullptr) {
				length = std::max(std::min(value.size(), max), min);
				this->value = new uint8_t[length];
				::memcpy(this->value, value.c_str(), std::min(value.size(), size_t(length)));
			}

			tlv(const uint16_t tag, const std::string &value):
				tag(tag), length(0), value(nullptr) {
				length = value.size();
				this->value = new uint8_t[length];
				::memcpy(this->value, value.c_str(), length);
			}

			~tlv() {
				delete [] value;
			}


			size_t size() {
				return sizeof(tag) + sizeof(length) + length;
			}

			size_t to_buffer(uint8_t * const buffer) {
				auto copy_offset = size_t(0);
				::memcpy(buffer+copy_offset, &tag, sizeof(tag)); copy_offset += sizeof(tag);
				::memcpy(buffer+copy_offset, &length, sizeof(length)); copy_offset += sizeof(length);
				::memcpy(buffer+copy_offset, value, length); copy_offset += length;
				return copy_offset;
			}

			size_t from_buffer(const uint8_t *buffer) {
				if ( nullptr == buffer ) {
					return 0;
				}
				auto copy_offset = size_t(0);
				::memcpy(&tag, buffer+copy_offset, sizeof(tag)); copy_offset += sizeof(tag);
				::memcpy(&length, buffer+copy_offset, sizeof(length)); copy_offset += sizeof(length);
				::memcpy(value, buffer+copy_offset, length); copy_offset += length;
				return copy_offset;
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


			//getters
			template<typename T>
			void get(T &value) {
				if ( length == sizeof(value) ) ::memcpy(value, this->value, length);
			}

			void get(std::string &value) {
				value = std::string(reinterpret_cast<char *>(this->value), length);
			}

			/*
			 * @brief if tlv belongs to same type as given in tag
			 *
			 * @param tag value as define above
			 */
			bool operator==(uint16_t tag) {
				return this->tag == tag;
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



			void set_broadcast_frequency_interval(const uint8_t time_units, const uint16_t no_time_units) {
				tag = BROADCAST_FREQUENCY_INTERVAL;
				length = 3;
				value = new uint8_t[length];
				value[0] = time_units;
				::memcpy(value+1, &no_time_units, sizeof(no_time_units));
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

			void set_dest_addr_np_country(const uint64_t country_code) {
				tag = DEST_ADDR_NP_COUNTRY;
				length = 5;		//TODO: not clear if it will always be 5 byte or can be less also value representation is also not clear
				value = new uint8_t[length];
				::memcpy(value, &country_code, length);
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

			//TODO: this logic should be treated separately through specialization
			void set_source_subaddress(const uint16_t subaddress_tag, const std::string &subaddress) {
				tag = SOURCE_SUBADDRESS;
				length = std::max(std::min(subaddress.size(), size_t(23)), size_t(2));
				value = new uint8_t[length];
				::memcpy(value, &subaddress_tag, sizeof(subaddress_tag));
				::memcpy(value+sizeof(subaddress_tag), subaddress.c_str(), std::min(subaddress.size(), size_t(length - sizeof(subaddress_tag))));
			}

		};


		SMPP_PDU_TLV_STRING_RANGE(additional_status_info_text, ADDITIONAL_STATUS_INFO_TEXT, 255, 1);
		SMPP_PDU_TLV_NOVALUE(alert_on_message_delivery, ALERT_ON_MESSAGE_DELIVERY);

		SMPP_PDU_TLV_STRING_RANGE(broadcast_end_time, BROADCAST_END_TIME, 16, 16);
		SMPP_PDU_TLV_SIMPLE(broadcast_error_status, BROADCAST_ERROR_STATUS, uint32_t);
		SMPP_PDU_TLV_SIMPLE(broadcast_area_success, BROADCAST_AREA_SUCCESS, uint8_t);
		SMPP_PDU_TLV_STRING_RANGE(broadcast_content_type_info, BROADCAST_CONTENT_TYPE_INFO, 255, 1);
		SMPP_PDU_TLV_SIMPLE(broadcast_channel_indicator, BROADCAST_CHANNEL_INDICATOR, uint8_t);
		SMPP_PDU_TLV_SIMPLE(broadcast_message_class, BROADCAST_MESSAGE_CLASS, uint8_t);
		SMPP_PDU_TLV_SIMPLE(broadcast_rep_num, BROADCAST_REP_NUM, uint16_t);
		SMPP_PDU_TLV_STRING_RANGE(broadcast_service_group, BROADCAST_SERVICE_GROUP, 255, 1);
		SMPP_PDU_TLV_SIMPLE(callback_num_pres_ind, CALLBACK_NUM_PRES_IND, uint8_t);
		SMPP_PDU_TLV_SIMPLE(congestion_state, CONGESTION_STATE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(delivery_failure_reason, DELIVERY_FAILURE_REASON, uint8_t);
		SMPP_PDU_TLV_STRING_RANGE(dest_addr_np_information, DEST_ADDR_NP_INFORMATION, 10, 10);
		SMPP_PDU_TLV_STRING_RANGE(dest_network_id, DEST_NETWORK_ID, 65, 7);
		SMPP_PDU_TLV_STRING_RANGE(dest_node_id, DEST_NODE_ID, 6, 6);
		SMPP_PDU_TLV_SIMPLE(dest_network_type, DEST_NETWORK_TYPE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(dest_addr_np_resolution, DEST_ADDR_NP_RESOLUTION, uint8_t);
		SMPP_PDU_TLV_SIMPLE(dest_addr_subunit, DEST_ADDR_SUBUNIT, uint8_t);
		SMPP_PDU_TLV_SIMPLE(dest_bearer_type, DEST_BEARER_TYPE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(dest_port, DEST_PORT, uint16_t);
		SMPP_PDU_TLV_SIMPLE(display_time, DISPLAY_TIME, uint8_t);
		SMPP_PDU_TLV_SIMPLE(dpf_result, DPF_RESULT, uint8_t);
		SMPP_PDU_TLV_SIMPLE(its_reply_type, ITS_REPLY_TYPE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(language_indicator, LANGUAGE_INDICATOR, uint8_t);
		SMPP_PDU_TLV_STRING(message_payload, MESSAGE_PAYLOAD);
		SMPP_PDU_TLV_SIMPLE(message_state, MESSAGE_STATE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(more_messages_to_send, MORE_MESSAGES_TO_SEND, uint8_t);
		SMPP_PDU_TLV_SIMPLE(ms_availability_status, MS_AVAILABILITY_STATUS, uint8_t);
		SMPP_PDU_TLV_SIMPLE(number_of_messages, NUMBER_OF_MESSAGES, uint8_t);
		SMPP_PDU_TLV_SIMPLE(payload_type, PAYLOAD_TYPE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(privacy_indicator, PRIVACY_INDICATOR, uint8_t);
		SMPP_PDU_TLV_SIMPLE(qos_time_to_live, QOS_TIME_TO_LIVE, uint32_t);
		SMPP_PDU_TLV_STRING_RANGE(receipted_message_id, RECEIPTED_MESSAGE_ID, 65, 1);
		SMPP_PDU_TLV_SIMPLE(sar_msg_ref_num, SAR_MSG_REF_NUM, uint16_t);
		SMPP_PDU_TLV_SIMPLE(sar_segment_seqnum, SAR_SEGMENT_SEQNUM, uint8_t);
		SMPP_PDU_TLV_SIMPLE(sar_total_segments, SAR_TOTAL_SEGMENTS, uint8_t);
		SMPP_PDU_TLV_SIMPLE(sc_interface_version, SC_INTERFACE_VERSION, uint8_t);
		SMPP_PDU_TLV_SIMPLE(set_dpf, SET_DPF, uint8_t);
		SMPP_PDU_TLV_SIMPLE(sm_signal, SM_SIGNAL, uint16_t);
		SMPP_PDU_TLV_SIMPLE(source_addr_subunit, SOURCE_ADDR_SUBUNIT, uint8_t);
		SMPP_PDU_TLV_SIMPLE(source_bearer_type, SOURCE_BEARER_TYPE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(source_network_type, SOURCE_NETWORK_TYPE, uint8_t);
		SMPP_PDU_TLV_STRING_RANGE(source_network_id, SOURCE_NETWORK_ID, 65, 7);
		SMPP_PDU_TLV_STRING_RANGE(source_node_id, SOURCE_NODE_ID, 6, 6);
		SMPP_PDU_TLV_SIMPLE(source_port, SOURCE_PORT, uint16_t);
		SMPP_PDU_TLV_SIMPLE(source_telematics_id, SOURCE_TELEMATICS_ID, uint8_t);
		SMPP_PDU_TLV_SIMPLE(user_message_reference, USER_MESSAGE_REFERENCE, uint16_t);
		SMPP_PDU_TLV_SIMPLE(user_response_code, USER_RESPONSE_CODE, uint8_t);
		SMPP_PDU_TLV_SIMPLE(ussd_service_op, USSD_SERVICE_OP, uint8_t);

#pragma pack(pop)

	};

};
#endif /* PDU_TLV_H_ */
