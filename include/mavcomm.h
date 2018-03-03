/*
 * mavcomm.h
 *
 *  Created on: Mar 3, 2018
 *      Author: kyle
 */

#ifndef INCLUDE_MAVCOMM_H_
#define INCLUDE_MAVCOMM_H_

#include <array>
#include <deque>
#include <memory>
#include <thread>
#include <mutex>

#include <boost/asio.hpp>

#include "msgbuffer.h"

class MAVComm:public std::enable_shared_from_this<MAVComm>{
	using lock_guard = std::lock_guard<std::recursive_mutex>;
public:
	static constexpr auto DEFAULT_DEVICE = "/dev/ttyUSB0";
	static constexpr auto DEFAULT_BAUDRATE = 38400;

	/**
	 * @throws boost::system::system_error upon unsuccessful system call
	 */
	MAVComm(uint8_t system_id = 1, uint8_t component_id = 1,
			std::string device = DEFAULT_DEVICE, unsigned baudrate =
					DEFAULT_BAUDRATE);

	~MAVComm();

	void close();

	using closed_callback_t = std::function<void (void)>;
	closed_callback_t port_closed_cb;

	inline bool is_open(){
		return serial_dev.is_open();
	}

private:
	boost::asio::io_service io_service;
	std::thread io_thread;
	boost::asio::serial_port serial_dev;

	std::recursive_mutex mutex;
	std::deque<MsgBuffer> tx_q;
	std::array<uint8_t, MsgBuffer::MAX_SIZE> rx_buf;

	void do_read();
	void do_write(bool check_tx_state);
};





#endif /* INCLUDE_MAVCOMM_H_ */
