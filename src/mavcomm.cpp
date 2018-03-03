/*
 * mavcomm.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: kyle
 */
#include "mavcomm.h"
#include <cstdio>

using boost::system::error_code;
using boost::asio::io_service;
using boost::asio::buffer;

MAVComm::MAVComm(uint8_t system_id, uint8_t component_id,
		std::string device, unsigned baudrate):
			io_service(),
			serial_dev(io_service)
{
	using SPB = boost::asio::serial_port_base;
	serial_dev.open(device);

	// Set baudrate and 8N1 mode
	serial_dev.set_option(SPB::baud_rate(baudrate));
	serial_dev.set_option(SPB::character_size(8));
	serial_dev.set_option(SPB::parity(SPB::parity::none));
	serial_dev.set_option(SPB::stop_bits(SPB::stop_bits::one));
	serial_dev.set_option(SPB::flow_control(SPB::flow_control::none));

	fprintf(stderr,"Successfully opened serial device\n");
	// give some work to io_service before start
	io_service.post(std::bind(&MAVComm::do_read, this));

		// run io_service for async io
//		io_thread = std::thread([this] () {
//					utils::set_this_thread_name("mserial%zu", conn_id);
//					io_service.run();
//				});

}

MAVComm::~MAVComm(){
	close();
}

void MAVComm::close()
{
	lock_guard lock(mutex);
	if (!is_open())
		return;

	io_service.stop();
	serial_dev.close();

	if (io_thread.joinable())
		io_thread.join();

	if (port_closed_cb)
		port_closed_cb();
}

void MAVComm::do_read(void)
{
	auto sthis = shared_from_this();
	serial_dev.async_read_some(
			buffer(rx_buf),
			[sthis] (error_code error, size_t bytes_transferred) {
				if (error) {
					printf("receive: %s", error.message().c_str());
					sthis->close();
					return;
				}

				//sthis->parse_buffer(PFX, sthis->rx_buf.data(), sthis->rx_buf.size(), bytes_transferred);
				sthis->do_read();
			});
}
