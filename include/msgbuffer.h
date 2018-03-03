/*
 * msgbuffer.h
 *
 *  Created on: Mar 3, 2018
 *      Author: kyle
 */

#ifndef INCLUDE_MSGBUFFER_H_
#define INCLUDE_MSGBUFFER_H_

#include "mavlink/chibi/mavlink.h"

struct MsgBuffer {
	//! Maximum buffer size with padding for CRC bytes (280 + padding)
	static constexpr ssize_t MAX_SIZE = MAVLINK_MAX_DIALECT_PAYLOAD_SIZE + 16;
	uint8_t data[MAX_SIZE];
	ssize_t pos;
	ssize_t len;

	MsgBuffer() :
		pos(0),
		len(0)
	{ }

	/**
	 * @brief Buffer constructor from mavlink_message_t
	 */
	explicit MsgBuffer(const mavlink_message_t *msg) :
		pos(0)
	{
		len = mavlink_msg_to_send_buffer(data, msg);
		// paranoic check, it must be less than MAVLINK_MAX_PACKET_LEN
		assert(len < MAX_SIZE);
	}

	/**
	 * @brief Buffer constructor for send_bytes()
	 * @param[in] nbytes should be less than MAX_SIZE
	 */
	MsgBuffer(const uint8_t *bytes, ssize_t nbytes) :
		pos(0),
		len(nbytes)
	{
		assert(0 < nbytes && nbytes < MAX_SIZE);
		memcpy(data, bytes, nbytes);
	}

	virtual ~MsgBuffer() {
		pos = 0;
		len = 0;
	}

	uint8_t *dpos() {
		return data + pos;
	}

	ssize_t nbytes() {
		return len - pos;
	}
};
#endif /* INCLUDE_MSGBUFFER_H_ */
