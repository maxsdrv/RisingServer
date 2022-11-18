#include "MonitorMode.h"

#include <memory>
#include <algorithm>

#include "MMKOInterface.h"

MonitorMode::MonitorMode(MMKOInterface* objMko)
		: mMko(objMko),
		  monitorSession(Common::getInstance().session)
{
	monitorStatus = mMko->mkoStatus;
	try
	{
		StartMonitor();
	}
	catch(MMKOErrors& ex)
	{
		std::cerr << ex.what();
		StopMonitor();
	}
}
void MonitorMode::StartMonitor() const
{
	int errMonitor = unmmko1_mon_configure(Common::getInstance().session, UNMMKO1_MON_TRANSFORM
			| UNMMKO1_MON_BUS_A_AND_B);
	if (errMonitor < 0)
	{
		auto errMsg = MMKOErrors::ErrorMessage(Common::getInstance().session, &unmmko1_error_message);
		throw MMKOErrors(__FUNCTION__ + std::get<0>(errMsg), std::get<1>(errMsg));
	}
	else
	{
		 MkoValidation(__FUNCTION__, monitorSession,
				 unmmko1_mon_start(monitorSession));
	}
}
bool MonitorMode::MessagesRead()
{
	uint32_t messagesCount{};
	auto lMsg = std::make_unique<unmmko1_message>();
	if (unmmko1_mon_messages_count(monitorSession, &messagesCount) < 0)
		return false;
	/* read messages and store into vector */
	auto status = unmmko1_mon_messages_read(monitorSession, messagesCount, lMsg.get(), &messagesCount);
	if (status < 0)
		return false;
	else
		messages.push_back(std::move(lMsg));
	return true;
}
const Msg& MonitorMode::PullMessage()
{
	if (MessagesRead())
	{
		for (const auto& msg : messages)
		{
			std::cerr << "State:\n";
			if (UNMMKO1_MSG_ERR_OK == msg->error)
				std::cerr << "\tOK\n";
			if (msg->error & UNMMKO1_MSG_ERR_NO_RESPONSE)
				std::cerr << "\tNo response\n";
			if(msg->error & UNMMKO1_MSG_ERR_ANY_ERROR_BIT)
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
void MonitorMode::StopMonitor() const
{
	MkoValidation(__FUNCTION__, monitorSession, unmmko1_mon_stop(monitorSession));
}
MonitorMode::~MonitorMode()
{
	StopMonitor();
}















