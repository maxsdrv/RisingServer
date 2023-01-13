#include <algorithm>

#include "MainBus.h"
#include "MMKOErrors.h"
#include "MonitorMode.h"

MonitorMode::MonitorMode(MainBus* object_mmko) :
		monitor_session(object_mmko->get_mko_session())
{
	try {
		monitor_status = MkoExceptions::check_functions("Monitor configure",
				monitor_session, unmmko1_mon_configure, monitor_session,
				UNMMKO1_MON_DEFAULT | UNMMKO1_MON_BUS_A_AND_B);
	}
	catch(const MkoExceptions& ex) {
		std::cerr << ex.what();
	}
	std::cout << "MonitorMode\n";
}
void MonitorMode::start_monitor() const {
	unmmko1_mon_start(monitor_session);
}
bool MonitorMode::messages_read() {
	uint32_t messagesCount{};
	auto lMsg = std::make_unique<unmmko1_message>();
	if (unmmko1_mon_messages_count(monitor_session, &messagesCount) < 0)
		return false;
	/* read messages and store into vector */
	auto status = unmmko1_mon_messages_read(monitor_session, messagesCount, lMsg.get(), &messagesCount);
	if (status < 0)
		return false;
	else
		messages.push_back(std::move(lMsg));
	return true;
}
const Msg& MonitorMode::pull_message() {
	if (messages_read()) {
		for (const auto& msg : messages) {
			std::cerr << "State:\n";
			if (UNMMKO1_MSG_ERR_OK == msg->error)
				std::cerr << "\tOK\n";
			if (msg->error & UNMMKO1_MSG_ERR_NO_RESPONSE)
				std::cerr << "\tNo response\n";
			if (msg->error & UNMMKO1_MSG_ERR_ANY_ERROR_BIT)
				std::cerr << "\tAny error\n";
			if (msg->error & UNMMKO1_MSG_ERR_PROTOCOL)
				std::cerr << "\tProtocol error\n";
			if (msg->error & UNMMKO1_MSG_ERR_DATA_COUNT)
				std::cerr << "\tData count error\n";
			if (msg->error & UNMMKO1_MSG_ERR_MANCHECTER)
				std::cerr << "\tManchester error\n";
			if (msg->error & UNMMKO1_MSG_ERR_SYSTEM)
				std::cerr << "\tSystem error\n";
		}
	}
	return messages;
}
void MonitorMode::stop_monitor() const {
	unmmko1_mon_stop(monitor_session);
}
MonitorMode::~MonitorMode() {
	std::cout << "~MonitorMode()\n";
}















